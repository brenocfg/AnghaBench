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
struct TYPE_4__ {int /*<<< orphan*/  (* get_proc_address ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ;} ;
struct TYPE_5__ {TYPE_1__ vt; } ;
typedef  TYPE_2__ vdp_t ;
typedef  int /*<<< orphan*/  VdpStatus ;
typedef  int /*<<< orphan*/  VdpFuncId ;
typedef  int /*<<< orphan*/  VdpDevice ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FUNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_PROC_ADDRESS ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ; 

VdpStatus vdp_get_proc_address(const vdp_t *vdp, VdpDevice device,
    VdpFuncId func_id, void **func_ptr)
{
    CHECK_FUNC(GET_PROC_ADDRESS);
    return vdp->vt.get_proc_address(device, func_id, func_ptr);
}