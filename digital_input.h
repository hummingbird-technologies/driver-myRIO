#ifndef MYRIO_DRIVER_DIGITAL_INPUTS_H_
#define MYRIO_DRIVER_DIGITAL_INPUTS_H_

#include <stdbool.h>
#include "channel.h"

struct digital_input_t {
    const struct dio_channel_personality_t *channel_personality;

    /* running mode */
    bool running;
    bool value;
};

struct digital_input_run_args_t {
    struct digital_input_t *di;
    uint32_t frequency;
};

bool digital_input_init(struct digital_input_t *, uint8_t channel_num);

status_t digital_input_read(struct digital_input_t *);

void digital_input_run(struct digital_input_run_args_t *);

#endif /* MYRIO_DRIVER_DIGITAL_INPUTS_H_ */
