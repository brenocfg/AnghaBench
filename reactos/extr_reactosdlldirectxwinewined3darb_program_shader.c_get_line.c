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
 int /*<<< orphan*/  strlen (char const*) ; 
 char* strstr (char const*,char*) ; 

__attribute__((used)) static const char *get_line(const char **ptr)
{
    const char *p, *q;

    p = *ptr;
    if (!(q = strstr(p, "\n")))
    {
        if (!*p) return NULL;
        *ptr += strlen(p);
        return p;
    }
    *ptr = q + 1;

    return p;
}