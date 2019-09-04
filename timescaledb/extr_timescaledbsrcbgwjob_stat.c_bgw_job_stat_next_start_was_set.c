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
struct TYPE_3__ {scalar_t__ next_start; } ;
typedef  TYPE_1__ FormData_bgw_job_stat ;

/* Variables and functions */
 scalar_t__ DT_NOBEGIN ; 

__attribute__((used)) static bool
bgw_job_stat_next_start_was_set(FormData_bgw_job_stat *fd)
{
	return fd->next_start != DT_NOBEGIN;
}