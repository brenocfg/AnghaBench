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
typedef  scalar_t__ time_t ;
struct time {scalar_t__ sec; } ;

/* Variables and functions */
 scalar_t__ atol (char const*) ; 

__attribute__((used)) static void
parse_timesec(struct time *time, const char *sec)
{
	time->sec = (time_t) atol(sec);
}