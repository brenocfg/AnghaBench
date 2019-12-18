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
typedef  int /*<<< orphan*/  usec_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (char const*) ; 
 int log_debug_errno (int,char*,char const*) ; 
 int safe_atou64 (char const*,int /*<<< orphan*/ *) ; 

int deserialize_usec(const char *value, usec_t *ret) {
        int r;

        assert(value);

        r = safe_atou64(value, ret);
        if (r < 0)
                return log_debug_errno(r, "Failed to parse usec value \"%s\": %m", value);

        return 0;
}