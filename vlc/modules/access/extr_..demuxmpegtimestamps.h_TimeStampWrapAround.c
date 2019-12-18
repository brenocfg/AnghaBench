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
typedef  int stime_t ;

/* Variables and functions */

__attribute__((used)) static inline stime_t TimeStampWrapAround( stime_t i_first_pcr, stime_t i_time )
{
    stime_t i_adjust = 0;
    if( i_first_pcr > 0x0FFFFFFFF && i_time < 0x0FFFFFFFF )
        i_adjust = 0x1FFFFFFFF;

    return i_time + i_adjust;
}