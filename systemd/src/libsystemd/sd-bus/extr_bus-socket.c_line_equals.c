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
 scalar_t__ memcmp (char const*,char const*,size_t) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static bool line_equals(const char *s, size_t m, const char *line) {
        size_t l;

        l = strlen(line);
        if (l != m)
                return false;

        return memcmp(s, line, l) == 0;
}