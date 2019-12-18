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
 int /*<<< orphan*/ * getenv (char const*) ; 
 char* malloc (size_t) ; 
 int putenv (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,char const*) ; 
 size_t strlen (char const*) ; 

int setenv (const char *name, const char *value, int override)
{
#ifdef HAVE_GETENV
    if (override == 0 && getenv (name) != NULL)
        return 0;

    size_t namelen = strlen (name);
    size_t valuelen = strlen (value);
    char *var = malloc (namelen + valuelen + 2);

    if (var == NULL)
        return -1;

    sprintf (var, "%s=%s", name, value);
    /* This leaks memory. This is unavoidable. */
    return putenv (var);
#else
    return -1;
#endif
}