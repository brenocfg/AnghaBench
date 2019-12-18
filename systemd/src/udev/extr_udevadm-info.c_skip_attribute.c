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
 int /*<<< orphan*/  ELEMENTSOF (char const* const*) ; 
 scalar_t__ string_table_lookup (char const* const*,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static bool skip_attribute(const char *name) {
        static const char* const skip[] = {
                "uevent",
                "dev",
                "modalias",
                "resource",
                "driver",
                "subsystem",
                "module",
        };

        return string_table_lookup(skip, ELEMENTSOF(skip), name) >= 0;
}