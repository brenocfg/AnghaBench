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

/* Variables and functions */
 int /*<<< orphan*/  DISABLE_WARNING_FORMAT_NONLITERAL ; 
 int /*<<< orphan*/  REENABLE_WARNING ; 
 int /*<<< orphan*/  log_internalv (int,int /*<<< orphan*/ ,char const*,int,char const*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void systemd_kmod_log(void *data, int priority, const char *file, int line,
                             const char *fn, const char *format, va_list args) {

        DISABLE_WARNING_FORMAT_NONLITERAL;
        log_internalv(priority, 0, file, line, fn, format, args);
        REENABLE_WARNING;
}