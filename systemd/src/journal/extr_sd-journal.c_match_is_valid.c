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
 int /*<<< orphan*/  assert (void const*) ; 
 scalar_t__ startswith (void const*,char*) ; 

__attribute__((used)) static int match_is_valid(const void *data, size_t size) {
        const char *b, *p;

        assert(data);

        if (size < 2)
                return false;

        if (startswith(data, "__"))
                return false;

        b = data;
        for (p = b; p < b + size; p++) {

                if (*p == '=')
                        return p > b;

                if (*p == '_')
                        continue;

                if (*p >= 'A' && *p <= 'Z')
                        continue;

                if (*p >= '0' && *p <= '9')
                        continue;

                return false;
        }

        return false;
}