#include <stdio.h>
#include <unistd.h>

#include "digital_input.h"


#define MICROSECONDS_PER_SECOND 1000000

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
    status_t status;

    status = channel_register_setup((struct channel_personality_t *) channel_personality, digital_input_setup);
    if (status != status_ok) {
        return false;
    }

    di->channel_personality = channel_personality;
    return true;
}

status_t digital_input_read(struct digital_input_t *di) {
    const struct dio_channel_personality_t *personality = di->channel_personality;
    NiFpga_Status status;
    uint8_t inValue;

    status = NiFpga_ReadU8(myrio_session, personality->bank->in, &inValue);
    MyRio_ReturnStatusIfNotSuccess(status, "Could not read from the DIO channel in register!");

    inValue = inValue & (1 << personality->bit);
    di->value = (inValue > 0) ? NiFpga_True : NiFpga_False;
    printf("Reading: %d\n", di->value);
    return status_ok;
}


static void *digital_input_stop(void *ra) {
    struct digital_input_t *digital_input = ((struct digital_input_run_args_t *) ra)->di;
    digital_input->running = false;
    return NULL;
}

static void *digital_input_start(void *ra) {
    struct digital_input_run_args_t *run_args = (struct digital_input_run_args_t *) ra;
    uint32_t period_micros = MICROSECONDS_PER_SECOND / run_args->frequency;

    run_args->di->running = true;
    while (run_args->di->running) {
        digital_input_read(run_args->di);
        usleep(period_micros);
    }

    return NULL;
}

void digital_input_run(struct digital_input_run_args_t *ra) {
    channel_run_setup((struct channel_personality_t *) ra->di->channel_personality,
            digital_input_start,
            digital_input_stop,
            ra);
}


