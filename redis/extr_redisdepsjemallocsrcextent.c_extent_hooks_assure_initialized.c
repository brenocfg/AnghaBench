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
typedef  int /*<<< orphan*/  extent_hooks_t ;
typedef  int /*<<< orphan*/  arena_t ;

/* Variables and functions */
 int /*<<< orphan*/ * EXTENT_HOOKS_INITIALIZER ; 
 int /*<<< orphan*/ * extent_hooks_get (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
extent_hooks_assure_initialized(arena_t *arena,
    extent_hooks_t **r_extent_hooks) {
	if (*r_extent_hooks == EXTENT_HOOKS_INITIALIZER) {
		*r_extent_hooks = extent_hooks_get(arena);
	}
}