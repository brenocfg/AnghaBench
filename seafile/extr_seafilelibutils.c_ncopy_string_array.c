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
 char** g_malloc (int) ; 
 char* g_strdup (char*) ; 

char **
ncopy_string_array (char **orig, int n)
{
    char **ret = g_malloc (sizeof(char *) * n);
    int i = 0;

    for (; i < n; i++)
        ret[i] = g_strdup(orig[i]);
    return ret;
}