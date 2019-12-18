#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_6__ {size_t last_deleted; size_t last_added; size_t total_size; int /*<<< orphan*/  timeout; TYPE_1__* entries; } ;
struct TYPE_5__ {int /*<<< orphan*/  time; } ;
typedef  TYPE_2__ Ping_Array ;

/* Variables and functions */
 int /*<<< orphan*/  clear_entry (TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  is_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ping_array_clear_timedout(Ping_Array *array)
{
    while (array->last_deleted != array->last_added) {
        uint32_t index = array->last_deleted % array->total_size;

        if (!is_timeout(array->entries[index].time, array->timeout))
            break;

        clear_entry(array, index);
        ++array->last_deleted;
    }
}