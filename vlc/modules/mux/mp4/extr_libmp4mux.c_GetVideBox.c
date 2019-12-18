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
typedef  char uint8_t ;
struct TYPE_12__ {int i_visible_width; int i_visible_height; } ;
struct TYPE_10__ {int i_codec; char* p_extra; size_t i_extra; TYPE_5__ video; } ;
struct TYPE_9__ {size_t i_data; char* p_data; } ;
struct TYPE_11__ {TYPE_2__ fmt; TYPE_1__ sample_priv; } ;
typedef  TYPE_3__ mp4mux_trackinfo_t ;
typedef  int /*<<< orphan*/  bo_t ;

/* Variables and functions */
 int /*<<< orphan*/  GetAvcCTag (char const*,size_t) ; 
 int /*<<< orphan*/  GetClli (TYPE_5__*) ; 
 int /*<<< orphan*/  GetColrBox (TYPE_5__*,int) ; 
 int /*<<< orphan*/  GetD263Tag () ; 
 int /*<<< orphan*/  GetESDS (TYPE_3__*) ; 
 int /*<<< orphan*/  GetHvcCTag (char const*,size_t,int) ; 
 int /*<<< orphan*/  GetMdcv (TYPE_5__*) ; 
 int /*<<< orphan*/  GetSVQ3Tag (char const*,size_t) ; 
 int /*<<< orphan*/  GetxxxxTag (char const*,size_t,char*) ; 
#define  VLC_CODEC_AV1 139 
#define  VLC_CODEC_H263 138 
#define  VLC_CODEC_H264 137 
#define  VLC_CODEC_HEVC 136 
#define  VLC_CODEC_MJPG 135 
#define  VLC_CODEC_MP4V 134 
#define  VLC_CODEC_MPGV 133 
#define  VLC_CODEC_SVQ1 132 
#define  VLC_CODEC_SVQ3 131 
#define  VLC_CODEC_VC1 130 
#define  VLC_CODEC_YUYV 129 
#define  VLC_CODEC_YV12 128 
 int /*<<< orphan*/  VLC_UNUSED (int) ; 
 int /*<<< orphan*/  bo_add_16be (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bo_add_32be (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bo_add_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bo_add_mem (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  box_gather (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * box_new (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  vlc_fourcc_to_char (int,char*) ; 

__attribute__((used)) static bo_t *GetVideBox(vlc_object_t *p_obj, mp4mux_trackinfo_t *p_track, bool b_mov)
{
    VLC_UNUSED(p_obj);
    VLC_UNUSED(b_mov);

    char fcc[4];

    switch(p_track->fmt.i_codec)
    {
    case VLC_CODEC_MP4V:
    case VLC_CODEC_MPGV: memcpy(fcc, "mp4v", 4); break;
    case VLC_CODEC_MJPG: memcpy(fcc, "mjpa", 4); break;
    case VLC_CODEC_SVQ1: memcpy(fcc, "SVQ1", 4); break;
    case VLC_CODEC_SVQ3: memcpy(fcc, "SVQ3", 4); break;
    case VLC_CODEC_H263: memcpy(fcc, "s263", 4); break;
    case VLC_CODEC_H264: memcpy(fcc, "avc1", 4); break;
    case VLC_CODEC_VC1 : memcpy(fcc, "vc-1", 4); break;
    /* FIXME: find a way to know if no non-VCL units are in the stream (->hvc1)
     * see 14496-15 8.4.1.1.1 */
    case VLC_CODEC_HEVC: memcpy(fcc, "hev1", 4); break;
    case VLC_CODEC_YV12: memcpy(fcc, "yv12", 4); break;
    case VLC_CODEC_YUYV: memcpy(fcc, "yuy2", 4); break;
    default:
        vlc_fourcc_to_char(p_track->fmt.i_codec, fcc);
        break;
    }

    bo_t *vide = box_new(fcc);
    if(!vide)
        return NULL;
    for (int i = 0; i < 6; i++)
        bo_add_8(vide, 0);        // reserved;
    bo_add_16be(vide, 1);         // data-reference-index

    bo_add_16be(vide, 0);         // predefined;
    bo_add_16be(vide, 0);         // reserved;
    for (int i = 0; i < 3; i++)
        bo_add_32be(vide, 0);     // predefined;

    bo_add_16be(vide, p_track->fmt.video.i_visible_width);  // i_width
    bo_add_16be(vide, p_track->fmt.video.i_visible_height); // i_height

    bo_add_32be(vide, 0x00480000);                // h 72dpi
    bo_add_32be(vide, 0x00480000);                // v 72dpi

    bo_add_32be(vide, 0);         // data size, always 0
    bo_add_16be(vide, 1);         // frames count per sample

    // compressor name;
    uint8_t compressor_name[32] = {0};
    switch (p_track->fmt.i_codec)
    {
        case VLC_CODEC_AV1:
            memcpy(compressor_name, "\012AOM Coding", 11);
            break;
        default:
            break;
    }
    bo_add_mem(vide, 32, compressor_name);

    bo_add_16be(vide, 0x18);      // depth
    bo_add_16be(vide, 0xffff);    // predefined

    /* codec specific extradata */
    const uint8_t *p_extradata = p_track->fmt.p_extra;
    size_t i_extradata = p_track->fmt.i_extra;
    if(p_track->sample_priv.i_data)
    {
        p_extradata = p_track->sample_priv.p_data;
        i_extradata = p_track->sample_priv.i_data;
    }

    /* add an ES Descriptor */
    switch(p_track->fmt.i_codec)
    {
    case VLC_CODEC_AV1:
        box_gather(vide, GetxxxxTag(p_extradata, i_extradata, "av1C"));
        box_gather(vide, GetColrBox(&p_track->fmt.video, b_mov));
        break;

    case VLC_CODEC_MP4V:
    case VLC_CODEC_MPGV:
        box_gather(vide, GetESDS(p_track));
        break;

    case VLC_CODEC_H263:
        box_gather(vide, GetD263Tag());
        break;

    case VLC_CODEC_SVQ3:
        box_gather(vide, GetSVQ3Tag(p_extradata, i_extradata));
        break;

    case VLC_CODEC_H264:
        box_gather(vide, GetAvcCTag(p_extradata, i_extradata));
        break;

    case VLC_CODEC_VC1:
        box_gather(vide, GetxxxxTag(p_extradata, i_extradata, "dvc1"));
            break;

    case VLC_CODEC_HEVC:
        /* Write HvcC without forcing VPS/SPS/PPS/SEI array_completeness */
        box_gather(vide, GetHvcCTag(p_extradata, i_extradata, false));
        break;
    }

    box_gather(vide, GetMdcv(&p_track->fmt.video));
    box_gather(vide, GetClli(&p_track->fmt.video));

    return vide;
}