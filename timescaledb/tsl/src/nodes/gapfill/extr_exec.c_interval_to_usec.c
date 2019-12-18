#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64 ;
struct TYPE_3__ {int month; int day; scalar_t__ time; } ;
typedef  TYPE_1__ Interval ;

/* Variables and functions */
 int DAYS_PER_MONTH ; 
 int /*<<< orphan*/  ERRCODE_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
 int USECS_PER_DAY ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 

__attribute__((used)) static inline int64
interval_to_usec(Interval *interval)
{
	if (interval == NULL)
		ereport(ERROR, (errcode(ERRCODE_INTERNAL_ERROR), errmsg("interval cannot be NULL")));
	return (interval->month * DAYS_PER_MONTH * USECS_PER_DAY) + (interval->day * USECS_PER_DAY) +
		   interval->time;
}