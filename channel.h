#ifndef MYRIO_DRIVER_DEVICE_H_
#define MYRIO_DRIVER_DEVICE_H_

#include <stdbool.h>
#include "MyRio.h"


typedef uint8_t status_t;
static const status_t status_ok = 0;
static const status_t channel_not_available = 1;

struct channel_personality_t {
    struct channel_t *channel;
};

typedef NiFpga_Status (* channel_setup_func)(const struct channel_personality_t *);

struct channel_t {
    bool acquired;
    channel_setup_func setup;
    struct channel_personality_t *personality;
};

status_t channel_register(
        struct channel_personality_t *,
        channel_setup_func);


status_t device_setup();

status_t device_teardown();


#define NUM_DIO_CHANNELS 40

struct dio_channel_bank_t {
    uint32_t dir;
    uint32_t out;
    uint32_t in;
};

struct dio_channel_personality_t {
    struct channel_t *channel;
    struct dio_channel_bank_t *bank;
    uint8_t bit;
};

extern const struct dio_channel_personality_t dio_channel_personalities[NUM_DIO_CHANNELS];


#endif /* MYRIO_DRIVER_DEVICE_H_ */
