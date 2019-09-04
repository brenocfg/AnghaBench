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
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  LOG_LEVEL ;

/* Variables and functions */
 int /*<<< orphan*/  level_syslog (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vsyslog (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

void log_syslog(LOG_LEVEL level, const char *format, va_list args)
{
    vsyslog(level_syslog(level), format, args);
}