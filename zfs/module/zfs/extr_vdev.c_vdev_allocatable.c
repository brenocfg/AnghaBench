#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ vdev_state; TYPE_1__* vdev_mg; int /*<<< orphan*/  vdev_cant_write; } ;
typedef  TYPE_2__ vdev_t ;
typedef  scalar_t__ uint64_t ;
typedef  int boolean_t ;
struct TYPE_5__ {scalar_t__ mg_initialized; } ;

/* Variables and functions */
 scalar_t__ VDEV_STATE_CLOSED ; 
 scalar_t__ VDEV_STATE_DEGRADED ; 
 scalar_t__ vdev_is_concrete (TYPE_2__*) ; 

boolean_t
vdev_allocatable(vdev_t *vd)
{
	uint64_t state = vd->vdev_state;

	/*
	 * We currently allow allocations from vdevs which may be in the
	 * process of reopening (i.e. VDEV_STATE_CLOSED). If the device
	 * fails to reopen then we'll catch it later when we're holding
	 * the proper locks.  Note that we have to get the vdev state
	 * in a local variable because although it changes atomically,
	 * we're asking two separate questions about it.
	 */
	return (!(state < VDEV_STATE_DEGRADED && state != VDEV_STATE_CLOSED) &&
	    !vd->vdev_cant_write && vdev_is_concrete(vd) &&
	    vd->vdev_mg->mg_initialized);
}