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
 int /*<<< orphan*/  EPERM ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 scalar_t__ geteuid () ; 
 int log_error_errno (int /*<<< orphan*/ ,char*) ; 

int must_be_root(void) {

        if (geteuid() == 0)
                return 0;

        return log_error_errno(SYNTHETIC_ERRNO(EPERM), "Need to be root.");
}