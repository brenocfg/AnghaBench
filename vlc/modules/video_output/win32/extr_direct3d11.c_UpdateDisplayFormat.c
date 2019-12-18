#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ vout_display_t ;
struct TYPE_14__ {scalar_t__ color; scalar_t__ transfer; scalar_t__ primaries; scalar_t__ b_full_range; scalar_t__ luminance_peak; TYPE_5__ const* pixelFormat; int /*<<< orphan*/  member_0; } ;
struct TYPE_12__ {TYPE_4__ display; } ;
typedef  TYPE_2__ vout_display_sys_t ;
typedef  scalar_t__ video_transfer_func_t ;
typedef  int /*<<< orphan*/  video_format_t ;
typedef  scalar_t__ video_color_space_t ;
typedef  scalar_t__ video_color_primaries_t ;
struct TYPE_13__ {int transfer; scalar_t__ full_range; scalar_t__ primaries; scalar_t__ colorspace; scalar_t__ surface_format; } ;
typedef  TYPE_3__ libvlc_video_output_cfg_t ;
typedef  TYPE_4__ display_info_t ;
struct TYPE_15__ {scalar_t__ formatTexture; int /*<<< orphan*/  fourcc; int /*<<< orphan*/ * name; } ;
typedef  TYPE_5__ d3d_format_t ;
typedef  scalar_t__ DXGI_FORMAT ;

/* Variables and functions */
 void* DEFAULT_SRGB_BRIGHTNESS ; 
 scalar_t__ Direct3D11CreateFormatResources (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 TYPE_5__* GetRenderFormatList () ; 
 scalar_t__ MAX_PQ_BRIGHTNESS ; 
#define  TRANSFER_FUNC_LINEAR 130 
#define  TRANSFER_FUNC_SMPTE_ST2084 129 
#define  TRANSFER_FUNC_SRGB 128 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  is_d3d11_opaque (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int UpdateDisplayFormat(vout_display_t *vd, libvlc_video_output_cfg_t *out,
                               const video_format_t *input_fmt)
{
    vout_display_sys_t *sys = vd->sys;
    display_info_t new_display = { 0 };

    for (const d3d_format_t *output_format = GetRenderFormatList();
         output_format->name != NULL; ++output_format)
    {
        if (output_format->formatTexture == (DXGI_FORMAT)out->surface_format &&
            !is_d3d11_opaque(output_format->fourcc))
        {
            new_display.pixelFormat = output_format;
            break;
        }
    }
    if (unlikely(new_display.pixelFormat == NULL))
    {
        msg_Err(vd, "Could not find the output format.");
        return VLC_EGENERIC;
    }

    new_display.color     = (video_color_space_t)     out->colorspace;
    new_display.transfer  = (video_transfer_func_t)   out->transfer;
    new_display.primaries = (video_color_primaries_t) out->primaries;
    new_display.b_full_range = out->full_range;

    /* guestimate the display peak luminance */
    switch (out->transfer)
    {
    case TRANSFER_FUNC_LINEAR:
    case TRANSFER_FUNC_SRGB:
        new_display.luminance_peak = DEFAULT_SRGB_BRIGHTNESS;
        break;
    case TRANSFER_FUNC_SMPTE_ST2084:
        new_display.luminance_peak = MAX_PQ_BRIGHTNESS;
        break;
    default:
        new_display.luminance_peak = DEFAULT_SRGB_BRIGHTNESS;
        break;
    }

    if ( sys->display.pixelFormat == NULL ||
         ( sys->display.pixelFormat    != new_display.pixelFormat ||
           sys->display.luminance_peak != new_display.luminance_peak ||
           sys->display.color          != new_display.color ||
           sys->display.transfer       != new_display.transfer ||
           sys->display.primaries      != new_display.primaries ||
           sys->display.b_full_range   != new_display.b_full_range ))
    {
        sys->display = new_display;
        /* TODO release the pixel shaders if the format changed */
        if (Direct3D11CreateFormatResources(vd, input_fmt)) {
            msg_Err(vd, "Failed to allocate format resources");
            return VLC_EGENERIC;
        }
    }

    return VLC_SUCCESS;
}