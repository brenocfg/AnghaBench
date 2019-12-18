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
typedef  scalar_t__ time_t ;

/* Variables and functions */
 scalar_t__ MOUNT_TIME ; 
 int /*<<< orphan*/  finish_progress (char*) ; 
 int /*<<< orphan*/  gettext (char*) ; 
 int /*<<< orphan*/  set_progress_header (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_progress (char*) ; 

__attribute__((used)) static void
report_mount_progress(int current, int total)
{
	static time_t last_progress_time = 0;
	time_t now = time(NULL);
	char info[32];

	/* report 1..n instead of 0..n-1 */
	++current;

	/* display header if we're here for the first time */
	if (current == 1) {
		set_progress_header(gettext("Mounting ZFS filesystems"));
	} else if (current != total && last_progress_time + MOUNT_TIME >= now) {
		/* too soon to report again */
		return;
	}

	last_progress_time = now;

	(void) sprintf(info, "(%d/%d)", current, total);

	if (current == total)
		finish_progress(info);
	else
		update_progress(info);
}