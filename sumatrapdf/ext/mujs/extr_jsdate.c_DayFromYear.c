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

/* Variables and functions */
 int floor (int) ; 

__attribute__((used)) static int DayFromYear(int y)
{
	return 365 * (y - 1970) +
		floor((y - 1969) / 4.0) -
		floor((y - 1901) / 100.0) +
		floor((y - 1601) / 400.0);
}