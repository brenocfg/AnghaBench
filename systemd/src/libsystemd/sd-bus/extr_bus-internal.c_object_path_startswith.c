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
 int /*<<< orphan*/  object_path_is_valid (char const*) ; 
 char* startswith (char const*,char const*) ; 
 scalar_t__ streq (char const*,char*) ; 

char* object_path_startswith(const char *a, const char *b) {
        const char *p;

        if (!object_path_is_valid(a) ||
            !object_path_is_valid(b))
                return NULL;

        if (streq(b, "/"))
                return (char*) a + 1;

        p = startswith(a, b);
        if (!p)
                return NULL;

        if (*p == 0)
                return (char*) p;

        if (*p == '/')
                return (char*) p + 1;

        return NULL;
}