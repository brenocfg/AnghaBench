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
 int asprintf (char**,char*,...) ; 
 char* strrchr (char const*,char) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static char *vlc_uri_merge_paths(const char *base, const char *ref)
{
    char *str;
    int len;

    if (base == NULL)
        len = asprintf(&str, "/%s", ref);
    else
    {
        const char *end = strrchr(base, '/');

        if (end != NULL)
            end++;
        else
            end = base;

        len = asprintf(&str, "%.*s%s", (int)(end - base), base, ref);
    }

    if (unlikely(len == -1))
        str = NULL;
    return str;
}