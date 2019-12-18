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
struct TYPE_4__ {int /*<<< orphan*/  (* video_surface_put_bits_y_cb_cr ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const* const*,int /*<<< orphan*/  const*) ;} ;
struct TYPE_5__ {TYPE_1__ vt; } ;
typedef  TYPE_2__ vdp_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  VdpYCbCrFormat ;
typedef  int /*<<< orphan*/  VdpVideoSurface ;
typedef  int /*<<< orphan*/  VdpStatus ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FUNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VIDEO_SURFACE_PUT_BITS_Y_CB_CR ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const* const*,int /*<<< orphan*/  const*) ; 

VdpStatus vdp_video_surface_put_bits_y_cb_cr(const vdp_t *vdp,
    VdpVideoSurface surface, VdpYCbCrFormat fmt,
    const void *const *data, uint32_t const *pitches)
{
    CHECK_FUNC(VIDEO_SURFACE_PUT_BITS_Y_CB_CR);
    return vdp->vt.video_surface_put_bits_y_cb_cr(surface, fmt, data, pitches);
}