#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned long long tv_sec; unsigned long long tv_nsec; } ;
typedef  TYPE_1__ UTIL_time_t ;
typedef  unsigned long long PTime ;

/* Variables and functions */
 TYPE_1__ UTIL_getSpanTime (TYPE_1__,TYPE_1__) ; 

PTime UTIL_getSpanTimeMicro(UTIL_time_t begin, UTIL_time_t end)
{
    UTIL_time_t const diff = UTIL_getSpanTime(begin, end);
    PTime micro = 0;
    micro += 1000000ULL * diff.tv_sec;
    micro += diff.tv_nsec / 1000ULL;
    return micro;
}