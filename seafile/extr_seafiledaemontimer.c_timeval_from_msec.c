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
typedef  int uint64_t ;
struct timeval {int tv_sec; int tv_usec; } ;

/* Variables and functions */

struct timeval
timeval_from_msec (uint64_t milliseconds)
{
    struct timeval ret;
    const uint64_t microseconds = milliseconds * 1000;
    ret.tv_sec  = microseconds / 1000000;
    ret.tv_usec = microseconds % 1000000;
    return ret;
}