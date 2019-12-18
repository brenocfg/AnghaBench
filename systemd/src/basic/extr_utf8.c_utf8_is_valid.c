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
 int utf8_encoded_valid_unichar (char const*,size_t) ; 

char *utf8_is_valid(const char *str) {
        const char *p;

        assert(str);

        p = str;
        while (*p) {
                int len;

                len = utf8_encoded_valid_unichar(p, (size_t) -1);
                if (len < 0)
                        return NULL;

                p += len;
        }

        return (char*) str;
}