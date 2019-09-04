#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  length; int /*<<< orphan*/ * data; } ;
typedef  TYPE_2__ int16_t ;
struct TYPE_16__ {int /*<<< orphan*/  userdata; TYPE_1__* g_c; int /*<<< orphan*/  (* audio_data ) (int /*<<< orphan*/ ,int,int,TYPE_2__*,int,int,unsigned int,int /*<<< orphan*/ ) ;} ;
struct TYPE_15__ {int decoder_channels; int last_packet_samples; int /*<<< orphan*/ * audio_decoder; int /*<<< orphan*/  buffer; } ;
struct TYPE_13__ {int /*<<< orphan*/  m; } ;
typedef  TYPE_3__ Group_Peer_AV ;
typedef  TYPE_2__ Group_Audio_Packet ;
typedef  TYPE_5__ Group_AV ;

/* Variables and functions */
 int /*<<< orphan*/  LOGGER_ERROR (char*,int /*<<< orphan*/ ) ; 
 int OPUS_INVALID_PACKET ; 
 int OPUS_OK ; 
 TYPE_2__* dequeue (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 TYPE_2__* malloc (int) ; 
 int opus_decode (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,int,int) ; 
 int /*<<< orphan*/ * opus_decoder_create (unsigned int,int,int*) ; 
 int /*<<< orphan*/  opus_decoder_destroy (int /*<<< orphan*/ *) ; 
 int opus_decoder_get_nb_samples (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int opus_packet_get_nb_channels (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opus_strerror (int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int,TYPE_2__*,int,int,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int decode_audio_packet(Group_AV *group_av, Group_Peer_AV *peer_av, int groupnumber, int friendgroupnumber)
{
    if (!group_av || !peer_av)
        return -1;

    int success;
    Group_Audio_Packet *pk = dequeue(peer_av->buffer, &success);

    if (success == 0)
        return -1;

    int16_t *out_audio = NULL;
    int out_audio_samples = 0;

    unsigned int sample_rate = 48000;

    if (success == 1) {
        int channels = opus_packet_get_nb_channels(pk->data);

        if (channels == OPUS_INVALID_PACKET) {
            free(pk);
            return -1;
        }

        if (channels != 1 && channels != 2) {
            free(pk);
            return -1;
        }

        if (channels != peer_av->decoder_channels) {
            if (peer_av->audio_decoder) {
                opus_decoder_destroy(peer_av->audio_decoder);
                peer_av->audio_decoder = NULL;
            }

            int rc;
            peer_av->audio_decoder = opus_decoder_create(sample_rate, channels, &rc);

            if (rc != OPUS_OK) {
                LOGGER_ERROR("Error while starting audio decoder: %s", opus_strerror(rc));
                free(pk);
                return -1;
            }

            peer_av->decoder_channels = channels;
        }

        int num_samples = opus_decoder_get_nb_samples(peer_av->audio_decoder, pk->data, pk->length);

        out_audio = malloc(num_samples * peer_av->decoder_channels * sizeof(int16_t));

        if (!out_audio) {
            free(pk);
            return -1;
        }

        out_audio_samples = opus_decode(peer_av->audio_decoder, pk->data, pk->length, out_audio, num_samples, 0);
        free(pk);

        if (out_audio_samples <= 0)
            return -1;

        peer_av->last_packet_samples = out_audio_samples;
    } else {
        if (!peer_av->audio_decoder)
            return -1;

        if (!peer_av->last_packet_samples)
            return -1;

        out_audio = malloc(peer_av->last_packet_samples * peer_av->decoder_channels * sizeof(int16_t));

        if (!out_audio) {
            free(pk);
            return -1;
        }

        out_audio_samples = opus_decode(peer_av->audio_decoder, NULL, 0, out_audio, peer_av->last_packet_samples, 1);

        if (out_audio_samples <= 0)
            return -1;

    }

    if (out_audio) {

        if (group_av->audio_data)
            group_av->audio_data(group_av->g_c->m, groupnumber, friendgroupnumber, out_audio, out_audio_samples,
                                 peer_av->decoder_channels, sample_rate, group_av->userdata);

        free(out_audio);
        return 0;
    }

    return -1;
}