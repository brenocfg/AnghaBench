#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  context; } ;
typedef  TYPE_2__ vlc_vdp_video_field_t ;
typedef  int /*<<< orphan*/  vdp_t ;
struct TYPE_6__ {scalar_t__ i_chroma; } ;
struct TYPE_8__ {int /*<<< orphan*/ * context; TYPE_1__ format; } ;
typedef  TYPE_3__ picture_t ;
typedef  int /*<<< orphan*/  VdpVideoSurface ;
typedef  int /*<<< orphan*/  VdpStatus ;

/* Variables and functions */
 int /*<<< orphan*/  VDP_STATUS_OK ; 
 int /*<<< orphan*/  VDP_STATUS_RESOURCES ; 
 scalar_t__ VLC_CODEC_VDPAU_VIDEO_420 ; 
 scalar_t__ VLC_CODEC_VDPAU_VIDEO_422 ; 
 scalar_t__ VLC_CODEC_VDPAU_VIDEO_444 ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 TYPE_2__* vlc_vdp_video_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

VdpStatus vlc_vdp_video_attach(vdp_t *vdp, VdpVideoSurface surface,
                               picture_t *pic)
{
    vlc_vdp_video_field_t *field = vlc_vdp_video_create(vdp, surface);
    if (unlikely(field == NULL))
        return VDP_STATUS_RESOURCES;

    assert(pic->format.i_chroma == VLC_CODEC_VDPAU_VIDEO_420
        || pic->format.i_chroma == VLC_CODEC_VDPAU_VIDEO_422
        || pic->format.i_chroma == VLC_CODEC_VDPAU_VIDEO_444);
    assert(pic->context == NULL);
    pic->context = &field->context;
    return VDP_STATUS_OK;
}