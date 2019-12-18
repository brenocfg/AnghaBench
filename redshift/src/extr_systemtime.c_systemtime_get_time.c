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
struct timeval {double tv_sec; double tv_usec; } ;
struct timespec {double tv_sec; double tv_nsec; } ;
struct TYPE_4__ {double QuadPart; int /*<<< orphan*/  HighPart; int /*<<< orphan*/  LowPart; } ;
typedef  TYPE_1__ ULARGE_INTEGER ;
struct TYPE_5__ {int /*<<< orphan*/  dwHighDateTime; int /*<<< orphan*/  dwLowDateTime; } ;
typedef  TYPE_2__ FILETIME ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int /*<<< orphan*/  GetSystemTimeAsFileTime (TYPE_2__*) ; 
 int clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perror (char*) ; 

int
systemtime_get_time(double *t)
{
#if defined(_WIN32) /* Windows */
	FILETIME now;
	ULARGE_INTEGER i;
	GetSystemTimeAsFileTime(&now);
	i.LowPart = now.dwLowDateTime;
	i.HighPart = now.dwHighDateTime;

	/* FILETIME is tenths of microseconds since 1601-01-01 UTC */
	*t = (i.QuadPart / 10000000.0) - 11644473600.0;
#elif _POSIX_TIMERS > 0 /* POSIX timers */
	struct timespec now;
	int r = clock_gettime(CLOCK_REALTIME, &now);
	if (r < 0) {
		perror("clock_gettime");
		return -1;
	}

	*t = now.tv_sec + (now.tv_nsec / 1000000000.0);
#else /* other platforms */
	struct timeval now;
	int r = gettimeofday(&now, NULL);
	if (r < 0) {
		perror("gettimeofday");
		return -1;
	}

	*t = now.tv_sec + (now.tv_usec / 1000000.0);
#endif

	return 0;
}