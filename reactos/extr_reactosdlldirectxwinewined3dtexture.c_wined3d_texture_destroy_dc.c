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
struct wined3d_texture_idx {unsigned int sub_resource_idx; struct wined3d_texture* texture; } ;
struct TYPE_4__ {int /*<<< orphan*/  map_binding; struct wined3d_device* device; } ;
struct wined3d_texture {TYPE_1__ resource; struct wined3d_dc_info* dc_info; } ;
struct wined3d_device {scalar_t__ d3d_initialized; } ;
struct wined3d_dc_info {int /*<<< orphan*/ * bitmap; int /*<<< orphan*/ * dc; } ;
struct wined3d_context {int dummy; } ;
struct wined3d_bo_address {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/ * hBitmap; int /*<<< orphan*/ * hDc; } ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_2__ D3DKMT_DESTROYDCFROMMEMORY ;

/* Variables and functions */
 int /*<<< orphan*/  D3DKMTDestroyDCFromMemory (TYPE_2__*) ; 
 int /*<<< orphan*/  ERR (char*,struct wined3d_texture*,...) ; 
 int /*<<< orphan*/  GL_PIXEL_UNPACK_BUFFER ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct wined3d_context* context_acquire (struct wined3d_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  context_release (struct wined3d_context*) ; 
 int /*<<< orphan*/  context_unmap_bo_address (struct wined3d_context*,struct wined3d_bo_address*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wined3d_texture_get_memory (struct wined3d_texture*,unsigned int,struct wined3d_bo_address*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wined3d_texture_destroy_dc(void *object)
{
    const struct wined3d_texture_idx *idx = object;
    D3DKMT_DESTROYDCFROMMEMORY destroy_desc;
    struct wined3d_context *context = NULL;
    struct wined3d_texture *texture;
    struct wined3d_dc_info *dc_info;
    struct wined3d_bo_address data;
    unsigned int sub_resource_idx;
    struct wined3d_device *device;
    NTSTATUS status;

    texture = idx->texture;
    sub_resource_idx = idx->sub_resource_idx;
    device = texture->resource.device;
    dc_info = &texture->dc_info[sub_resource_idx];

    if (!dc_info->dc)
    {
        ERR("Sub-resource {%p, %u} has no DC.\n", texture, sub_resource_idx);
        return;
    }

    TRACE("dc %p, bitmap %p.\n", dc_info->dc, dc_info->bitmap);

    destroy_desc.hDc = dc_info->dc;
    destroy_desc.hBitmap = dc_info->bitmap;
    if ((status = D3DKMTDestroyDCFromMemory(&destroy_desc)))
        ERR("Failed to destroy dc, status %#x.\n", status);
    dc_info->dc = NULL;
    dc_info->bitmap = NULL;

    if (device->d3d_initialized)
        context = context_acquire(device, NULL, 0);

    wined3d_texture_get_memory(texture, sub_resource_idx, &data, texture->resource.map_binding);
    context_unmap_bo_address(context, &data, GL_PIXEL_UNPACK_BUFFER);

    if (context)
        context_release(context);
}