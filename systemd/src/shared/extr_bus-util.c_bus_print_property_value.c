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

/* Variables and functions */
 int /*<<< orphan*/  assert (char const*) ; 
 int /*<<< orphan*/  printf (char*,char const*,char const*) ; 
 int /*<<< orphan*/  puts (char const*) ; 
 int /*<<< orphan*/  streq_ptr (char const*,char const*) ; 

int bus_print_property_value(const char *name, const char *expected_value, bool only_value, const char *value) {
        assert(name);

        if (expected_value && !streq_ptr(expected_value, value))
                return 0;

        if (only_value)
                puts(value);
        else
                printf("%s=%s\n", name, value);

        return 0;
}