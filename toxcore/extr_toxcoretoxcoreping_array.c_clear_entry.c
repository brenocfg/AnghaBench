#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_5__ {TYPE_1__* entries; } ;
struct TYPE_4__ {scalar_t__ ping_id; scalar_t__ time; scalar_t__ length; int /*<<< orphan*/ * data; } ;
typedef  TYPE_2__ Ping_Array ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void clear_entry(Ping_Array *array, uint32_t index)
{
    free(array->entries[index].data);
    array->entries[index].data = NULL;
    array->entries[index].length =
        array->entries[index].time =
            array->entries[index].ping_id = 0;
}