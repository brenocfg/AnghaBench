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
typedef  int /*<<< orphan*/  LogRealm ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_REALM_PLUS_LEVEL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int log_internal_realm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,char const*,char*) ; 

int log_oom_internal(LogRealm realm, const char *file, int line, const char *func) {
        return log_internal_realm(LOG_REALM_PLUS_LEVEL(realm, LOG_ERR),
                                  ENOMEM, file, line, func, "Out of memory.");
}