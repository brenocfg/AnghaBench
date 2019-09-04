#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  tsdn_t ;
typedef  int /*<<< orphan*/  arena_t ;

/* Variables and functions */
 scalar_t__ arena_decay_dirty (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  arena_decay_muzzy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 

void
arena_decay(tsdn_t *tsdn, arena_t *arena, bool is_background_thread, bool all) {
	if (arena_decay_dirty(tsdn, arena, is_background_thread, all)) {
		return;
	}
	arena_decay_muzzy(tsdn, arena, is_background_thread, all);
}