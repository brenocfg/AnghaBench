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
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int priority; scalar_t__ do_stderr; scalar_t__ do_syslog; } ;

/* Variables and functions */
 int ZED_LOG_MAX_LOG_LEN ; 
 TYPE_1__ _ctx ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  syslog (int,char*,char*) ; 
 int vsnprintf (char*,int,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_zed_log_aux(int priority, const char *fmt, va_list vargs)
{
	char buf[ZED_LOG_MAX_LOG_LEN];
	int n;

	if (!fmt)
		return;

	n = vsnprintf(buf, sizeof (buf), fmt, vargs);
	if ((n < 0) || (n >= sizeof (buf))) {
		buf[sizeof (buf) - 2] = '+';
		buf[sizeof (buf) - 1] = '\0';
	}

	if (_ctx.do_syslog)
		syslog(priority, "%s", buf);

	if (_ctx.do_stderr && (priority <= _ctx.priority))
		fprintf(stderr, "%s\n", buf);
}