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
typedef  int uint64_t ;
struct TYPE_4__ {int /*<<< orphan*/ * backlog; } ;
typedef  TYPE_1__ arena_decay_t ;

/* Variables and functions */
 int SMOOTHSTEP_NSTEPS ; 
 int /*<<< orphan*/  arena_decay_backlog_update_last (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void
arena_decay_backlog_update(arena_decay_t *decay, uint64_t nadvance_u64,
    size_t current_npages) {
	if (nadvance_u64 >= SMOOTHSTEP_NSTEPS) {
		memset(decay->backlog, 0, (SMOOTHSTEP_NSTEPS-1) *
		    sizeof(size_t));
	} else {
		size_t nadvance_z = (size_t)nadvance_u64;

		assert((uint64_t)nadvance_z == nadvance_u64);

		memmove(decay->backlog, &decay->backlog[nadvance_z],
		    (SMOOTHSTEP_NSTEPS - nadvance_z) * sizeof(size_t));
		if (nadvance_z > 1) {
			memset(&decay->backlog[SMOOTHSTEP_NSTEPS -
			    nadvance_z], 0, (nadvance_z-1) * sizeof(size_t));
		}
	}

	arena_decay_backlog_update_last(decay, current_npages);
}