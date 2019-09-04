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
 scalar_t__ opt_mailmap ; 

const char *
log_custom_pretty_arg(void)
{
	return opt_mailmap
		? "--pretty=format:commit %m %H %P%x00%aN <%aE> %ad%x00%s"
		: "--pretty=format:commit %m %H %P%x00%an <%ae> %ad%x00%s";
}