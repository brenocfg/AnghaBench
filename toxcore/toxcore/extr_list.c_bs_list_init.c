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
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {scalar_t__ capacity; int /*<<< orphan*/ * ids; int /*<<< orphan*/ * data; scalar_t__ element_size; scalar_t__ n; } ;
typedef  TYPE_1__ BS_LIST ;

/* Variables and functions */
 int /*<<< orphan*/  resize (TYPE_1__*,scalar_t__) ; 

int bs_list_init(BS_LIST *list, uint32_t element_size, uint32_t initial_capacity)
{
    //set initial values
    list->n = 0;
    list->element_size = element_size;
    list->capacity = 0;
    list->data = NULL;
    list->ids = NULL;

    if (initial_capacity != 0) {
        if (!resize(list, initial_capacity)) {
            return 0;
        }
    }

    list->capacity = initial_capacity;

    return 1;
}