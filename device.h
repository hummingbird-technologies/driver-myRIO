#ifndef MYRIO_DRIVER_DEVICE_H_
#define MYRIO_DRIVER_DEVICE_H_

#include "MyRio.h"


#define NUM_DIO_CHANNELS 40

struct dio_channel_bank_t {
    uint32_t dir;
    uint32_t out;
    uint32_t in;
};



struct dio_channel_t {
	struct dio_channel_bank_t *bank;
	uint8_t bit;
};

extern const struct dio_channel_t dio_channels[NUM_DIO_CHANNELS];


struct channel_t {
	const void *ref;
	NiFpga_Status (*setup)(struct channel_t *);
};

#endif /* MYRIO_DRIVER_DEVICE_H_ */
