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
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_4__ {int /*<<< orphan*/ * arcs_esize; } ;
typedef  TYPE_1__ arc_state_t ;
typedef  size_t arc_buf_contents_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARC_EVICT_ALL ; 
 scalar_t__ arc_evict_state (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ zfs_refcount_count (int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint64_t
arc_flush_state(arc_state_t *state, uint64_t spa, arc_buf_contents_t type,
    boolean_t retry)
{
	uint64_t evicted = 0;

	while (zfs_refcount_count(&state->arcs_esize[type]) != 0) {
		evicted += arc_evict_state(state, spa, ARC_EVICT_ALL, type);

		if (!retry)
			break;
	}

	return (evicted);
}