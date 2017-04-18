#ifndef MYRIO_DRIVER_QUADRATURE_ENCODER_H_
#define MYRIO_DRIVER_QUADRATURE_ENCODER_H_

#include <stdbool.h>
#include "digital_input.h"

struct quadrature_encoder_t {
    struct digital_input_t digital_input_a;
    struct digital_input_t digital_input_b;

    bool a_leading;
    uint32_t reading;
};

status_t quadrature_encoder_init(
        struct quadrature_encoder_t *,
        uint8_t channel_a_num,
        uint8_t channel_b_num);

status_t quadrature_encoder_step(struct quadrature_encoder_t *qe);

#endif /* MYRIO_DRIVER_QUADRATURE_ENCODER_H_ */
