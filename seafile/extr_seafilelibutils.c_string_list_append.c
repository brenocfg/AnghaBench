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
 int /*<<< orphan*/ * g_list_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_return_val_if_fail (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_strdup (char const*) ; 
 scalar_t__ string_list_is_exists (int /*<<< orphan*/ *,char const*) ; 

GList*
string_list_append (GList *str_list, const char *string)
{
    g_return_val_if_fail (string != NULL, str_list);

    if (string_list_is_exists(str_list, string))
        return str_list;

    str_list = g_list_append (str_list, g_strdup(string));
    return str_list;
}