#ifndef MYRIO_DRIVER_DEVICE_H_
#define MYRIO_DRIVER_DEVICE_H_

#include <stdbool.h>
#include <pthread.h>
#include "MyRio.h"


typedef uint8_t status_t;
static const status_t status_ok = 0;
static const status_t channel_not_available = 1;
static const status_t channel_not_acquired = 2;

struct channel_personality_t {
    struct channel_t *channel;
};

typedef NiFpga_Status (* channel_setup_func)(const struct channel_personality_t *);
typedef void *(* channel_run_func)(void *run_args);

struct channel_t {
    bool acquired;
    struct channel_personality_t *personality;

    channel_setup_func setup;
    channel_run_func start;
    channel_run_func stop;
    void *run_args;
    pthread_t thread;
};

status_t channel_register_setup(
        struct channel_personality_t *,
        channel_setup_func);

status_t channel_run_setup(
        struct channel_personality_t *,
        channel_run_func start,
        channel_run_func stop,
        void *run_args);


status_t device_setup();

void device_run();

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
