#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct RTPMessage {scalar_t__ len; int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_5__ {int /*<<< orphan*/  second; int /*<<< orphan*/  (* first ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {int lp_sampling_rate; int lp_frame_duration; int /*<<< orphan*/  queue_mutex; TYPE_1__ acb; int /*<<< orphan*/  lp_channel_count; int /*<<< orphan*/  friend_number; int /*<<< orphan*/  av; int /*<<< orphan*/  decoder; int /*<<< orphan*/  j_buf; } ;
typedef  TYPE_2__ ACSession ;

/* Variables and functions */
 int /*<<< orphan*/  LOGGER_DEBUG (char*) ; 
 int /*<<< orphan*/  LOGGER_WARNING (char*,...) ; 
 int /*<<< orphan*/  free (struct RTPMessage*) ; 
 struct RTPMessage* jbuf_read (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ *,int) ; 
 int ntohl (int) ; 
 int opus_decode (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  opus_packet_get_nb_channels (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opus_strerror (int) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reconfigure_audio_decoder (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void ac_iterate(ACSession *ac)
{
    if (!ac)
        return;

    /* TODO fix this and jitter buffering */

    /* Enough space for the maximum frame size (120 ms 48 KHz stereo audio) */
    int16_t tmp[5760 * 2];

    struct RTPMessage *msg;
    int rc = 0;

    pthread_mutex_lock(ac->queue_mutex);

    while ((msg = jbuf_read(ac->j_buf, &rc)) || rc == 2) {
        pthread_mutex_unlock(ac->queue_mutex);

        if (rc == 2) {
            LOGGER_DEBUG("OPUS correction");
            int fs = (ac->lp_sampling_rate * ac->lp_frame_duration) / 1000;
            rc = opus_decode(ac->decoder, NULL, 0, tmp, fs, 1);
        } else {
            /* Get values from packet and decode. */
            /* NOTE: This didn't work very well
            rc = convert_bw_to_sampling_rate(opus_packet_get_bandwidth(msg->data));
            if (rc != -1) {
                cs->last_packet_sampling_rate = rc;
            } else {
                LOGGER_WARNING("Failed to load packet values!");
                rtp_free_msg(msg);
                continue;
            }*/


            /* Pick up sampling rate from packet */
            memcpy(&ac->lp_sampling_rate, msg->data, 4);
            ac->lp_sampling_rate = ntohl(ac->lp_sampling_rate);

            ac->lp_channel_count = opus_packet_get_nb_channels(msg->data + 4);

            /** NOTE: even though OPUS supports decoding mono frames with stereo decoder and vice versa,
              * it didn't work quite well.
              */
            if (!reconfigure_audio_decoder(ac, ac->lp_sampling_rate, ac->lp_channel_count)) {
                LOGGER_WARNING("Failed to reconfigure decoder!");
                free(msg);
                continue;
            }

            rc = opus_decode(ac->decoder, msg->data + 4, msg->len - 4, tmp, 5760, 0);
            free(msg);
        }

        if (rc < 0) {
            LOGGER_WARNING("Decoding error: %s", opus_strerror(rc));
        } else if (ac->acb.first) {
            ac->lp_frame_duration = (rc * 1000) / ac->lp_sampling_rate;

            ac->acb.first(ac->av, ac->friend_number, tmp, rc, ac->lp_channel_count,
                          ac->lp_sampling_rate, ac->acb.second);
        }

        return;
    }

    pthread_mutex_unlock(ac->queue_mutex);
}