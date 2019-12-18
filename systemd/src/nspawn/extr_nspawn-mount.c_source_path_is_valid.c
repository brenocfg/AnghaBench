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
 int path_is_absolute (char const*) ; 

__attribute__((used)) static bool source_path_is_valid(const char *p) {
        assert(p);

        if (*p == '+')
                p++;

        return path_is_absolute(p);
}