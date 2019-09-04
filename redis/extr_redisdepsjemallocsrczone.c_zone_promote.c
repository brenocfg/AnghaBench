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
 int /*<<< orphan*/ * default_zone ; 
 int /*<<< orphan*/  jemalloc_zone ; 
 int /*<<< orphan*/  malloc_zone_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_zone_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * purgeable_zone ; 
 int /*<<< orphan*/ * zone_default_get () ; 

__attribute__((used)) static void
zone_promote(void) {
	malloc_zone_t *zone;

	do {
		/*
		 * Unregister and reregister the default zone.  On OSX >= 10.6,
		 * unregistering takes the last registered zone and places it
		 * at the location of the specified zone.  Unregistering the
		 * default zone thus makes the last registered one the default.
		 * On OSX < 10.6, unregistering shifts all registered zones.
		 * The first registered zone then becomes the default.
		 */
		malloc_zone_unregister(default_zone);
		malloc_zone_register(default_zone);

		/*
		 * On OSX 10.6, having the default purgeable zone appear before
		 * the default zone makes some things crash because it thinks it
		 * owns the default zone allocated pointers.  We thus
		 * unregister/re-register it in order to ensure it's always
		 * after the default zone.  On OSX < 10.6, there is no purgeable
		 * zone, so this does nothing.  On OSX >= 10.6, unregistering
		 * replaces the purgeable zone with the last registered zone
		 * above, i.e. the default zone.  Registering it again then puts
		 * it at the end, obviously after the default zone.
		 */
		if (purgeable_zone != NULL) {
			malloc_zone_unregister(purgeable_zone);
			malloc_zone_register(purgeable_zone);
		}

		zone = zone_default_get();
	} while (zone != &jemalloc_zone);
}