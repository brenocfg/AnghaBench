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
 int EINVAL ; 
 int log_level_from_string (char const*) ; 
 int /*<<< orphan*/  log_set_max_level_realm (int /*<<< orphan*/ ,int) ; 

int log_set_max_level_from_string_realm(LogRealm realm, const char *e) {
        int t;

        t = log_level_from_string(e);
        if (t < 0)
                return -EINVAL;

        log_set_max_level_realm(realm, t);
        return 0;
}