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
 char* g_strconcat (char*,char*,int /*<<< orphan*/ *) ; 
 char* g_strdup (char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static char *
canonical_perm_path (const char *path)
{
    int len = strlen(path);
    char *copy, *ret;

    if (strcmp (path, "/") == 0)
        return g_strdup(path);

    if (path[0] == '/' && path[len-1] != '/')
        return g_strdup(path);

    copy = g_strdup(path);

    if (copy[len-1] == '/')
        copy[len-1] = 0;

    if (copy[0] != '/')
        ret = g_strconcat ("/", copy, NULL);
    else
        ret = copy;

    return ret;
}