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
 int /*<<< orphan*/  PR_SET_MM ; 
 int /*<<< orphan*/  PR_SET_MM_ENV_END ; 
 int /*<<< orphan*/  PR_SET_MM_ENV_START ; 
 int errno ; 
 scalar_t__ prctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int reset_environ(const char *new_environment, size_t length) {
        unsigned long start, end;

        start = (unsigned long) new_environment;
        end = start + length;

        if (prctl(PR_SET_MM, PR_SET_MM_ENV_START, start, 0, 0) < 0)
                return -errno;

        if (prctl(PR_SET_MM, PR_SET_MM_ENV_END, end, 0, 0) < 0)
                return -errno;

        return 0;
}