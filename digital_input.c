#include "digital_input.h"

struct digital_input_t {
	uint8_t channel_num;
	struct dio_channel_t *channel;
};

void digital_input_create(struct digital_input_t *di, uint8_t channel_num) {
	di->channel_num = channel_num;
	di->channel = dio_channels[channel_num];
}

NiFpga_Status digital_input_setup(struct digital_input_t *di) {
	NiFpga_Status status;
	uint8_t dirValue;

	status = NiFpga_ReadU8(myrio_session, di->channel->bank->dir, &dirValue);
	MyRio_ReturnStatusIfNotSuccess(status, "Could not read from the DIO channel direction register!");

	dirValue = dirValue & ~(1 << di->channel->bit);
	return NiFpga_WriteU8(myrio_session, di->channel->bank->dir, dirValue);
}

NiFpga_Bool digital_input_read(struct digital_input_t *di) {
	NiFpga_Status status;
	uint8_t inValue;

	NiFpga_ReadArrayU8(myrio_session, di->channel->bank->in, &inValue);
	MyRio_ReturnStatusIfNotSuccess(status, "Could not read from the DIO channel in register!");

	inValue = inValue & (1 << di->channel->bit);
	return (inValue > 0) ? NiFpga_True : NiFpga_False;
}
