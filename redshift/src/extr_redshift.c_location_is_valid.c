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
struct TYPE_3__ {scalar_t__ lat; scalar_t__ lon; } ;
typedef  TYPE_1__ location_t ;

/* Variables and functions */
 scalar_t__ MAX_LAT ; 
 scalar_t__ MAX_LON ; 
 scalar_t__ MIN_LAT ; 
 scalar_t__ MIN_LON ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
location_is_valid(const location_t *location)
{
	/* Latitude */
	if (location->lat < MIN_LAT || location->lat > MAX_LAT) {
		/* TRANSLATORS: Append degree symbols if possible. */
		fprintf(stderr,
			_("Latitude must be between %.1f and %.1f.\n"),
			MIN_LAT, MAX_LAT);
		return 0;
	}

	/* Longitude */
	if (location->lon < MIN_LON || location->lon > MAX_LON) {
		/* TRANSLATORS: Append degree symbols if possible. */
		fprintf(stderr,
			_("Longitude must be between"
			  " %.1f and %.1f.\n"), MIN_LON, MAX_LON);
		return 0;
	}

	return 1;
}