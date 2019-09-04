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
 char* g_strconcat (char*,char const*,int /*<<< orphan*/ *) ; 
 char* g_strdup (char const*) ; 
 int strlen (char const*) ; 

char*
format_dir_path (const char *path)
{
    int path_len = strlen (path);
    char *rpath;
    if (path[0] != '/') {
        rpath = g_strconcat ("/", path, NULL);
        path_len++;
    } else {
        rpath = g_strdup (path);
    }
    while (path_len > 1 && rpath[path_len-1] == '/') {
        rpath[path_len-1] = '\0';
        path_len--;
    }

    return rpath;
}