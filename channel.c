#include <stdio.h>
#include "channel.h"

#define NUM_A_CHANNELS 34
#define NUM_B_CHANNELS 34
#define NUM_C_CHANNELS 20

struct channel_t A_CHANNELS[NUM_A_CHANNELS] = {{0}};
struct channel_t B_CHANNELS[NUM_B_CHANNELS] = {{0}};
struct channel_t C_CHANNELS[NUM_C_CHANNELS] = {{0}};

status_t channel_register_setup(
        struct channel_personality_t *cp,
        channel_setup_func setup) {
    struct channel_t *channel = cp->channel;

    if (channel->acquired) {
        return channel_not_available;
    }

    channel->acquired = true;
    channel->setup = setup;
    channel->personality = cp;
    return status_ok;
}

status_t channel_run_setup(
        struct channel_personality_t *cp,
        channel_run_func start,
        channel_run_func stop,
        void *run_args) {
    struct channel_t *channel = cp->channel;

    if (!channel->acquired) {
        return channel_not_acquired;
    }

    if (channel->personality != cp) {
        return channel_not_available;
    }

    channel->start = start;
    channel->stop = stop;
    channel->run_args = run_args;
    return status_ok;
}


status_t device_setup() {
    status_t status;
    uint8_t i;

    status = MyRio_Open();
    MyRio_ReturnStatusIfNotSuccess(status, "Could not open myRIO session.");

    for (i = 0; i < NUM_A_CHANNELS; i++) {
        struct channel_t *channel = &A_CHANNELS[i];
        if (channel->acquired) {
            if (channel->setup != NULL) {
                channel->setup(channel->personality);
            }
        }
    }

    for (i = 0; i < NUM_B_CHANNELS; i++) {
        struct channel_t *channel = &B_CHANNELS[i];
        if (channel->acquired) {
            if (channel->setup != NULL) {
                channel->setup(channel->personality);
            }
        }
    }

    for (i = 0; i < NUM_C_CHANNELS; i++) {
        struct channel_t *channel = &C_CHANNELS[i];
        if (channel->acquired) {
            if (channel->setup != NULL) {
                channel->setup(channel->personality);
            }
        }
    }

    return status_ok;
}

static status_t channel_start(struct channel_t *c) {
    return pthread_create(&c->thread, NULL, c->start, c->run_args);
}

void device_run() {
    uint8_t i;

    for (i = 0; i < NUM_A_CHANNELS; i++) {
        struct channel_t *channel = &A_CHANNELS[i];
        if (channel->acquired) {
            if (channel->start != NULL) {
                channel_start(channel);
            }
        }
    }

    for (i = 0; i < NUM_B_CHANNELS; i++) {
        struct channel_t *channel = &B_CHANNELS[i];
        if (channel->acquired) {
            if (channel->start != NULL) {
                channel_start(channel);
            }
        }
    }

    for (i = 0; i < NUM_C_CHANNELS; i++) {
        struct channel_t *channel = &C_CHANNELS[i];
        if (channel->acquired) {
            if (channel->start != NULL) {
                channel_start(channel);
            }
        }
    }
}

status_t device_teardown() {
    uint8_t i;

    // Stop threads
    for (i = 0; i < NUM_A_CHANNELS; i++) {
        struct channel_t *channel = &A_CHANNELS[i];
        if (channel->acquired) {
            if (channel->stop != NULL) {
                channel->stop(channel->run_args);
            }
        }
    }

    for (i = 0; i < NUM_B_CHANNELS; i++) {
        struct channel_t *channel = &B_CHANNELS[i];
        if (channel->acquired) {
            if (channel->stop != NULL) {
                channel->stop(channel->run_args);
            }
        }
    }

    for (i = 0; i < NUM_C_CHANNELS; i++) {
        struct channel_t *channel = &C_CHANNELS[i];
        if (channel->acquired) {
            if (channel->stop != NULL) {
                channel->stop(channel->run_args);
            }
        }
    }

    // Wait on threads
    for (i = 0; i < NUM_A_CHANNELS; i++) {
        struct channel_t *channel = &A_CHANNELS[i];
        if (channel->acquired) {
            if (channel->start != NULL) {
                pthread_join(channel->thread, NULL);
            }
        }
    }

    for (i = 0; i < NUM_B_CHANNELS; i++) {
        struct channel_t *channel = &B_CHANNELS[i];
        if (channel->acquired) {
            if (channel->start != NULL) {
                pthread_join(channel->thread, NULL);
            }
        }
    }

    for (i = 0; i < NUM_C_CHANNELS; i++) {
        struct channel_t *channel = &C_CHANNELS[i];
        if (channel->acquired) {
            if (channel->start != NULL) {
                pthread_join(channel->thread, NULL);
            }
        }
    }

    return MyRio_Close();
}


