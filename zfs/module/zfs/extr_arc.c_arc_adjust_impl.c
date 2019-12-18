#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_4__ {int /*<<< orphan*/ * arcs_esize; } ;
typedef  TYPE_1__ arc_state_t ;
typedef  size_t arc_buf_contents_t ;

/* Variables and functions */
 scalar_t__ MIN (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  arc_evict_state (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__,size_t) ; 
 scalar_t__ zfs_refcount_count (int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint64_t
arc_adjust_impl(arc_state_t *state, uint64_t spa, int64_t bytes,
    arc_buf_contents_t type)
{
	int64_t delta;

	if (bytes > 0 && zfs_refcount_count(&state->arcs_esize[type]) > 0) {
		delta = MIN(zfs_refcount_count(&state->arcs_esize[type]),
		    bytes);
		return (arc_evict_state(state, spa, delta, type));
	}

	return (0);
}