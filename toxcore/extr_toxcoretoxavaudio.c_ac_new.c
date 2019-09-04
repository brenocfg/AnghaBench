#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  toxav_audio_receive_frame_cb ;
typedef  int /*<<< orphan*/  ToxAV ;
struct TYPE_6__ {void* second; int /*<<< orphan*/ * first; } ;
struct TYPE_7__ {int le_bit_rate; int le_sample_rate; int le_channel_count; int ld_channel_count; int ld_sample_rate; int lp_frame_duration; int lp_sampling_rate; int lp_channel_count; int /*<<< orphan*/  queue_mutex; int /*<<< orphan*/  j_buf; int /*<<< orphan*/  decoder; TYPE_1__ acb; int /*<<< orphan*/  friend_number; int /*<<< orphan*/ * av; scalar_t__ ldrts; int /*<<< orphan*/ * encoder; } ;
typedef  TYPE_2__ ACSession ;

/* Variables and functions */
 int /*<<< orphan*/  LOGGER_ERROR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOGGER_WARNING (char*) ; 
 int OPUS_OK ; 
 TYPE_2__* calloc (int,int) ; 
 int /*<<< orphan*/ * create_audio_encoder (int,int,int) ; 
 scalar_t__ create_recursive_mutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  jbuf_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jbuf_new (int) ; 
 int /*<<< orphan*/  opus_decoder_create (int,int,int*) ; 
 int /*<<< orphan*/  opus_decoder_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opus_strerror (int) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ ) ; 

ACSession *ac_new(ToxAV *av, uint32_t friend_number, toxav_audio_receive_frame_cb *cb, void *cb_data)
{
    ACSession *ac = calloc(sizeof(ACSession), 1);

    if (!ac) {
        LOGGER_WARNING("Allocation failed! Application might misbehave!");
        return NULL;
    }

    if (create_recursive_mutex(ac->queue_mutex) != 0) {
        LOGGER_WARNING("Failed to create recursive mutex!");
        free(ac);
        return NULL;
    }

    int status;
    ac->decoder = opus_decoder_create(48000, 2, &status);

    if (status != OPUS_OK) {
        LOGGER_ERROR("Error while starting audio decoder: %s", opus_strerror(status));
        goto BASE_CLEANUP;
    }

    if (!(ac->j_buf = jbuf_new(3))) {
        LOGGER_WARNING("Jitter buffer creaton failed!");
        opus_decoder_destroy(ac->decoder);
        goto BASE_CLEANUP;
    }

    /* Initialize encoders with default values */
    ac->encoder = create_audio_encoder(48000, 48000, 2);

    if (ac->encoder == NULL)
        goto DECODER_CLEANUP;

    ac->le_bit_rate = 48000;
    ac->le_sample_rate = 48000;
    ac->le_channel_count = 2;

    ac->ld_channel_count = 2;
    ac->ld_sample_rate = 48000;
    ac->ldrts = 0; /* Make it possible to reconfigure straight away */

    /* These need to be set in order to properly
     * do error correction with opus */
    ac->lp_frame_duration = 120;
    ac->lp_sampling_rate = 48000;
    ac->lp_channel_count = 1;

    ac->av = av;
    ac->friend_number = friend_number;
    ac->acb.first = cb;
    ac->acb.second = cb_data;

    return ac;

DECODER_CLEANUP:
    opus_decoder_destroy(ac->decoder);
    jbuf_free(ac->j_buf);
BASE_CLEANUP:
    pthread_mutex_destroy(ac->queue_mutex);
    free(ac);
    return NULL;
}