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

/* Variables and functions */
 int /*<<< orphan*/  SWAY_ERROR ; 
 scalar_t__ getegid () ; 
 scalar_t__ geteuid () ; 
 scalar_t__ getgid () ; 
 scalar_t__ getuid () ; 
 scalar_t__ setgid (scalar_t__) ; 
 int setuid (scalar_t__) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool drop_permissions(void) {
	if (getuid() != geteuid() || getgid() != getegid()) {
		if (setuid(getuid()) != 0 || setgid(getgid()) != 0) {
			sway_log(SWAY_ERROR, "Unable to drop root, refusing to start");
			return false;
		}
	}
	if (setuid(0) != -1) {
		sway_log(SWAY_ERROR, "Unable to drop root (we shouldn't be able to "
			"restore it after setuid), refusing to start");
		return false;
	}
	return true;
}