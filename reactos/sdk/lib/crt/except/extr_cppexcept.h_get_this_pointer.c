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
struct TYPE_3__ {scalar_t__ vbase_descr; int vbase_offset; int this_offset; } ;
typedef  TYPE_1__ this_ptr_offsets ;

/* Variables and functions */

__attribute__((used)) static inline void* get_this_pointer(const this_ptr_offsets* off, void* object)
{
    if (!object) return NULL;

    if (off->vbase_descr >= 0)
    {
        int* offset_ptr;

        /* move this ptr to vbase descriptor */
        object = (char*)object + off->vbase_descr;
        /* and fetch additional offset from vbase descriptor */
        offset_ptr = (int*)(*(char**)object + off->vbase_offset);
        object = (char*)object + *offset_ptr;
    }

    object = (char*)object + off->this_offset;
    return object;
}