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
typedef  int uint32_t ;
struct TYPE_4__ {int last_deleted; int last_added; int total_size; int /*<<< orphan*/ * entries; } ;
typedef  TYPE_1__ Ping_Array ;

/* Variables and functions */
 int /*<<< orphan*/  clear_entry (TYPE_1__*,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

void ping_array_free_all(Ping_Array *array)
{
    while (array->last_deleted != array->last_added) {
        uint32_t index = array->last_deleted % array->total_size;
        clear_entry(array, index);
        ++array->last_deleted;
    }

    free(array->entries);
    array->entries = NULL;
}