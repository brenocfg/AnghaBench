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
typedef  enum wined3d_format_id { ____Placeholder_wined3d_format_id } wined3d_format_id ;
struct TYPE_3__ {int id; int idx; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 int WINED3D_FORMAT_FOURCC_BASE ; 
 TYPE_1__* format_index_remap ; 

__attribute__((used)) static inline int get_format_idx(enum wined3d_format_id format_id)
{
    unsigned int i;

    if (format_id < WINED3D_FORMAT_FOURCC_BASE)
        return format_id;

    for (i = 0; i < ARRAY_SIZE(format_index_remap); ++i)
    {
        if (format_index_remap[i].id == format_id)
            return format_index_remap[i].idx;
    }

    return -1;
}