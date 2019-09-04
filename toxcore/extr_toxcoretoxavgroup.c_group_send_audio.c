#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  int16_t ;
typedef  int /*<<< orphan*/  encoded ;
struct TYPE_4__ {int audio_channels; unsigned int audio_sample_rate; int audio_bitrate; int /*<<< orphan*/  audio_encoder; } ;
typedef  int /*<<< orphan*/  Group_Chats ;
typedef  TYPE_1__ Group_AV ;

/* Variables and functions */
 TYPE_1__* group_get_object (int /*<<< orphan*/ *,int) ; 
 scalar_t__ opus_encode (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int,int*,int) ; 
 int recreate_encoder (TYPE_1__*) ; 
 int send_audio_packet (int /*<<< orphan*/ *,int,int*,scalar_t__) ; 

int group_send_audio(Group_Chats *g_c, int groupnumber, const int16_t *pcm, unsigned int samples, uint8_t channels,
                     unsigned int sample_rate)
{
    Group_AV *group_av = group_get_object(g_c, groupnumber);

    if (!group_av)
        return -1;

    if (channels != 1 && channels != 2)
        return -1;

    if (sample_rate != 8000 && sample_rate != 12000 && sample_rate != 16000 && sample_rate != 24000 && sample_rate != 48000)
        return -1;

    if (!group_av->audio_encoder || group_av->audio_channels != channels || group_av->audio_sample_rate != sample_rate) {
        group_av->audio_channels = channels;
        group_av->audio_sample_rate = sample_rate;

        if (channels == 1) {
            group_av->audio_bitrate = 32000; //TODO: add way of adjusting bitrate
        } else {
            group_av->audio_bitrate = 64000; //TODO: add way of adjusting bitrate
        }

        if (recreate_encoder(group_av) == -1)
            return -1;
    }

    uint8_t encoded[1024];
    int32_t size = opus_encode(group_av->audio_encoder, pcm, samples, encoded, sizeof(encoded));

    if (size <= 0)
        return -1;

    return send_audio_packet(g_c, groupnumber, encoded, size);
}