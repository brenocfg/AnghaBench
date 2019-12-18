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
struct TYPE_4__ {int /*<<< orphan*/  (* output_surface_put_bits_indexed ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const* const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,void const*) ;} ;
struct TYPE_5__ {TYPE_1__ vt; } ;
typedef  TYPE_2__ vdp_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  VdpStatus ;
typedef  int /*<<< orphan*/  VdpRect ;
typedef  int /*<<< orphan*/  VdpOutputSurface ;
typedef  int /*<<< orphan*/  VdpIndexedFormat ;
typedef  int /*<<< orphan*/  VdpColorTableFormat ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FUNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OUTPUT_SURFACE_PUT_BITS_INDEXED ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const* const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,void const*) ; 

VdpStatus vdp_output_surface_put_bits_indexed(const vdp_t *vdp,
    VdpOutputSurface surface, VdpIndexedFormat fmt, const void *const *data,
    const uint32_t *pitch, const VdpRect *dst,
    VdpColorTableFormat tabfmt, const void *tab)
{
    CHECK_FUNC(OUTPUT_SURFACE_PUT_BITS_INDEXED);
    return vdp->vt.output_surface_put_bits_indexed(surface, fmt, data, pitch,
                                                   dst, tabfmt, tab);
}