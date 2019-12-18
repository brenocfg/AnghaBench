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
typedef  int /*<<< orphan*/  sd_id128_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IN_SET (char const,int /*<<< orphan*/ ,char,char) ; 
 int /*<<< orphan*/  SD_ID128_NULL ; 
 int safe_atoi (char const*,int*) ; 
 int sd_id128_from_string (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ streq (char const*,char*) ; 
 int strlen (char const*) ; 
 char* strndupa (char const*,int) ; 

__attribute__((used)) static int parse_boot_descriptor(const char *x, sd_id128_t *boot_id, int *offset) {
        sd_id128_t id = SD_ID128_NULL;
        int off = 0, r;

        if (streq(x, "all")) {
                *boot_id = SD_ID128_NULL;
                *offset = 0;
                return 0;
        } else if (strlen(x) >= 32) {
                char *t;

                t = strndupa(x, 32);
                r = sd_id128_from_string(t, &id);
                if (r >= 0)
                        x += 32;

                if (!IN_SET(*x, 0, '-', '+'))
                        return -EINVAL;

                if (*x != 0) {
                        r = safe_atoi(x, &off);
                        if (r < 0)
                                return r;
                }
        } else {
                r = safe_atoi(x, &off);
                if (r < 0)
                        return r;
        }

        if (boot_id)
                *boot_id = id;

        if (offset)
                *offset = off;

        return 1;
}