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
 scalar_t__ getegid () ; 
 scalar_t__ geteuid () ; 
 int /*<<< orphan*/  getgid () ; 
 int /*<<< orphan*/  getuid () ; 
 int setgid (int /*<<< orphan*/ ) ; 
 int setuid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int drop_privileges(void) {
    // If we are not effectively root, don't drop privileges
    if (geteuid() != 0 && getegid() != 0) {
        return 0;
    }
    if (setgid(getgid()) == -1) {
        return -1;
    }
    if (setuid(getuid()) == -1) {
        return -1;
    }
    return 0;
}