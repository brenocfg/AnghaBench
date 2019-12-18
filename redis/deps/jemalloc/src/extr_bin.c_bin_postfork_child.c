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
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ bin_t ;

/* Variables and functions */
 int /*<<< orphan*/  malloc_mutex_postfork_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
bin_postfork_child(tsdn_t *tsdn, bin_t *bin) {
	malloc_mutex_postfork_child(tsdn, &bin->lock);
}