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
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  REENABLE_WARNING ; 
 int /*<<< orphan*/  log_internalv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 char* strjoina (char*,char const*) ; 

void microhttpd_logger(void *arg, const char *fmt, va_list ap) {
        char *f;

        f = strjoina("microhttpd: ", fmt);

        DISABLE_WARNING_FORMAT_NONLITERAL;
        log_internalv(LOG_INFO, 0, NULL, 0, NULL, f, ap);
        REENABLE_WARNING;
}