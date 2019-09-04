#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wined3d_texture_sub_resource {int /*<<< orphan*/  offset; int /*<<< orphan*/  buffer_object; } ;
struct TYPE_2__ {int /*<<< orphan*/ * heap_memory; } ;
struct wined3d_texture {TYPE_1__ resource; int /*<<< orphan*/ * user_memory; struct wined3d_texture_sub_resource* sub_resources; } ;
struct wined3d_bo_address {int /*<<< orphan*/  buffer_object; int /*<<< orphan*/ * addr; } ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,struct wined3d_texture*,unsigned int,struct wined3d_bo_address*,int /*<<< orphan*/ ) ; 
 int WINED3D_LOCATION_BUFFER ; 
 int WINED3D_LOCATION_SYSMEM ; 
 int WINED3D_LOCATION_USER_MEMORY ; 
 int /*<<< orphan*/  wined3d_debug_location (int) ; 

void wined3d_texture_get_memory(struct wined3d_texture *texture, unsigned int sub_resource_idx,
        struct wined3d_bo_address *data, DWORD locations)
{
    struct wined3d_texture_sub_resource *sub_resource;

    TRACE("texture %p, sub_resource_idx %u, data %p, locations %s.\n",
            texture, sub_resource_idx, data, wined3d_debug_location(locations));

    sub_resource = &texture->sub_resources[sub_resource_idx];
    if (locations & WINED3D_LOCATION_BUFFER)
    {
        data->addr = NULL;
        data->buffer_object = sub_resource->buffer_object;
        return;
    }
    if (locations & WINED3D_LOCATION_USER_MEMORY)
    {
        data->addr = texture->user_memory;
        data->buffer_object = 0;
        return;
    }
    if (locations & WINED3D_LOCATION_SYSMEM)
    {
        data->addr = texture->resource.heap_memory;
        data->addr += sub_resource->offset;
        data->buffer_object = 0;
        return;
    }

    ERR("Unexpected locations %s.\n", wined3d_debug_location(locations));
    data->addr = NULL;
    data->buffer_object = 0;
}