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
struct TYPE_3__ {scalar_t__ i_width; scalar_t__ i_height; } ;
typedef  TYPE_1__ video_format_t ;
typedef  int /*<<< orphan*/  vdp_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ VdpStatus ;
typedef  int /*<<< orphan*/  VdpRGBAFormat ;
typedef  int /*<<< orphan*/  VdpDevice ;
typedef  int /*<<< orphan*/  VdpBool ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/  const*) ; 
#define  VDP_RGBA_FORMAT_B10G10R10A2 131 
#define  VDP_RGBA_FORMAT_B8G8R8A8 130 
#define  VDP_RGBA_FORMAT_R10G10B10A2 129 
#define  VDP_RGBA_FORMAT_R8G8B8A8 128 
 scalar_t__ VDP_STATUS_OK ; 
 int VLC_EGENERIC ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  vdp_get_error_string (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ vdp_output_surface_query_capabilities (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static int OutputCheckFormat(vlc_object_t *obj, vdp_t *vdp, VdpDevice dev,
                             const video_format_t *fmt,
                             VdpRGBAFormat *restrict rgb_fmt)
{
    static const VdpRGBAFormat rgb_fmts[] = {
        VDP_RGBA_FORMAT_R10G10B10A2, VDP_RGBA_FORMAT_B10G10R10A2,
        VDP_RGBA_FORMAT_B8G8R8A8, VDP_RGBA_FORMAT_R8G8B8A8,
    };

    for (unsigned i = 0; i < ARRAY_SIZE(rgb_fmts); i++)
    {
        uint32_t w, h;
        VdpBool ok;

        VdpStatus err = vdp_output_surface_query_capabilities(vdp, dev,
                                                     rgb_fmts[i], &ok, &w, &h);
        if (err != VDP_STATUS_OK)
        {
            msg_Err(obj, "%s capabilities query failure: %s", "output surface",
                    vdp_get_error_string(vdp, err));
            continue;
        }

        if (!ok || w < fmt->i_width || h < fmt->i_height)
            continue;

        *rgb_fmt = rgb_fmts[i];
        msg_Dbg(obj, "using RGBA format %u", *rgb_fmt);
        return 0;
    }

    msg_Err(obj, "no supported output surface format");
    return VLC_EGENERIC;
}