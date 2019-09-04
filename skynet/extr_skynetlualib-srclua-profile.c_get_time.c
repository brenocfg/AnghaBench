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
struct timespec {int tv_sec; int tv_nsec; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_THREAD_CPUTIME_ID ; 
 double NANOSEC ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 

__attribute__((used)) static double
get_time() {
#if  !defined(__APPLE__)
	struct timespec ti;
	clock_gettime(CLOCK_THREAD_CPUTIME_ID, &ti);

	int sec = ti.tv_sec & 0xffff;
	int nsec = ti.tv_nsec;

	return (double)sec + (double)nsec / NANOSEC;	
#else
	struct task_thread_times_info aTaskInfo;
	mach_msg_type_number_t aTaskInfoCount = TASK_THREAD_TIMES_INFO_COUNT;
	if (KERN_SUCCESS != task_info(mach_task_self(), TASK_THREAD_TIMES_INFO, (task_info_t )&aTaskInfo, &aTaskInfoCount)) {
		return 0;
	}

	int sec = aTaskInfo.user_time.seconds & 0xffff;
	int msec = aTaskInfo.user_time.microseconds;

	return (double)sec + (double)msec / MICROSEC;
#endif
}