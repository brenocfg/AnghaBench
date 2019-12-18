#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ do_syslog; } ;

/* Variables and functions */
 TYPE_1__ _ctx ; 
 int /*<<< orphan*/  closelog () ; 

void
zed_log_syslog_close(void)
{
	if (_ctx.do_syslog) {
		_ctx.do_syslog = 0;
		closelog();
	}
}