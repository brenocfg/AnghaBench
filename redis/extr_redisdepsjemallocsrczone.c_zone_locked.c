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
typedef  int boolean_t ;

/* Variables and functions */

__attribute__((used)) static boolean_t
zone_locked(malloc_zone_t *zone) {
	/* Pretend no lock is being held */
	return false;
}