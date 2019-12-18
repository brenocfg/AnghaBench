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
struct timeval {double tv_sec; double tv_usec; } ;
struct _timeb {double time; double millitm; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ftime (struct _timeb*) ; 
 double floor (double) ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 double time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static double Now(void)
{
#if defined(__unix__) || defined(__APPLE__)
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return floor(tv.tv_sec * 1000.0 + tv.tv_usec / 1000.0);
#elif defined(_WIN32)
	struct _timeb tv;
	_ftime(&tv);
	return tv.time * 1000.0 + tv.millitm;
#else
	return time(NULL) * 1000.0;
#endif
}