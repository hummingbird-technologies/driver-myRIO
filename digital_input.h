#ifndef MYRIO_DRIVER_DIGITAL_INPUTS_H_
#define MYRIO_DRIVER_DIGITAL_INPUTS_H_

#include "device.h"

struct digital_input_t;

void digital_input_create(struct digital_input_t *, uint8_t channel_num);

NiFpga_Status digital_input_create(struct digital_input_t *);

NiFpga_Bool digital_input_read(struct digital_input_t *);

#endif /* MYRIO_DRIVER_DIGITAL_INPUTS_H_ */
