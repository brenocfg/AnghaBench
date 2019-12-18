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
struct timespec {unsigned int tv_sec; unsigned int tv_nsec; } ;

/* Variables and functions */
 int /*<<< orphan*/  Sleep (unsigned int) ; 
 int /*<<< orphan*/  nanosleep (struct timespec*,int /*<<< orphan*/ *) ; 

void
systemtime_msleep(unsigned int msecs)
{
#ifndef _WIN32
	struct timespec sleep;
	sleep.tv_sec = msecs / 1000;
	sleep.tv_nsec = (msecs % 1000)*1000000;
	nanosleep(&sleep, NULL);
#else
	Sleep(msecs);
#endif
}