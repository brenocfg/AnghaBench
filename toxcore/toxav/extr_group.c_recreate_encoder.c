#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * audio_encoder; int /*<<< orphan*/  audio_bitrate; int /*<<< orphan*/  audio_channels; int /*<<< orphan*/  audio_sample_rate; } ;
typedef  TYPE_1__ Group_AV ;

/* Variables and functions */
 int /*<<< orphan*/  LOGGER_ERROR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPUS_APPLICATION_AUDIO ; 
 int OPUS_OK ; 
 int /*<<< orphan*/  OPUS_SET_BITRATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPUS_SET_COMPLEXITY (int) ; 
 int /*<<< orphan*/ * opus_encoder_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int opus_encoder_ctl (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opus_encoder_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opus_strerror (int) ; 

__attribute__((used)) static int recreate_encoder(Group_AV *group_av)
{
    if (group_av->audio_encoder) {
        opus_encoder_destroy(group_av->audio_encoder);
        group_av->audio_encoder = NULL;
    }

    int rc = OPUS_OK;
    group_av->audio_encoder = opus_encoder_create(group_av->audio_sample_rate, group_av->audio_channels,
                              OPUS_APPLICATION_AUDIO, &rc);

    if (rc != OPUS_OK) {
        LOGGER_ERROR("Error while starting audio encoder: %s", opus_strerror(rc));
        group_av->audio_encoder = NULL;
        return -1;
    }

    rc = opus_encoder_ctl(group_av->audio_encoder, OPUS_SET_BITRATE(group_av->audio_bitrate));

    if (rc != OPUS_OK) {
        LOGGER_ERROR("Error while setting encoder ctl: %s", opus_strerror(rc));
        opus_encoder_destroy(group_av->audio_encoder);
        group_av->audio_encoder = NULL;
        return -1;
    }

    rc = opus_encoder_ctl(group_av->audio_encoder, OPUS_SET_COMPLEXITY(10));

    if (rc != OPUS_OK) {
        LOGGER_ERROR("Error while setting encoder ctl: %s", opus_strerror(rc));
        opus_encoder_destroy(group_av->audio_encoder);
        group_av->audio_encoder = NULL;
        return -1;
    }

    return 0;
}