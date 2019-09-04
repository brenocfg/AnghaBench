#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int size; } ;
struct wined3d_buffer {int modified_areas; TYPE_2__ resource; TYPE_1__* maps; int /*<<< orphan*/  maps_size; } ;
struct TYPE_3__ {unsigned int offset; unsigned int size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  wined3d_array_reserve (void**,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void buffer_invalidate_bo_range(struct wined3d_buffer *buffer, unsigned int offset, unsigned int size)
{
    if (!offset && (!size || size == buffer->resource.size))
        goto invalidate_all;

    if (offset > buffer->resource.size || size > buffer->resource.size - offset)
    {
        WARN("Invalid range specified, invalidating entire buffer.\n");
        goto invalidate_all;
    }

    if (!wined3d_array_reserve((void **)&buffer->maps, &buffer->maps_size,
            buffer->modified_areas + 1, sizeof(*buffer->maps)))
    {
        ERR("Failed to allocate maps array, invalidating entire buffer.\n");
        goto invalidate_all;
    }

    buffer->maps[buffer->modified_areas].offset = offset;
    buffer->maps[buffer->modified_areas].size = size;
    ++buffer->modified_areas;
    return;

invalidate_all:
    buffer->modified_areas = 1;
    buffer->maps[0].offset = 0;
    buffer->maps[0].size = buffer->resource.size;
}