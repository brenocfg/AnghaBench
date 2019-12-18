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
struct TYPE_4__ {int /*<<< orphan*/  (* presentation_queue_target_destroy ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {TYPE_1__ vt; } ;
typedef  TYPE_2__ vdp_t ;
typedef  int /*<<< orphan*/  VdpStatus ;
typedef  int /*<<< orphan*/  VdpPresentationQueueTarget ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FUNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRESENTATION_QUEUE_TARGET_DESTROY ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

VdpStatus vdp_presentation_queue_target_destroy(const vdp_t *vdp,
    VdpPresentationQueueTarget target)
{
    CHECK_FUNC(PRESENTATION_QUEUE_TARGET_DESTROY);
    return vdp->vt.presentation_queue_target_destroy(target);
}