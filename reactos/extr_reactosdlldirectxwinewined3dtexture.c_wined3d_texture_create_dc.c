#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct wined3d_texture_idx {unsigned int sub_resource_idx; struct wined3d_texture* texture; } ;
struct TYPE_5__ {int /*<<< orphan*/  map_binding; struct wined3d_format* format; struct wined3d_device* device; } ;
struct wined3d_texture {unsigned int level_count; unsigned int layer_count; struct wined3d_dc_info* dc_info; TYPE_2__* sub_resources; TYPE_1__ resource; } ;
struct wined3d_format {scalar_t__ ddi_format; int /*<<< orphan*/  id; } ;
struct wined3d_device {scalar_t__ d3d_initialized; } ;
struct wined3d_dc_info {int /*<<< orphan*/  bitmap; int /*<<< orphan*/  dc; } ;
struct wined3d_context {int dummy; } ;
struct wined3d_bo_address {int dummy; } ;
struct TYPE_7__ {unsigned int Pitch; int /*<<< orphan*/  hBitmap; int /*<<< orphan*/  hDc; int /*<<< orphan*/  hDeviceDc; int /*<<< orphan*/ * pColorTable; int /*<<< orphan*/  Height; int /*<<< orphan*/  Width; scalar_t__ Format; int /*<<< orphan*/  pMemory; } ;
struct TYPE_6__ {int /*<<< orphan*/  size; } ;
typedef  scalar_t__ NTSTATUS ;
typedef  TYPE_3__ D3DKMT_CREATEDCFROMMEMORY ;

/* Variables and functions */
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ *) ; 
 scalar_t__ D3DKMTCreateDCFromMemory (TYPE_3__*) ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  GL_PIXEL_UNPACK_BUFFER ; 
 int /*<<< orphan*/  TRACE (char*,struct wined3d_texture*,unsigned int,...) ; 
 int /*<<< orphan*/  WARN (char*,scalar_t__) ; 
 int WINED3D_MAP_READ ; 
 int WINED3D_MAP_WRITE ; 
 struct wined3d_context* context_acquire (struct wined3d_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  context_map_bo_address (struct wined3d_context*,struct wined3d_bo_address*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  context_release (struct wined3d_context*) ; 
 scalar_t__ debug_d3dformat (int /*<<< orphan*/ ) ; 
 struct wined3d_dc_info* heap_calloc (unsigned int,int) ; 
 int /*<<< orphan*/  wined3d_texture_get_level_height (struct wined3d_texture*,unsigned int) ; 
 int /*<<< orphan*/  wined3d_texture_get_level_width (struct wined3d_texture*,unsigned int) ; 
 int /*<<< orphan*/  wined3d_texture_get_memory (struct wined3d_texture*,unsigned int,struct wined3d_bo_address*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wined3d_texture_get_pitch (struct wined3d_texture*,unsigned int,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  wined3d_texture_invalidate_location (struct wined3d_texture*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wined3d_texture_load_location (struct wined3d_texture*,unsigned int,struct wined3d_context*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wined3d_texture_create_dc(void *object)
{
    const struct wined3d_texture_idx *idx = object;
    struct wined3d_context *context = NULL;
    unsigned int sub_resource_idx, level;
    const struct wined3d_format *format;
    unsigned int row_pitch, slice_pitch;
    struct wined3d_texture *texture;
    struct wined3d_dc_info *dc_info;
    struct wined3d_bo_address data;
    D3DKMT_CREATEDCFROMMEMORY desc;
    struct wined3d_device *device;
    NTSTATUS status;

    TRACE("texture %p, sub_resource_idx %u.\n", idx->texture, idx->sub_resource_idx);

    texture = idx->texture;
    sub_resource_idx = idx->sub_resource_idx;
    level = sub_resource_idx % texture->level_count;
    device = texture->resource.device;

    format = texture->resource.format;
    if (!format->ddi_format)
    {
        WARN("Cannot create a DC for format %s.\n", debug_d3dformat(format->id));
        return;
    }

    if (!texture->dc_info)
    {
        unsigned int sub_count = texture->level_count * texture->layer_count;

        if (!(texture->dc_info = heap_calloc(sub_count, sizeof(*texture->dc_info))))
        {
            ERR("Failed to allocate DC info.\n");
            return;
        }
    }

    if (device->d3d_initialized)
        context = context_acquire(device, NULL, 0);

    wined3d_texture_load_location(texture, sub_resource_idx, context, texture->resource.map_binding);
    wined3d_texture_invalidate_location(texture, sub_resource_idx, ~texture->resource.map_binding);
    wined3d_texture_get_pitch(texture, level, &row_pitch, &slice_pitch);
    wined3d_texture_get_memory(texture, sub_resource_idx, &data, texture->resource.map_binding);
    desc.pMemory = context_map_bo_address(context, &data,
            texture->sub_resources[sub_resource_idx].size,
            GL_PIXEL_UNPACK_BUFFER, WINED3D_MAP_READ | WINED3D_MAP_WRITE);

    if (context)
        context_release(context);

    desc.Format = format->ddi_format;
    desc.Width = wined3d_texture_get_level_width(texture, level);
    desc.Height = wined3d_texture_get_level_height(texture, level);
    desc.Pitch = row_pitch;
    desc.hDeviceDc = CreateCompatibleDC(NULL);
    desc.pColorTable = NULL;

    status = D3DKMTCreateDCFromMemory(&desc);
    DeleteDC(desc.hDeviceDc);
    if (status)
    {
        WARN("Failed to create DC, status %#x.\n", status);
        return;
    }

    dc_info = &texture->dc_info[sub_resource_idx];
    dc_info->dc = desc.hDc;
    dc_info->bitmap = desc.hBitmap;

    TRACE("Created DC %p, bitmap %p for texture %p, %u.\n", dc_info->dc, dc_info->bitmap, texture, sub_resource_idx);
}