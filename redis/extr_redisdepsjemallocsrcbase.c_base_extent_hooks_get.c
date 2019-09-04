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
typedef  int /*<<< orphan*/  extent_hooks_t ;
struct TYPE_3__ {int /*<<< orphan*/  extent_hooks; } ;
typedef  TYPE_1__ base_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC_ACQUIRE ; 
 scalar_t__ atomic_load_p (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

extent_hooks_t *
base_extent_hooks_get(base_t *base) {
	return (extent_hooks_t *)atomic_load_p(&base->extent_hooks,
	    ATOMIC_ACQUIRE);
}