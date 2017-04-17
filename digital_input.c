#include <stdio.h>

#include "digital_input.h"

extern NiFpga_Session myrio_session;


static NiFpga_Status digital_input_setup(const struct channel_personality_t *cp) {
    struct dio_channel_personality_t *dcp = (struct dio_channel_personality_t *) cp;
    NiFpga_Status status;
    uint8_t dirValue;

    status = NiFpga_ReadU8(myrio_session, dcp->bank->dir, &dirValue);
    MyRio_ReturnStatusIfNotSuccess(status, "Could not read from the DIO channel direction register!");

    dirValue = dirValue & ~(1 << dcp->bit);
    return NiFpga_WriteU8(myrio_session, dcp->bank->dir, dirValue);
}

bool digital_input_init(struct digital_input_t *di, uint8_t channel_num) {
    const struct dio_channel_personality_t *channel_personality = &dio_channel_personalities[channel_num];
    channel_status_t status;

    status = channel_register((struct channel_personality_t *) channel_personality, digital_input_setup);
    if (status != channel_ok) {
        return false;
    }

    di->channel_personality = channel_personality;
    di->channel_num = channel_num;
    return true;
}

NiFpga_Bool digital_input_read(struct digital_input_t *di) {
    const struct dio_channel_personality_t *personality = di->channel_personality;
    NiFpga_Status status;
    uint8_t inValue;

    status = NiFpga_ReadU8(myrio_session, personality->bank->in, &inValue);
    MyRio_ReturnStatusIfNotSuccess(status, "Could not read from the DIO channel in register!");

    inValue = inValue & (1 << personality->bit);
    return (inValue > 0) ? NiFpga_True : NiFpga_False;
}
