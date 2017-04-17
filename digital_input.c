#include "digital_input.h"

struct digital_input_t {
	uint8_t channel_num;
	struct dio_channel_t *channel;
};

void digital_input_create(struct digital_input_t *di, uint8_t channel_num) {
	di->channel_num = channel_num;
	di->channel = dio_channels[channel_num];
}
