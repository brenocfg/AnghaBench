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
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  vdp; int /*<<< orphan*/  surface; } ;
typedef  TYPE_3__ vlc_vdp_video_frame_t ;
struct TYPE_15__ {TYPE_3__* frame; } ;
typedef  TYPE_4__ vlc_vdp_video_field_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_12__ {scalar_t__ i_chroma; } ;
struct TYPE_16__ {int i_planes; TYPE_2__* p; TYPE_1__ format; scalar_t__ context; } ;
typedef  TYPE_5__ picture_t ;
typedef  int /*<<< orphan*/  filter_t ;
typedef  int /*<<< orphan*/  VdpYCbCrFormat ;
typedef  int /*<<< orphan*/  VdpVideoSurface ;
typedef  scalar_t__ VdpStatus ;
struct TYPE_13__ {int /*<<< orphan*/  i_pitch; void* p_pixels; } ;

/* Variables and functions */
 scalar_t__ VDP_STATUS_OK ; 
 scalar_t__ VLC_CODEC_I420 ; 
 scalar_t__ VLC_CODEC_I422 ; 
 scalar_t__ VLC_CODEC_I444 ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  picture_CopyProperties (TYPE_5__*,TYPE_5__*) ; 
 int /*<<< orphan*/  picture_Release (TYPE_5__*) ; 
 int /*<<< orphan*/  vdp_get_error_string (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ vdp_video_surface_get_bits_y_cb_cr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static picture_t *VideoExport(filter_t *filter, picture_t *src, picture_t *dst,
                              VdpYCbCrFormat format)
{
    vlc_vdp_video_field_t *field = (vlc_vdp_video_field_t *)src->context;
    vlc_vdp_video_frame_t *psys = field->frame;
    VdpStatus err;
    VdpVideoSurface surface = psys->surface;
    void *planes[3];
    uint32_t pitches[3];

    picture_CopyProperties(dst, src);

    for (int i = 0; i < dst->i_planes; i++)
    {
        planes[i] = dst->p[i].p_pixels;
        pitches[i] = dst->p[i].i_pitch;
    }
    if (dst->format.i_chroma == VLC_CODEC_I420
     || dst->format.i_chroma == VLC_CODEC_I422
     || dst->format.i_chroma == VLC_CODEC_I444)
    {
        planes[1] = dst->p[2].p_pixels;
        planes[2] = dst->p[1].p_pixels;
        pitches[1] = dst->p[2].i_pitch;
        pitches[2] = dst->p[1].i_pitch;
    }
    err = vdp_video_surface_get_bits_y_cb_cr(psys->vdp, surface, format,
                                             planes, pitches);
    if (err != VDP_STATUS_OK)
    {
        msg_Err(filter, "video %s %s failure: %s", "surface", "export",
                vdp_get_error_string(psys->vdp, err));
        picture_Release(dst);
        dst = NULL;
    }
    picture_Release(src);
    return dst;
}