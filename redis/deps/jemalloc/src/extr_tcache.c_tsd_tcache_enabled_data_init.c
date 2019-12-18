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
typedef  int /*<<< orphan*/  tsd_t ;

/* Variables and functions */
 scalar_t__ opt_tcache ; 
 int /*<<< orphan*/  tsd_slow_update (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsd_tcache_data_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsd_tcache_enabled_set (int /*<<< orphan*/ *,scalar_t__) ; 

bool
tsd_tcache_enabled_data_init(tsd_t *tsd) {
	/* Called upon tsd initialization. */
	tsd_tcache_enabled_set(tsd, opt_tcache);
	tsd_slow_update(tsd);

	if (opt_tcache) {
		/* Trigger tcache init. */
		tsd_tcache_data_init(tsd);
	}

	return false;
}