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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_INFO ; 
 int /*<<< orphan*/  log_file (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * popen (char*,char*) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void log_kernel(void) {
	FILE *f = popen("uname -a", "r");
	if (!f) {
		sway_log(SWAY_INFO, "Unable to determine kernel version");
		return;
	}
	log_file(f);
	pclose(f);
}