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
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  vlc_fourcc_t ;
struct TYPE_3__ {int i_codec; int /*<<< orphan*/  i_extra; } ;
typedef  TYPE_1__ es_format_t ;

/* Variables and functions */
 int /*<<< orphan*/  BRAND_smoo ; 
#define  VLC_CODEC_A52 156 
#define  VLC_CODEC_AMR_NB 155 
#define  VLC_CODEC_AMR_WB 154 
#define  VLC_CODEC_AV1 153 
#define  VLC_CODEC_DTS 152 
#define  VLC_CODEC_EAC3 151 
#define  VLC_CODEC_H263 150 
#define  VLC_CODEC_H264 149 
#define  VLC_CODEC_HEVC 148 
#define  VLC_CODEC_MJPG 147 
#define  VLC_CODEC_MJPGB 146 
#define  VLC_CODEC_MP1V 145 
#define  VLC_CODEC_MP2V 144 
#define  VLC_CODEC_MP3 143 
#define  VLC_CODEC_MP4A 142 
#define  VLC_CODEC_MP4V 141 
#define  VLC_CODEC_MPGA 140 
#define  VLC_CODEC_MPGV 139 
#define  VLC_CODEC_QTXT 138 
#define  VLC_CODEC_SUBT 137 
#define  VLC_CODEC_SVQ1 136 
#define  VLC_CODEC_SVQ3 135 
#define  VLC_CODEC_TTML 134 
#define  VLC_CODEC_TX3G 133 
#define  VLC_CODEC_VC1 132 
#define  VLC_CODEC_WEBVTT 131 
#define  VLC_CODEC_WMAP 130 
#define  VLC_CODEC_YUYV 129 
#define  VLC_CODEC_YV12 128 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*) ; 

bool mp4mux_CanMux(vlc_object_t *p_obj, const es_format_t *p_fmt,
                   vlc_fourcc_t i_brand, bool b_fragmented)
{
    switch(p_fmt->i_codec)
    {
    case VLC_CODEC_A52:
    case VLC_CODEC_DTS:
    case VLC_CODEC_EAC3:
    case VLC_CODEC_MP4A:
    case VLC_CODEC_MP4V:
    case VLC_CODEC_MPGA:
    case VLC_CODEC_MP3:
    case VLC_CODEC_MPGV:
    case VLC_CODEC_MP2V:
    case VLC_CODEC_MP1V:
    case VLC_CODEC_MJPG:
    case VLC_CODEC_MJPGB:
    case VLC_CODEC_SVQ1:
    case VLC_CODEC_SVQ3:
    case VLC_CODEC_H263:
    case VLC_CODEC_AMR_NB:
    case VLC_CODEC_AMR_WB:
    case VLC_CODEC_YV12:
    case VLC_CODEC_YUYV:
    case VLC_CODEC_VC1:
    case VLC_CODEC_WMAP:
    case VLC_CODEC_AV1:
        break;
    case VLC_CODEC_H264:
        if(!p_fmt->i_extra && p_obj)
            msg_Warn(p_obj, "H264 muxing from AnnexB source will set an incorrect default profile");
        break;
    case VLC_CODEC_HEVC:
        if(!p_fmt->i_extra)
        {
            if(p_obj)
                msg_Err(p_obj, "HEVC muxing from AnnexB source is unsupported");
            return false;
        }
        break;
    case VLC_CODEC_SUBT:
        if(p_obj)
            msg_Warn(p_obj, "subtitle track added like in .mov (even when creating .mp4)");
        return !b_fragmented;
    case VLC_CODEC_TTML:
        /* Special case with smooth headers where we need to force frag TTML */
        /* TTML currently not supported in sout, until we can keep original timestamps */
            return i_brand == BRAND_smoo;
    case VLC_CODEC_QTXT:
    case VLC_CODEC_TX3G:
    case VLC_CODEC_WEBVTT:
        return !b_fragmented;
    default:
        return false;
    }
    return true;
}