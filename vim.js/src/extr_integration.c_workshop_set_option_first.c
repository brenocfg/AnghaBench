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
typedef  int Boolean ;

/* Variables and functions */
 int atoi (char*) ; 
 int save_files ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  workshop_balloon_delay (int) ; 
 int /*<<< orphan*/  workshop_balloon_mode (int) ; 
 int /*<<< orphan*/  workshop_hotkeys (int) ; 
 int /*<<< orphan*/  workshop_set_option (char*,char*) ; 

void workshop_set_option_first(char *name, char *value)
{
	/* Currently value can only be on/off. This may change later (for
	 * example to set an option like "balloon evaluate delay", but
	 * for now just convert it into a boolean */
	Boolean on = !strcmp(value, "on");

	if (!strcmp(name, "workshopkeys")) {
		workshop_hotkeys(on);
	} else if (!strcmp(name, "savefiles")) {
		save_files = on;
	} else if (!strcmp(name, "balloon")) {
		workshop_balloon_mode(on);
	} else if (!strcmp(name, "balloondelay")) {
		int delay = atoi(value);
		/* Should I validate the number here?? */
		workshop_balloon_delay(delay);
	} else {
		/* Let editor interpret it */
		workshop_set_option(name, value);
	}
}