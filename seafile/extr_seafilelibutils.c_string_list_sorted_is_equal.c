#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_4__ {struct TYPE_4__* next; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ GList ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ g_strcmp0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

gboolean
string_list_sorted_is_equal (GList *list1, GList *list2)
{
    GList *ptr1 = list1, *ptr2 = list2;

    while (ptr1 && ptr2) {
        if (g_strcmp0(ptr1->data, ptr2->data) != 0)
            break;

        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
    }

    if (!ptr1 && !ptr2)
        return TRUE;
    return FALSE;
}