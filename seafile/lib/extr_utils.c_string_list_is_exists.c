#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_3__ {int /*<<< orphan*/  data; struct TYPE_3__* next; } ;
typedef  TYPE_1__ GList ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ g_strcmp0 (char const*,int /*<<< orphan*/ ) ; 

gboolean
string_list_is_exists (GList *str_list, const char *string)
{
    GList *ptr;
    for (ptr = str_list; ptr; ptr = ptr->next) {
        if (g_strcmp0(string, ptr->data) == 0)
            return TRUE;
    }
    return FALSE;
}