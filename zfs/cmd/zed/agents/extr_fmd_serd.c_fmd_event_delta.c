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
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ hrtime_t ;

/* Variables and functions */
 scalar_t__ UINT64_MAX ; 

__attribute__((used)) static hrtime_t
fmd_event_delta(hrtime_t t1, hrtime_t t2)
{
	uint64_t old = t1;
	uint64_t new = t2;

	return (new >= old ? new - old : (UINT64_MAX - old) + new + 1);
}