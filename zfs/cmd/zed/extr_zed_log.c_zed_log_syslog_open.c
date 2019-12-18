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
struct TYPE_2__ {int do_syslog; int /*<<< orphan*/  identity; } ;

/* Variables and functions */
 int LOG_NDELAY ; 
 int LOG_PID ; 
 TYPE_1__ _ctx ; 
 int /*<<< orphan*/  openlog (int /*<<< orphan*/ ,int,int) ; 

void
zed_log_syslog_open(int facility)
{
	_ctx.do_syslog = 1;
	openlog(_ctx.identity, LOG_NDELAY | LOG_PID, facility);
}