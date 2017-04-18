#include <stdio.h>

#include "quadrature_encoder.h"


extern NiFpga_Session myrio_session;

typedef enum {
    encoder_enable = 0x01,      /**< The encoder enable option is set */
    encoder_reset = 0x02,       /**< The encoder reset counter option is set */
    encoder_signal_mode = 0x04,  /**< The encoder signal mode option is set */
    encoder_error = 0x08,       /**< The encoder clear error option is set */
    encoder_overflow = 0x10     /**< The encoder clear overflow option is set */
} encoder_configure_mask;

typedef enum {
	encoder_disabled = 0x00,
	encoder_enabled = 0x01,
	encoder_reset_counter = 0x02,

	encoder_quad_phase = 0x00,
	encoder_step_direction = 0x04,
	encoder_clear_error = 0x08,

	encoder_clear_overflow = 0x10
} encoder_configure_settings;

static NiFpga_Status quadrature_encoder_setup(const struct channel_personality_t *cp) {
	struct qenc_channel_personality_t *qcp = (struct qenc_channel_personality_t *) cp;
	NiFpga_Status status;
	uint8_t cnfg_value;
	uint8_t mask = encoder_enable | encoder_signal_mode;
	uint8_t settings = encoder_enabled | encoder_step_direction;

	status = NiFpga_ReadU8(myrio_session, qcp->bank->cnfg, &cnfg_value);
	MyRio_ReturnStatusIfNotSuccess(status, "Could not read from the encoder configure register!");

	cnfg_value = cnfg_value & ~mask;
	cnfg_value = cnfg_value | settings;

	status = NiFpga_WriteU8(myrio_session, qcp->bank->cnfg, cnfg_value);
	MyRio_ReturnStatusIfNotSuccess(status, "Could not write to the encoder configure register!");

	return status_ok;
}

status_t quadrature_encoder_init(struct quadrature_encoder_t *qe, uint8_t encoder_num) {
	const struct qenc_channel_personality_t *channel_personality =
			&qenc_channel_personalities[encoder_num];
	status_t status;

	status = channel_register_setup((struct channel_personality_t *) channel_personality, quadrature_encoder_setup);
	if (status != status_ok) {
		return status;
	}

	qe->channel_personality = channel_personality;
	qe->value = 0;
	return status_ok;
}

status_t quadrature_encoder_update(struct quadrature_encoder_t *qe) {
	return NiFpga_ReadU32(myrio_session, qe->channel_personality->bank->cntr, &qe->value);
}



