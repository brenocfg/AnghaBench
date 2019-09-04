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
struct TYPE_3__ {unsigned int layer_idx; unsigned int level_idx; int layer_count; } ;
struct TYPE_4__ {TYPE_1__ texture; } ;
struct wined3d_view_desc {TYPE_2__ u; } ;
struct wined3d_texture {unsigned int level_count; } ;
struct wined3d_resource {scalar_t__ type; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 scalar_t__ WINED3D_RTYPE_BUFFER ; 
 scalar_t__ WINED3D_RTYPE_TEXTURE_3D ; 
 int /*<<< orphan*/  buffer_from_resource (struct wined3d_resource*) ; 
 struct wined3d_texture* texture_from_resource (struct wined3d_resource*) ; 
 int /*<<< orphan*/  wined3d_buffer_invalidate_location (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wined3d_texture_invalidate_location (struct wined3d_texture*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wined3d_view_invalidate_location(struct wined3d_resource *resource,
        const struct wined3d_view_desc *desc, DWORD location)
{
    unsigned int i, sub_resource_idx, layer_count;
    struct wined3d_texture *texture;

    if (resource->type == WINED3D_RTYPE_BUFFER)
    {
        wined3d_buffer_invalidate_location(buffer_from_resource(resource), location);
        return;
    }

    texture = texture_from_resource(resource);

    sub_resource_idx = desc->u.texture.layer_idx * texture->level_count + desc->u.texture.level_idx;
    layer_count = resource->type != WINED3D_RTYPE_TEXTURE_3D ? desc->u.texture.layer_count : 1;
    for (i = 0; i < layer_count; ++i, sub_resource_idx += texture->level_count)
        wined3d_texture_invalidate_location(texture, sub_resource_idx, location);
}