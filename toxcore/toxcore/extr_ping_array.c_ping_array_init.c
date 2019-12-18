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
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {scalar_t__ timeout; scalar_t__ total_size; scalar_t__ last_added; scalar_t__ last_deleted; int /*<<< orphan*/ * entries; } ;
typedef  int /*<<< orphan*/  Ping_Array_Entry ;
typedef  TYPE_1__ Ping_Array ;

/* Variables and functions */
 int /*<<< orphan*/ * calloc (scalar_t__,int) ; 

int ping_array_init(Ping_Array *empty_array, uint32_t size, uint32_t timeout)
{
    if (size == 0 || timeout == 0 || empty_array == NULL)
        return -1;

    empty_array->entries = calloc(size, sizeof(Ping_Array_Entry));

    if (empty_array->entries == NULL)
        return -1;

    empty_array->last_deleted = empty_array->last_added = 0;
    empty_array->total_size = size;
    empty_array->timeout = timeout;
    return 0;
}