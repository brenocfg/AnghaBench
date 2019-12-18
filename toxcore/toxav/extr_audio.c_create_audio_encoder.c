#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  OpusEncoder ;

/* Variables and functions */
 int /*<<< orphan*/  LOGGER_ERROR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPUS_APPLICATION_VOIP ; 
 int OPUS_OK ; 
 int /*<<< orphan*/  OPUS_SET_BITRATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPUS_SET_COMPLEXITY (int) ; 
 int /*<<< orphan*/  OPUS_SET_INBAND_FEC (int) ; 
 int /*<<< orphan*/  OPUS_SET_PACKET_LOSS_PERC (int) ; 
 int /*<<< orphan*/ * opus_encoder_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int opus_encoder_ctl (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opus_encoder_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opus_strerror (int) ; 

OpusEncoder *create_audio_encoder (int32_t bit_rate, int32_t sampling_rate, int32_t channel_count)
{
    int status = OPUS_OK;
    OpusEncoder *rc = opus_encoder_create(sampling_rate, channel_count, OPUS_APPLICATION_VOIP, &status);

    if (status != OPUS_OK) {
        LOGGER_ERROR("Error while starting audio encoder: %s", opus_strerror(status));
        return NULL;
    }

    status = opus_encoder_ctl(rc, OPUS_SET_BITRATE(bit_rate));

    if (status != OPUS_OK) {
        LOGGER_ERROR("Error while setting encoder ctl: %s", opus_strerror(status));
        goto FAILURE;
    }

    /* Enable in-band forward error correction in codec */
    status = opus_encoder_ctl(rc, OPUS_SET_INBAND_FEC(1));

    if (status != OPUS_OK) {
        LOGGER_ERROR("Error while setting encoder ctl: %s", opus_strerror(status));
        goto FAILURE;
    }

    /* Make codec resistant to up to 10% packet loss
     * NOTE This could also be adjusted on the fly, rather than hard-coded,
     *      with feedback from the receiving client.
     */
    status = opus_encoder_ctl(rc, OPUS_SET_PACKET_LOSS_PERC(10));

    if (status != OPUS_OK) {
        LOGGER_ERROR("Error while setting encoder ctl: %s", opus_strerror(status));
        goto FAILURE;
    }

    /* Set algorithm to the highest complexity, maximizing compression */
    status = opus_encoder_ctl(rc, OPUS_SET_COMPLEXITY(10));

    if (status != OPUS_OK) {
        LOGGER_ERROR("Error while setting encoder ctl: %s", opus_strerror(status));
        goto FAILURE;
    }

    return rc;

FAILURE:
    opus_encoder_destroy(rc);
    return NULL;
}