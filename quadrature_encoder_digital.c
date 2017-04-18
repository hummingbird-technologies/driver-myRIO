#include "quadrature_encoder_digital.h"

status_t quadrature_encoder_digital_init(
        struct quadrature_encoder_digital_t *qe,
        uint8_t channel_a_num,
        uint8_t channel_b_num) {
    status_t status;

    qe->reading = 0;

    status = digital_input_init(&qe->digital_input_a, channel_a_num);
    if (status != status_ok) {
        return status;
    }

    return digital_input_init(&qe->digital_input_b, channel_b_num);
}

status_t quadrature_encoder_digital_step(struct quadrature_encoder_digital_t *qe) {
    status_t status;
    bool old_a_value = qe->digital_input_a.value;
    bool new_a_value;

    status = digital_input_read(&qe->digital_input_a);
    if (status != status_ok) {
        return status;
    }

    new_a_value = qe->digital_input_a.value;

    if (new_a_value != old_a_value) {
        status = digital_input_read(&qe->digital_input_b);
        if (status != status_ok) {
            return status;
        }

        if (!qe->digital_input_b.value) {
            if (new_a_value) {
                qe->a_leading = true;
                qe->reading += 1;
            } else {
                qe->a_leading = false;
                qe->reading -= 1;
            }
        }
    }

    return status_ok;
}
