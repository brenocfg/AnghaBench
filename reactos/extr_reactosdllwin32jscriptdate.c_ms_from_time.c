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
typedef  scalar_t__ DOUBLE ;

/* Variables and functions */
 scalar_t__ NAN ; 
 scalar_t__ fmod (scalar_t__,int) ; 
 scalar_t__ isnan (scalar_t__) ; 

__attribute__((used)) static inline DOUBLE ms_from_time(DOUBLE time)
{
    DOUBLE ret;

    if(isnan(time))
        return NAN;

    ret = fmod(time, 1000);
    if(ret<0) ret += 1000;

    return ret;
}