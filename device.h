#ifndef MYRIO_DRIVER_DEVICE_H_
#define MYRIO_DRIVER_DEVICE_H_

#include "MyRio.h"


struct dio_channel_bank_t {
    uint32_t dir;
    uint32_t out;
    uint32_t in;
};

struct dio_channel_bank_t
		a1_dio_channel_bank = {DIOA_70DIR, DIOA_70OUT, DIOA_70IN},
		a2_dio_channel_bank = {DIOA_158DIR, DIOA_158OUT, DIOA_158IN},
		b1_dio_channel_bank = {DIOB_70DIR, DIOB_70OUT, DIOB_70IN},
		b2_dio_channel_bank = {DIOB_158DIR, DIOB_158OUT, DIOB_158IN};


struct dio_channel_t {
	struct dio_channel_bank_t *Bank;
	uint8_t bit;
};

struct dio_channel_t dio_channels[32] = {
		// Channel Bank A 0-7
		{&a1_dio_channel_bank, 0},
		{&a1_dio_channel_bank, 1},
		{&a1_dio_channel_bank, 2},
		{&a1_dio_channel_bank, 3},
		{&a1_dio_channel_bank, 4},
		{&a1_dio_channel_bank, 5},
		{&a1_dio_channel_bank, 6},
		{&a1_dio_channel_bank, 7},

		// Channel Bank A 8-15
		{&a2_dio_channel_bank, 0},
		{&a2_dio_channel_bank, 1},
		{&a2_dio_channel_bank, 2},
		{&a2_dio_channel_bank, 3},
		{&a2_dio_channel_bank, 4},
		{&a2_dio_channel_bank, 5},
		{&a2_dio_channel_bank, 6},
		{&a2_dio_channel_bank, 7},

		// Channel Bank B 0-7
		{&b1_dio_channel_bank, 0},
		{&b1_dio_channel_bank, 1},
		{&b1_dio_channel_bank, 2},
		{&b1_dio_channel_bank, 3},
		{&b1_dio_channel_bank, 4},
		{&b1_dio_channel_bank, 5},
		{&b1_dio_channel_bank, 6},
		{&b1_dio_channel_bank, 7},

		// Channel Bank B 8-15
		{&b2_dio_channel_bank, 0},
		{&b2_dio_channel_bank, 1},
		{&b2_dio_channel_bank, 2},
		{&b2_dio_channel_bank, 3},
		{&b2_dio_channel_bank, 4},
		{&b2_dio_channel_bank, 5},
		{&b2_dio_channel_bank, 6},
		{&b2_dio_channel_bank, 7},
};

#endif /* MYRIO_DRIVER_DEVICE_H_ */
