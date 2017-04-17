#ifndef MYRIO_DRIVER_DIGITAL_INPUTS_H_
#define MYRIO_DRIVER_DIGITAL_INPUTS_H_

#include <stdbool.h>
#include "device.h"

struct digital_input_t {
	const struct dio_channel_personality_t *channel_personality;
	uint8_t channel_num;
};

bool digital_input_init(struct digital_input_t *, uint8_t channel_num);

NiFpga_Bool digital_input_read(struct digital_input_t *);

#endif /* MYRIO_DRIVER_DIGITAL_INPUTS_H_ */
