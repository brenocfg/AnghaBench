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
typedef  int gboolean ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ strcasecmp (char const*,char*) ; 
 int strlen (char const*) ; 

gboolean
is_eml_file (const char *path)
{
    int len = strlen(path);
    const char *ext;

    if (len < 5)
        return FALSE;
    ext = &path[len-4];
    return (strcasecmp (ext, ".eml") == 0);
}