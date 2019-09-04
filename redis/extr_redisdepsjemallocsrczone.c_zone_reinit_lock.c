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
typedef  int /*<<< orphan*/  malloc_zone_t ;

/* Variables and functions */
 int /*<<< orphan*/  zone_force_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
zone_reinit_lock(malloc_zone_t *zone) {
	/* As of OSX 10.12, this function is only used when force_unlock would
	 * be used if the zone version were < 9. So just use force_unlock. */
	zone_force_unlock(zone);
}