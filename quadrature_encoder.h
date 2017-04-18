#ifndef MYRIO_DRIVER_QUADRATURE_ENCODER_H_
#define MYRIO_DRIVER_QUADRATURE_ENCODER_H_

#include "channel.h"

struct quadrature_encoder_t {
	const struct qenc_channel_personality_t *channel_personality;

	uint32_t value;
};

status_t quadrature_encoder_init(struct quadrature_encoder_t *qe, uint8_t encoder_num);

status_t quadrature_encoder_update(struct quadrature_encoder_t *);


#endif /* MYRIO_DRIVER_QUADRATURE_ENCODER_H_ */
