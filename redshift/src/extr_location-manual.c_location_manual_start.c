#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lon; int /*<<< orphan*/  lat; } ;
struct TYPE_5__ {TYPE_1__ loc; } ;
typedef  TYPE_2__ location_manual_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ isnan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
location_manual_start(location_manual_state_t *state)
{
	/* Latitude and longitude must be set */
	if (isnan(state->loc.lat) || isnan(state->loc.lon)) {
		fputs(_("Latitude and longitude must be set.\n"), stderr);
		exit(EXIT_FAILURE);
	}

	return 0;
}