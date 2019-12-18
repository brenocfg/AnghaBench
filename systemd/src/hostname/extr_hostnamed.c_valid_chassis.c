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
 int nulstr_contains (char*,char const*) ; 

__attribute__((used)) static bool valid_chassis(const char *chassis) {
        assert(chassis);

        return nulstr_contains(
                        "vm\0"
                        "container\0"
                        "desktop\0"
                        "laptop\0"
                        "convertible\0"
                        "server\0"
                        "tablet\0"
                        "handset\0"
                        "watch\0"
                        "embedded\0",
                        chassis);
}