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

/* Variables and functions */
 int /*<<< orphan*/  ctl_mtx ; 
 int /*<<< orphan*/  malloc_mutex_postfork_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
ctl_postfork_child(tsdn_t *tsdn) {
	malloc_mutex_postfork_child(tsdn, &ctl_mtx);
}