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
typedef  int /*<<< orphan*/  GList ;

/* Variables and functions */
 int /*<<< orphan*/ * g_list_prepend (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * g_list_reverse (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_strdup (char*) ; 
 int /*<<< orphan*/  g_strfreev (char**) ; 
 char** g_strsplit (char const*,char const*,int /*<<< orphan*/ ) ; 

GList *
string_list_parse (const char *list_in_str, const char *seperator)
{
    if (!list_in_str)
        return NULL;

    GList *list = NULL;
    char **array = g_strsplit (list_in_str, seperator, 0);
    char **ptr;

    for (ptr = array; *ptr; ptr++) {
        list = g_list_prepend (list, g_strdup(*ptr));
    }
    list = g_list_reverse (list);
    
    g_strfreev (array);
    return list;
}