struct dio_channel_bank_t
        a1_dio_channel_bank = {DIOA_70DIR, DIOA_70OUT, DIOA_70IN},
        a2_dio_channel_bank = {DIOA_158DIR, DIOA_158OUT, DIOA_158IN},
        b1_dio_channel_bank = {DIOB_70DIR, DIOB_70OUT, DIOB_70IN},
        b2_dio_channel_bank = {DIOB_158DIR, DIOB_158OUT, DIOB_158IN},
        c1_dio_channel_bank = {DIOC_70DIR, DIOC_70OUT, DIOC_70IN};


const struct dio_channel_personality_t dio_channel_personalities[NUM_DIO_CHANNELS] = {
        // Channel Bank A 0-7
        {&A_CHANNELS[11], &a1_dio_channel_bank, 0},
        {&A_CHANNELS[13], &a1_dio_channel_bank, 1},
        {&A_CHANNELS[15], &a1_dio_channel_bank, 2},
        {&A_CHANNELS[17], &a1_dio_channel_bank, 3},
        {&A_CHANNELS[19], &a1_dio_channel_bank, 4},
        {&A_CHANNELS[21], &a1_dio_channel_bank, 5},
        {&A_CHANNELS[23], &a1_dio_channel_bank, 6},
        {&A_CHANNELS[25], &a1_dio_channel_bank, 7},

        // Channel Bank A 8-15
        {&A_CHANNELS[27], &a2_dio_channel_bank, 0},
        {&A_CHANNELS[29], &a2_dio_channel_bank, 1},
        {&A_CHANNELS[31], &a2_dio_channel_bank, 2},
        {&A_CHANNELS[18], &a2_dio_channel_bank, 3},
        {&A_CHANNELS[22], &a2_dio_channel_bank, 4},
        {&A_CHANNELS[26], &a2_dio_channel_bank, 5},
        {&A_CHANNELS[32], &a2_dio_channel_bank, 6},
        {&A_CHANNELS[34], &a2_dio_channel_bank, 7},

        // Channel Bank B 0-7
        {&B_CHANNELS[11], &b1_dio_channel_bank, 0},
        {&B_CHANNELS[13], &b1_dio_channel_bank, 1},
        {&B_CHANNELS[15], &b1_dio_channel_bank, 2},
        {&B_CHANNELS[17], &b1_dio_channel_bank, 3},
        {&B_CHANNELS[19], &b1_dio_channel_bank, 4},
        {&B_CHANNELS[21], &b1_dio_channel_bank, 5},
        {&B_CHANNELS[23], &b1_dio_channel_bank, 6},
        {&B_CHANNELS[25], &b1_dio_channel_bank, 7},

        // Channel Bank B 8-15
        {&B_CHANNELS[27], &b2_dio_channel_bank, 0},
        {&B_CHANNELS[29], &b2_dio_channel_bank, 1},
        {&B_CHANNELS[31], &b2_dio_channel_bank, 2},
        {&B_CHANNELS[18], &b2_dio_channel_bank, 3},
        {&B_CHANNELS[22], &b2_dio_channel_bank, 4},
        {&B_CHANNELS[26], &b2_dio_channel_bank, 5},
        {&B_CHANNELS[32], &b2_dio_channel_bank, 6},
        {&A_CHANNELS[34], &b2_dio_channel_bank, 7},

        // Channel Bank C 0-7
        {&C_CHANNELS[11], &c1_dio_channel_bank, 0},
        {&C_CHANNELS[12], &c1_dio_channel_bank, 1},
        {&C_CHANNELS[13], &c1_dio_channel_bank, 2},
        {&C_CHANNELS[14], &c1_dio_channel_bank, 3},
        {&C_CHANNELS[15], &c1_dio_channel_bank, 4},
        {&C_CHANNELS[16], &c1_dio_channel_bank, 5},
        {&C_CHANNELS[17], &c1_dio_channel_bank, 6},
        {&C_CHANNELS[18], &c1_dio_channel_bank, 7},
};
