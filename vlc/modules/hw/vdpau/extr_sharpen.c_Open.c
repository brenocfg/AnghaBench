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
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  vdp_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_13__ {int /*<<< orphan*/  video; } ;
struct TYPE_16__ {scalar_t__ i_chroma; } ;
struct TYPE_12__ {TYPE_5__ video; } ;
struct TYPE_14__ {int /*<<< orphan*/  p_cfg; TYPE_4__* p_sys; int /*<<< orphan*/  pf_video_filter; TYPE_2__ fmt_out; TYPE_1__ fmt_in; } ;
typedef  TYPE_3__ filter_t ;
struct TYPE_15__ {int /*<<< orphan*/  sigma; } ;
typedef  TYPE_4__ filter_sys_t ;
typedef  scalar_t__ VdpStatus ;
typedef  int /*<<< orphan*/  VdpDevice ;
typedef  scalar_t__ VdpBool ;

/* Variables and functions */
 int /*<<< orphan*/  Sharpen ; 
 int /*<<< orphan*/  SharpenCallback ; 
 scalar_t__ VDP_FALSE ; 
 scalar_t__ VDP_STATUS_OK ; 
 scalar_t__ VDP_TRUE ; 
 int /*<<< orphan*/  VDP_VIDEO_MIXER_FEATURE_SHARPNESS ; 
 scalar_t__ VLC_CODEC_VDPAU_VIDEO_420 ; 
 scalar_t__ VLC_CODEC_VDPAU_VIDEO_422 ; 
 scalar_t__ VLC_CODEC_VDPAU_VIDEO_444 ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  atomic_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_ChainParse (TYPE_3__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* malloc (int) ; 
 int /*<<< orphan*/  msg_Err (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  options ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_AddCallback (TYPE_3__*,char*,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  var_CreateGetFloatCommand (TYPE_3__*,char*) ; 
 scalar_t__ vdp_get_x11 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vdp_release_x11 (int /*<<< orphan*/ *) ; 
 scalar_t__ vdp_video_mixer_query_feature_support (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  video_format_IsSimilar (TYPE_5__*,int /*<<< orphan*/ *) ; 
 float vlc_to_vdp_sigma (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int Open(vlc_object_t *obj)
{
    filter_t *filter = (filter_t *)obj;

    if (filter->fmt_in.video.i_chroma != VLC_CODEC_VDPAU_VIDEO_420
     && filter->fmt_in.video.i_chroma != VLC_CODEC_VDPAU_VIDEO_422
     && filter->fmt_in.video.i_chroma != VLC_CODEC_VDPAU_VIDEO_444)
        return VLC_EGENERIC;
    if (!video_format_IsSimilar(&filter->fmt_in.video, &filter->fmt_out.video))
        return VLC_EGENERIC;

    /* Check for sharpen support */
    vdp_t *vdp;
    VdpDevice device;
    VdpStatus err;
    VdpBool ok;

    err = vdp_get_x11(NULL, -1, &vdp, &device);
    if (err != VDP_STATUS_OK)
        return VLC_EGENERIC; /* Weird. The decoder should be active... */

    err = vdp_video_mixer_query_feature_support(vdp, device,
                                       VDP_VIDEO_MIXER_FEATURE_SHARPNESS, &ok);
    if (err != VDP_STATUS_OK)
        ok = VDP_FALSE;
    vdp_release_x11(vdp);

    if (ok != VDP_TRUE)
    {
        msg_Err(filter, "sharpening/blurring not supported by VDPAU device");
        return VLC_EGENERIC;
    }

    /* Initialization */
    filter_sys_t *sys = malloc(sizeof (*sys));
    if (unlikely(sys == NULL))
        return VLC_ENOMEM;

    filter->pf_video_filter = Sharpen;
    filter->p_sys = sys;

    config_ChainParse(filter, "sharpen-", options, filter->p_cfg);
    var_AddCallback(filter, "sharpen-sigma", SharpenCallback, sys);

    union { uint32_t u; float f; } u;
    u.f = vlc_to_vdp_sigma(var_CreateGetFloatCommand(filter, "sharpen-sigma"));
    atomic_init(&sys->sigma, u.u);

    return VLC_SUCCESS;
}