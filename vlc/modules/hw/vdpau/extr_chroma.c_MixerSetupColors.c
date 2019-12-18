#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {float brightness; float contrast; float saturation; float hue; } ;
struct TYPE_14__ {TYPE_3__ procamp; int /*<<< orphan*/  vdp; } ;
typedef  TYPE_4__ vlc_vdp_mixer_t ;
struct TYPE_11__ {int space; int i_height; } ;
struct TYPE_12__ {TYPE_1__ video; } ;
struct TYPE_15__ {TYPE_2__ fmt_in; TYPE_4__* p_sys; } ;
typedef  TYPE_5__ filter_t ;
typedef  scalar_t__ VdpStatus ;
struct TYPE_16__ {float brightness; float contrast; float saturation; float hue; } ;
typedef  TYPE_6__ VdpProcamp ;
typedef  int /*<<< orphan*/  VdpColorStandard ;
typedef  int /*<<< orphan*/  VdpCSCMatrix ;

/* Variables and functions */
#define  COLOR_SPACE_BT601 129 
#define  COLOR_SPACE_BT709 128 
 int /*<<< orphan*/  VDP_COLOR_STANDARD_ITUR_BT_601 ; 
 int /*<<< orphan*/  VDP_COLOR_STANDARD_ITUR_BT_709 ; 
 scalar_t__ VDP_STATUS_OK ; 
 int /*<<< orphan*/  msg_Err (TYPE_5__*,char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ vdp_generate_csc_matrix (int /*<<< orphan*/ ,TYPE_6__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vdp_get_error_string (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static VdpStatus MixerSetupColors(filter_t *filter, const VdpProcamp *procamp,
                                  VdpCSCMatrix *restrict csc)
{
    vlc_vdp_mixer_t *sys = filter->p_sys;
    VdpStatus err;
    /* XXX: add some margin for padding... */
    VdpColorStandard std;

    switch (filter->fmt_in.video.space)
    {
        case COLOR_SPACE_BT601:
            std = VDP_COLOR_STANDARD_ITUR_BT_601;
            break;
        case COLOR_SPACE_BT709:
            std = VDP_COLOR_STANDARD_ITUR_BT_709;
            break;
        default:
            if (filter->fmt_in.video.i_height >= 720)
                std = VDP_COLOR_STANDARD_ITUR_BT_709;
            else
                std = VDP_COLOR_STANDARD_ITUR_BT_601;
    }

    err = vdp_generate_csc_matrix(sys->vdp, procamp, std, csc);
    if (err != VDP_STATUS_OK)
    {
        msg_Err(filter, "video %s failure: %s", "color space matrix",
                vdp_get_error_string(sys->vdp, err));
        return err;
    }

    if (procamp != NULL)
    {
        sys->procamp.brightness = procamp->brightness;
        sys->procamp.contrast = procamp->contrast;
        sys->procamp.saturation = procamp->saturation;
        sys->procamp.hue = procamp->hue;
    }
    else
    {
        sys->procamp.brightness = 0.f;
        sys->procamp.contrast = 1.f;
        sys->procamp.saturation = 1.f;
        sys->procamp.hue = 0.f;
    }
    return VDP_STATUS_OK;
}