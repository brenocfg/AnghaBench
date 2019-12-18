#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* output_surface_render_bitmap_surface ) (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {TYPE_1__ vt; } ;
typedef  TYPE_2__ vdp_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  VdpStatus ;
typedef  int /*<<< orphan*/  VdpRect ;
typedef  int /*<<< orphan*/  VdpOutputSurfaceRenderBlendState ;
typedef  int /*<<< orphan*/  VdpOutputSurface ;
typedef  int /*<<< orphan*/  VdpColor ;
typedef  int /*<<< orphan*/  VdpBitmapSurface ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FUNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OUTPUT_SURFACE_RENDER_BITMAP_SURFACE ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

VdpStatus vdp_output_surface_render_bitmap_surface(const vdp_t *vdp,
    VdpOutputSurface dst_surface, const VdpRect *dst_rect,
    VdpBitmapSurface src_surface, const VdpRect *src_rect,
    const VdpColor *colors,
    const VdpOutputSurfaceRenderBlendState *state, uint32_t flags)
{
    CHECK_FUNC(OUTPUT_SURFACE_RENDER_BITMAP_SURFACE);
    return vdp->vt.output_surface_render_bitmap_surface(dst_surface, dst_rect,
        src_surface, src_rect, colors, state, flags);
}