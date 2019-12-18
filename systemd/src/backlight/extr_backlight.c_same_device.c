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
typedef  int /*<<< orphan*/  sd_device ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int sd_device_get_subsystem (int /*<<< orphan*/ *,char const**) ; 
 int sd_device_get_sysname (int /*<<< orphan*/ *,char const**) ; 
 int streq (char const*,char const*) ; 

__attribute__((used)) static int same_device(sd_device *a, sd_device *b) {
        const char *a_val, *b_val;
        int r;

        assert(a);
        assert(b);

        r = sd_device_get_subsystem(a, &a_val);
        if (r < 0)
                return r;

        r = sd_device_get_subsystem(b, &b_val);
        if (r < 0)
                return r;

        if (!streq(a_val, b_val))
                return false;

        r = sd_device_get_sysname(a, &a_val);
        if (r < 0)
                return r;

        r = sd_device_get_sysname(b, &b_val);
        if (r < 0)
                return r;

        return streq(a_val, b_val);
}