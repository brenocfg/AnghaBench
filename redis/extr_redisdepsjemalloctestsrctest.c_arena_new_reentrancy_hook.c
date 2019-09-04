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

/* Variables and functions */
 int /*<<< orphan*/  arena_new_hook_ran ; 
 int /*<<< orphan*/  do_hook (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hooks_arena_new_hook ; 

__attribute__((used)) static void
arena_new_reentrancy_hook() {
	do_hook(&arena_new_hook_ran, &hooks_arena_new_hook);
}