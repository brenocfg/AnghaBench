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
struct TYPE_4__ {int /*<<< orphan*/  n; int /*<<< orphan*/  capacity; } ;
typedef  TYPE_1__ BS_LIST ;

/* Variables and functions */
 int /*<<< orphan*/  resize (TYPE_1__*,int /*<<< orphan*/ ) ; 

int bs_list_trim(BS_LIST *list)
{
    if (!resize(list, list->n)) {
        return 0;
    }

    list->capacity = list->n;
    return 1;
}