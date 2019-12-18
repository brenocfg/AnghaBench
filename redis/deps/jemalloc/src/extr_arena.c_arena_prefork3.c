#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsdn_t ;
struct TYPE_3__ {int /*<<< orphan*/  extents_retained; int /*<<< orphan*/  extents_muzzy; int /*<<< orphan*/  extents_dirty; } ;
typedef  TYPE_1__ arena_t ;

/* Variables and functions */
 int /*<<< orphan*/  extents_prefork (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
arena_prefork3(tsdn_t *tsdn, arena_t *arena) {
	extents_prefork(tsdn, &arena->extents_dirty);
	extents_prefork(tsdn, &arena->extents_muzzy);
	extents_prefork(tsdn, &arena->extents_retained);
}