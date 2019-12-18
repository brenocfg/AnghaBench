#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  scalar_t__ vlc_fourcc_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_9__ {int i_channels; int i_bitspersample; int i_rate; int i_frame_length; } ;
struct TYPE_12__ {scalar_t__ i_codec; size_t i_extra; int /*<<< orphan*/ * p_extra; TYPE_1__ audio; } ;
struct TYPE_10__ {size_t i_data; int /*<<< orphan*/ * p_data; } ;
struct TYPE_11__ {TYPE_5__ fmt; TYPE_2__ sample_priv; } ;
typedef  TYPE_3__ mp4mux_trackinfo_t ;
typedef  int /*<<< orphan*/  bo_t ;

/* Variables and functions */
 int /*<<< orphan*/ * GetDamrTag (TYPE_5__*) ; 
 int /*<<< orphan*/ * GetESDS (TYPE_3__*) ; 
 int /*<<< orphan*/ * GetWaveFormatExTag (TYPE_5__*,char*) ; 
 int /*<<< orphan*/ * GetWaveTag (TYPE_3__*) ; 
 int /*<<< orphan*/ * GetxxxxTag (int /*<<< orphan*/  const*,size_t,char*) ; 
 scalar_t__ VLC_CODEC_A52 ; 
 scalar_t__ VLC_CODEC_AMR_NB ; 
 scalar_t__ VLC_CODEC_DTS ; 
 scalar_t__ VLC_CODEC_EAC3 ; 
 scalar_t__ VLC_CODEC_MP3 ; 
 scalar_t__ VLC_CODEC_MP4A ; 
 scalar_t__ VLC_CODEC_MPGA ; 
 scalar_t__ VLC_CODEC_WMAP ; 
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bo_add_16be (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bo_add_32be (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bo_add_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  box_gather (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * box_new (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  vlc_fourcc_to_char (scalar_t__,char*) ; 

__attribute__((used)) static bo_t *GetSounBox(vlc_object_t *p_obj, mp4mux_trackinfo_t *p_track, bool b_mov)
{
    VLC_UNUSED(p_obj);

    bool b_descr = true;
    vlc_fourcc_t codec = p_track->fmt.i_codec;
    char fcc[4];

    if (codec == VLC_CODEC_MPGA ||
        codec == VLC_CODEC_MP3) {
        if (b_mov) {
            b_descr = false;
            memcpy(fcc, ".mp3", 4);
        } else
            memcpy(fcc, "mp4a", 4);
    } else if (codec == VLC_CODEC_A52) {
        memcpy(fcc, "ac-3", 4);
    } else if (codec == VLC_CODEC_EAC3) {
        memcpy(fcc, "ec-3", 4);
    } else if (codec == VLC_CODEC_DTS) {
        memcpy(fcc, "DTS ", 4);
    } else if (codec == VLC_CODEC_WMAP) {
        memcpy(fcc, "wma ", 4);
    } else
        vlc_fourcc_to_char(codec, fcc);

    bo_t *soun = box_new(fcc);
    if(!soun)
        return NULL;
    for (int i = 0; i < 6; i++)
        bo_add_8(soun, 0);        // reserved;
    bo_add_16be(soun, 1);         // data-reference-index

    /* SoundDescription */
    if (b_mov && codec == VLC_CODEC_MP4A)
        bo_add_16be(soun, 1);     // version 1;
    else
        bo_add_16be(soun, 0);     // version 0;
    bo_add_16be(soun, 0);         // revision level (0)
    bo_add_32be(soun, 0);         // vendor
    // channel-count
    bo_add_16be(soun, p_track->fmt.audio.i_channels);
    // sample size
    bo_add_16be(soun, p_track->fmt.audio.i_bitspersample ?
                 p_track->fmt.audio.i_bitspersample : 16);
    bo_add_16be(soun, -2);        // compression id
    bo_add_16be(soun, 0);         // packet size (0)
    bo_add_16be(soun, p_track->fmt.audio.i_rate); // sampleratehi
    bo_add_16be(soun, 0);                             // sampleratelo

    /* Extended data for SoundDescription V1 */
    if (b_mov && p_track->fmt.i_codec == VLC_CODEC_MP4A) {
        /* samples per packet */
        bo_add_32be(soun, p_track->fmt.audio.i_frame_length);
        bo_add_32be(soun, 1536); /* bytes per packet */
        bo_add_32be(soun, 2);    /* bytes per frame */
        /* bytes per sample */
        bo_add_32be(soun, 2 /*p_fmt->audio.i_bitspersample/8 */);
    }

    /* Add an ES Descriptor */
    if (b_descr) {
        bo_t *box;

        /* codec specific extradata */
        const uint8_t *p_extradata = p_track->fmt.p_extra;
        size_t i_extradata = p_track->fmt.i_extra;
        if(p_track->sample_priv.i_data)
        {
            p_extradata = p_track->sample_priv.p_data;
            i_extradata = p_track->sample_priv.i_data;
        }

        if (b_mov && codec == VLC_CODEC_MP4A)
            box = GetWaveTag(p_track);
        else if (codec == VLC_CODEC_AMR_NB)
            box = GetDamrTag(&p_track->fmt);
        else if (codec == VLC_CODEC_A52 && i_extradata >= 3)
            box = GetxxxxTag(p_extradata, i_extradata, "dac3");
        else if (codec == VLC_CODEC_EAC3 && i_extradata >= 5)
            box = GetxxxxTag(p_extradata, i_extradata, "dec3");
        else if (codec == VLC_CODEC_WMAP)
            box = GetWaveFormatExTag(&p_track->fmt, "wfex");
        else
            box = GetESDS(p_track);

        if (box)
            box_gather(soun, box);
    }

    return soun;
}