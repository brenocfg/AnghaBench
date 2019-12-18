#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_13__ {int i_frame_rate; } ;
struct TYPE_9__ {TYPE_6__ video; } ;
struct TYPE_12__ {scalar_t__ i_chroma; } ;
struct TYPE_8__ {TYPE_5__ video; } ;
struct TYPE_10__ {TYPE_2__ fmt_out; TYPE_4__* p_sys; int /*<<< orphan*/  pf_video_filter; TYPE_1__ fmt_in; } ;
typedef  TYPE_3__ filter_t ;
struct TYPE_11__ {int /*<<< orphan*/  last_pts; } ;
typedef  TYPE_4__ filter_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  Deinterlace ; 
 scalar_t__ VLC_CODEC_VDPAU_VIDEO_420 ; 
 scalar_t__ VLC_CODEC_VDPAU_VIDEO_422 ; 
 scalar_t__ VLC_CODEC_VDPAU_VIDEO_444 ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_TICK_INVALID ; 
 TYPE_4__* malloc (int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_format_IsSimilar (TYPE_5__*,TYPE_6__*) ; 

__attribute__((used)) static int Open(vlc_object_t *obj)
{
    filter_t *filter = (filter_t *)obj;

    if (filter->fmt_in.video.i_chroma != VLC_CODEC_VDPAU_VIDEO_420
     && filter->fmt_in.video.i_chroma != VLC_CODEC_VDPAU_VIDEO_422
     && filter->fmt_in.video.i_chroma != VLC_CODEC_VDPAU_VIDEO_444)
        return VLC_EGENERIC;
    if (!video_format_IsSimilar(&filter->fmt_in.video, &filter->fmt_out.video))
        return VLC_EGENERIC;

    filter_sys_t *sys = malloc(sizeof (*sys));
    if (unlikely(sys == NULL))
        return VLC_ENOMEM;

    /* NOTE: Only weave and bob are mandatory for the hardware to implement.
     * The other modes and IVTC should be checked. */

    sys->last_pts = VLC_TICK_INVALID;

    filter->pf_video_filter = Deinterlace;
    filter->p_sys = sys;
    filter->fmt_out.video.i_frame_rate *= 2;
    return VLC_SUCCESS;
}