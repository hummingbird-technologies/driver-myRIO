#include <stdio.h>

#include "digital_input.h"

extern NiFpga_Session myrio_session;


static NiFpga_Status digital_input_setup(struct channel_t *c) {
	const struct dio_channel_t *ref = c->ref;
	NiFpga_Status status;
	uint8_t dirValue;

	status = NiFpga_ReadU8(myrio_session, ref->bank->dir, &dirValue);
	MyRio_ReturnStatusIfNotSuccess(status, "Could not read from the DIO channel direction register!");

	dirValue = dirValue & ~(1 << ref->bit);
	return NiFpga_WriteU8(myrio_session, ref->bank->dir, dirValue);
}

void digital_input_init(struct digital_input_t *di, uint8_t channel_num) {
	di->channel.setup = digital_input_setup;
	di->channel.ref = &dio_channels[channel_num];
	di->channel_num = channel_num;
}

NiFpga_Bool digital_input_read(struct digital_input_t *di) {
	const struct dio_channel_t *ref = di->channel.ref;
	NiFpga_Status status;
	uint8_t inValue;

	status = NiFpga_ReadU8(myrio_session, ref->bank->in, &inValue);
	MyRio_ReturnStatusIfNotSuccess(status, "Could not read from the DIO channel in register!");

	inValue = inValue & (1 << ref->bit);
	return (inValue > 0) ? NiFpga_True : NiFpga_False;
}
