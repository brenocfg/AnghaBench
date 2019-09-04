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
 scalar_t__ MS_PER_DAY ; 
 scalar_t__ fmod (scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline DOUBLE time_within_day(DOUBLE time)
{
    DOUBLE ret;

    ret = fmod(time, MS_PER_DAY);
    if(ret < 0)
        ret += MS_PER_DAY;

    return ret;
}