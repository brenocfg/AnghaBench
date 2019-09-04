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
typedef  scalar_t__ uint64_t ;
struct timeval {unsigned long long tv_sec; scalar_t__ tv_usec; } ;

/* Variables and functions */
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint64_t current_time_actual(void)
{
    uint64_t time;
#if defined(_WIN32) || defined(__WIN32__) || defined (WIN32)
    /* This probably works fine */
    FILETIME ft;
    GetSystemTimeAsFileTime(&ft);
    time = ft.dwHighDateTime;
    time <<= 32;
    time |= ft.dwLowDateTime;
    time -= 116444736000000000ULL;
    return time / 10;
#else
    struct timeval a;
    gettimeofday(&a, NULL);
    time = 1000000ULL * a.tv_sec + a.tv_usec;
    return time;
#endif
}