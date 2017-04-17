#ifndef MYRIO_DRIVER_DIGITAL_INPUTS_H_
#define MYRIO_DRIVER_DIGITAL_INPUTS_H_

#include "device.h"

struct digital_input_t;

void digital_input_create(struct digital_input_t *di, uint8_t channel_num);


#endif /* MYRIO_DRIVER_DIGITAL_INPUTS_H_ */
