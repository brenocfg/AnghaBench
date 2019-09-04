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
typedef  int /*<<< orphan*/  UTIL_time_t ;
typedef  int /*<<< orphan*/  PTime ;

/* Variables and functions */
 int /*<<< orphan*/  UTIL_getSpanTimeNano (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  UTIL_getTime () ; 

PTime UTIL_clockSpanNano(UTIL_time_t clockStart )
{
    UTIL_time_t const clockEnd = UTIL_getTime();
    return UTIL_getSpanTimeNano(clockStart, clockEnd);
}