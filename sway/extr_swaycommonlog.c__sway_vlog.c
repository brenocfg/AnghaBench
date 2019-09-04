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
typedef  int /*<<< orphan*/  sway_log_importance_t ;

/* Variables and functions */
 int /*<<< orphan*/  sway_log_stderr (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

void _sway_vlog(sway_log_importance_t verbosity, const char *fmt, va_list args) {
	sway_log_stderr(verbosity, fmt, args);
}