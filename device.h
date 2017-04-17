#ifndef MYRIO_DRIVER_DEVICE_H_
#define MYRIO_DRIVER_DEVICE_H_

#include "MyRio.h"


struct dio_channel_bank_t {
    uint32_t dir;
    uint32_t out;
    uint32_t in;
};



struct dio_channel_t {
	struct dio_channel_bank_t *bank;
	uint8_t bit;
};

extern const struct dio_channel_t dio_channels[32];

#endif /* MYRIO_DRIVER_DEVICE_H_ */
