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
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_strdup (char const*) ; 
 scalar_t__ is_separator (char) ; 
 int /*<<< orphan*/  remove_trail_slash (char*) ; 

__attribute__((used)) static int
check_dir_inclusiveness (const char *dira, const char *dirb)
{
    char *a, *b;
    char *p1, *p2;
    int ret = 0;

    a = g_strdup(dira);
    b = g_strdup(dirb);
    remove_trail_slash (a);
    remove_trail_slash (b);

    p1 = a;
    p2 = b;
    while (*p1 != 0 && *p2 != 0) {
        /* Go to the last one in a path separator sequence. */
        while (is_separator(*p1) && is_separator(p1[1]))
            ++p1;
        while (is_separator(*p2) && is_separator(p2[1]))
            ++p2;

        if (!(is_separator(*p1) && is_separator(*p2)) && *p1 != *p2)
            goto out;

        ++p1;
        ++p2;
    }

    /* Example:
     *            p1
     * a: /abc/def/ghi
     *            p2
     * b: /abc/def
     */
    if (*p1 == 0 && *p2 == 0)
        ret = -1;
    else if (*p1 != 0 && is_separator(*p1))
        ret = 1;
    else if (*p2 != 0 && is_separator(*p2))
        ret = -1;

out:
    g_free (a);
    g_free (b);
    return ret;
}