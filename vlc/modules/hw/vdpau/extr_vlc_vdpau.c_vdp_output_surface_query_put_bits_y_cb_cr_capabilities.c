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
struct TYPE_4__ {int /*<<< orphan*/  (* output_surface_query_put_bits_y_cb_cr_capabilities ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_5__ {TYPE_1__ vt; } ;
typedef  TYPE_2__ vdp_t ;
typedef  int /*<<< orphan*/  VdpYCbCrFormat ;
typedef  int /*<<< orphan*/  VdpStatus ;
typedef  int /*<<< orphan*/  VdpRGBAFormat ;
typedef  int /*<<< orphan*/  VdpDevice ;
typedef  int /*<<< orphan*/  VdpBool ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FUNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OUTPUT_SURFACE_QUERY_PUT_BITS_Y_CB_CR_CAPABILITIES ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

VdpStatus vdp_output_surface_query_put_bits_y_cb_cr_capabilities(
    const vdp_t *vdp, VdpDevice device,
    VdpRGBAFormat fmt, VdpYCbCrFormat yccfmt, VdpBool *ok)
{
    CHECK_FUNC(OUTPUT_SURFACE_QUERY_PUT_BITS_Y_CB_CR_CAPABILITIES);
    return vdp->vt.output_surface_query_put_bits_y_cb_cr_capabilities(device,
                                                              fmt, yccfmt, ok);
}