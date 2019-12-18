#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  map ;
struct TYPE_11__ {int i_rate; scalar_t__ i_channels; } ;
struct TYPE_12__ {int* p_extra; int i_extra; TYPE_1__ audio; } ;
typedef  TYPE_2__ es_format_t ;
typedef  int /*<<< orphan*/  demux_t ;
struct TYPE_13__ {int i_left; } ;
typedef  TYPE_3__ bs_t ;
struct TYPE_14__ {unsigned char* stream_map; int input_sample_rate; int nb_coupled; int nb_streams; int channel_mapping; scalar_t__ channels; scalar_t__ preskip; } ;
typedef  TYPE_4__ OpusHeader ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_ES ; 
 int /*<<< orphan*/  VLC_CODEC_OPUS ; 
 int /*<<< orphan*/  bs_init (TYPE_3__*,int*,size_t) ; 
 int bs_read (TYPE_3__*,int) ; 
 int /*<<< orphan*/  es_format_Change (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,...) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  opus_prepare_header (int,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  opus_write_header (int**,int*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int vlc_ceil_log2 (int) ; 

__attribute__((used)) static void OpusSetup(demux_t *demux, uint8_t *p, size_t len, es_format_t *p_fmt)
{
    OpusHeader h;

    /* default mapping */
    static const unsigned char map[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
    memcpy(h.stream_map, map, sizeof(map));

    uint8_t mapping;
    int csc;
    int channels = 0;
    int stream_count = 0;
    int ccc = p[1]; // channel_config_code
    if (ccc <= 8) {
        channels = ccc;
        if (channels)
            mapping = channels > 2;
        else {
            mapping = 255;
            channels = 2; // dual mono
        }
        static const uint8_t p_csc[8] = { 0, 1, 1, 2, 2, 2, 3, 3 };
        csc = p_csc[channels - 1];
        stream_count = channels - csc;

        static const uint8_t maps[6][7] = {
            { 2,1 },
            { 1,2,3 },
            { 4,1,2,3 },
            { 4,1,2,3,5 },
            { 4,1,2,3,5,6 },
            { 6,1,2,3,4,5,7 },
        };
        if (channels > 2)
            memcpy(&h.stream_map[1], maps[channels-3], channels - 1);
    } else if (ccc == 0x81) {
        if (len < 4)
            goto explicit_config_too_short;

        channels = p[2];
        mapping = p[3];
        csc = 0;
        if (mapping) {
            bs_t s;
            bs_init(&s, &p[4], len - 4);
            stream_count = 1;
            if (channels) {
                int bits = vlc_ceil_log2(channels);
                if (s.i_left < bits)
                    goto explicit_config_too_short;
                stream_count = bs_read(&s, bits) + 1;
                bits = vlc_ceil_log2(stream_count + 1);
                if (s.i_left < bits)
                    goto explicit_config_too_short;
                csc = bs_read(&s, bits);
            }
            int channel_bits = vlc_ceil_log2(stream_count + csc + 1);
            if (s.i_left < channels * channel_bits)
                goto explicit_config_too_short;

            unsigned char silence = (1U << (stream_count + csc + 1)) - 1;
            for (int i = 0; i < channels; i++) {
                unsigned char m = bs_read(&s, channel_bits);
                if (m == silence)
                    m = 0xff;
                h.stream_map[i] = m;
            }
        }
    } else if (ccc >= 0x80 && ccc <= 0x88) {
        channels = ccc - 0x80;
        if (channels)
            mapping = 1;
        else {
            mapping = 255;
            channels = 2; // dual mono
        }
        csc = 0;
        stream_count = channels;
    } else {
        msg_Err(demux, "Opus channel configuration 0x%.2x is reserved", ccc);
    }

    if (!channels) {
        msg_Err(demux, "Opus channel configuration 0x%.2x not supported yet", p[1]);
        return;
    }

    opus_prepare_header(channels, 0, &h);
    h.preskip = 0;
    h.input_sample_rate = 48000;
    h.nb_coupled = csc;
    h.nb_streams = channels - csc;
    h.channel_mapping = mapping;

    if (h.channels) {
        uint8_t *p_extra = NULL;
        int i_extra = 0;
        opus_write_header(&p_extra, &i_extra, &h, NULL /* FIXME */);
        if (p_extra) {
            es_format_Change(p_fmt, AUDIO_ES, VLC_CODEC_OPUS);
            p_fmt->p_extra = p_extra;
            p_fmt->i_extra = i_extra;
            p_fmt->audio.i_channels = h.channels;
            p_fmt->audio.i_rate = 48000;
        }
    }

    return;

explicit_config_too_short:
    msg_Err(demux, "Opus descriptor too short");
}