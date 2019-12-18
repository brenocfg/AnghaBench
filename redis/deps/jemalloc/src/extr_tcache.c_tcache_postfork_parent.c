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
 int /*<<< orphan*/  config_prof ; 
 int /*<<< orphan*/  malloc_mutex_postfork_parent (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ opt_tcache ; 
 int /*<<< orphan*/  tcaches_mtx ; 

void
tcache_postfork_parent(tsdn_t *tsdn) {
	if (!config_prof && opt_tcache) {
		malloc_mutex_postfork_parent(tsdn, &tcaches_mtx);
	}
}