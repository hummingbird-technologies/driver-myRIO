#ifndef MYRIO_DRIVER_DIGITAL_INPUTS_H_
#define MYRIO_DRIVER_DIGITAL_INPUTS_H_

#include "device.h"

struct digital_input_t {
	struct channel_t channel;
	uint8_t channel_num;
};

void digital_input_init(struct digital_input_t *, uint8_t channel_num);

NiFpga_Bool digital_input_read(struct digital_input_t *);

#endif /* MYRIO_DRIVER_DIGITAL_INPUTS_H_ */
