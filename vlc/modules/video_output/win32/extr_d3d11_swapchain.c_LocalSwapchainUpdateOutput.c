#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct d3d11_local_swapchain {TYPE_1__* colorspace; TYPE_2__* pixelFormat; } ;
typedef  scalar_t__ libvlc_video_transfer_func_t ;
struct TYPE_7__ {scalar_t__ transfer; scalar_t__ primaries; scalar_t__ colorspace; int /*<<< orphan*/  full_range; int /*<<< orphan*/  surface_format; } ;
typedef  TYPE_3__ libvlc_video_output_cfg_t ;
typedef  int /*<<< orphan*/  libvlc_video_direct3d_cfg_t ;
typedef  scalar_t__ libvlc_video_color_space_t ;
typedef  scalar_t__ libvlc_video_color_primaries_t ;
struct TYPE_6__ {int /*<<< orphan*/  formatTexture; } ;
struct TYPE_5__ {scalar_t__ transfer; scalar_t__ primaries; scalar_t__ color; int /*<<< orphan*/  b_full_range; } ;

/* Variables and functions */
 int /*<<< orphan*/  UpdateSwapchain (struct d3d11_local_swapchain*,int /*<<< orphan*/  const*) ; 

bool LocalSwapchainUpdateOutput( void *opaque, const libvlc_video_direct3d_cfg_t *cfg, libvlc_video_output_cfg_t *out )
{
    struct d3d11_local_swapchain *display = opaque;
    if ( !UpdateSwapchain( display, cfg ) )
        return false;
    out->surface_format = display->pixelFormat->formatTexture;
    out->full_range     = display->colorspace->b_full_range;
    out->colorspace     = (libvlc_video_color_space_t)     display->colorspace->color;
    out->primaries      = (libvlc_video_color_primaries_t) display->colorspace->primaries;
    out->transfer       = (libvlc_video_transfer_func_t)   display->colorspace->transfer;
    return true;
}