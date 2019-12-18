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
typedef  int time_t ;
struct tm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gmtime_r (int*,struct tm*) ; 

__attribute__((used)) static void
get_tm(time_t t, int utc_offset, struct tm* tm)
{
  t += utc_offset;
  gmtime_r(&t, tm);
}