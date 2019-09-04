#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  format; int /*<<< orphan*/  map_binding; } ;
struct wined3d_texture {unsigned int level_count; TYPE_1__ resource; } ;
struct TYPE_9__ {unsigned int left; unsigned int right; unsigned int bottom; unsigned int top; unsigned int back; unsigned int front; } ;
struct TYPE_11__ {unsigned int left; unsigned int right; unsigned int bottom; unsigned int top; unsigned int back; unsigned int front; } ;
struct wined3d_cs_blt_sub_resource {int flags; unsigned int src_sub_resource_idx; unsigned int dst_sub_resource_idx; TYPE_3__* dst_resource; TYPE_3__* src_resource; int /*<<< orphan*/  filter; int /*<<< orphan*/  fx; TYPE_2__ src_box; TYPE_5__ dst_box; } ;
struct wined3d_cs {int /*<<< orphan*/  device; } ;
struct wined3d_context {int dummy; } ;
struct wined3d_bo_address {int dummy; } ;
struct TYPE_10__ {scalar_t__ type; scalar_t__ format; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,...) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*,...) ; 
 int WINED3D_BLT_RAW ; 
 int /*<<< orphan*/  WINED3D_LOCATION_TEXTURE_RGB ; 
 scalar_t__ WINED3D_RTYPE_BUFFER ; 
 scalar_t__ WINED3D_RTYPE_TEXTURE_3D ; 
 int /*<<< orphan*/  buffer_from_resource (TYPE_3__*) ; 
 struct wined3d_context* context_acquire (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  context_release (struct wined3d_context*) ; 
 int /*<<< orphan*/  debug_d3dresourcetype (scalar_t__) ; 
 int /*<<< orphan*/  texture2d_blt (struct wined3d_texture*,unsigned int,TYPE_5__*,struct wined3d_texture*,int,TYPE_2__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct wined3d_texture* texture_from_resource (TYPE_3__*) ; 
 int /*<<< orphan*/  wined3d_buffer_copy (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  wined3d_const_bo_address (struct wined3d_bo_address*) ; 
 int /*<<< orphan*/  wined3d_debug_location (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wined3d_resource_release (TYPE_3__*) ; 
 int /*<<< orphan*/  wined3d_texture_bind_and_dirtify (struct wined3d_texture*,struct wined3d_context*,int /*<<< orphan*/ ) ; 
 unsigned int wined3d_texture_get_level_depth (struct wined3d_texture*,unsigned int) ; 
 unsigned int wined3d_texture_get_level_height (struct wined3d_texture*,unsigned int) ; 
 unsigned int wined3d_texture_get_level_width (struct wined3d_texture*,unsigned int) ; 
 int /*<<< orphan*/  wined3d_texture_get_memory (struct wined3d_texture*,unsigned int,struct wined3d_bo_address*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wined3d_texture_get_pitch (struct wined3d_texture*,int,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  wined3d_texture_invalidate_location (struct wined3d_texture*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wined3d_texture_load_location (struct wined3d_texture*,unsigned int,struct wined3d_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wined3d_texture_prepare_texture (struct wined3d_texture*,struct wined3d_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wined3d_texture_upload_data (struct wined3d_texture*,unsigned int,struct wined3d_context*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wined3d_texture_validate_location (struct wined3d_texture*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wined3d_cs_exec_blt_sub_resource(struct wined3d_cs *cs, const void *data)
{
    const struct wined3d_cs_blt_sub_resource *op = data;

    if (op->dst_resource->type == WINED3D_RTYPE_BUFFER)
    {
        wined3d_buffer_copy(buffer_from_resource(op->dst_resource), op->dst_box.left,
                buffer_from_resource(op->src_resource), op->src_box.left,
                op->src_box.right - op->src_box.left);
    }
    else if (op->dst_resource->type == WINED3D_RTYPE_TEXTURE_3D)
    {
        struct wined3d_texture *src_texture, *dst_texture;
        unsigned int level, update_w, update_h, update_d;
        unsigned int row_pitch, slice_pitch;
        struct wined3d_context *context;
        struct wined3d_bo_address addr;

        if (op->flags & ~WINED3D_BLT_RAW)
        {
            FIXME("Flags %#x not implemented for %s resources.\n",
                    op->flags, debug_d3dresourcetype(op->dst_resource->type));
            goto error;
        }

        if (!(op->flags & WINED3D_BLT_RAW) && op->src_resource->format != op->dst_resource->format)
        {
            FIXME("Format conversion not implemented for %s resources.\n",
                    debug_d3dresourcetype(op->dst_resource->type));
            goto error;
        }

        update_w = op->dst_box.right - op->dst_box.left;
        update_h = op->dst_box.bottom - op->dst_box.top;
        update_d = op->dst_box.back - op->dst_box.front;
        if (op->src_box.right - op->src_box.left != update_w
                || op->src_box.bottom - op->src_box.top != update_h
                || op->src_box.back - op->src_box.front != update_d)
        {
            FIXME("Stretching not implemented for %s resources.\n",
                    debug_d3dresourcetype(op->dst_resource->type));
            goto error;
        }

        dst_texture = texture_from_resource(op->dst_resource);
        src_texture = texture_from_resource(op->src_resource);

        context = context_acquire(cs->device, NULL, 0);

        if (!wined3d_texture_load_location(src_texture, op->src_sub_resource_idx,
                context, src_texture->resource.map_binding))
        {
            ERR("Failed to load source sub-resource into %s.\n",
                    wined3d_debug_location(src_texture->resource.map_binding));
            context_release(context);
            goto error;
        }

        level = op->dst_sub_resource_idx % dst_texture->level_count;
        if (update_w == wined3d_texture_get_level_width(dst_texture, level)
                && update_h == wined3d_texture_get_level_height(dst_texture, level)
                && update_d == wined3d_texture_get_level_depth(dst_texture, level))
        {
            wined3d_texture_prepare_texture(dst_texture, context, FALSE);
        }
        else if (!wined3d_texture_load_location(dst_texture, op->dst_sub_resource_idx,
                context, WINED3D_LOCATION_TEXTURE_RGB))
        {
            ERR("Failed to load destination sub-resource.\n");
            context_release(context);
            goto error;
        }

        wined3d_texture_get_memory(src_texture, op->src_sub_resource_idx, &addr, src_texture->resource.map_binding);
        wined3d_texture_get_pitch(src_texture, op->src_sub_resource_idx % src_texture->level_count,
                &row_pitch, &slice_pitch);

        wined3d_texture_bind_and_dirtify(dst_texture, context, FALSE);
        wined3d_texture_upload_data(dst_texture, op->dst_sub_resource_idx, context,
                dst_texture->resource.format, &op->src_box, wined3d_const_bo_address(&addr),
                row_pitch, slice_pitch, op->dst_box.left, op->dst_box.top, op->dst_box.front, FALSE);
        wined3d_texture_validate_location(dst_texture, op->dst_sub_resource_idx, WINED3D_LOCATION_TEXTURE_RGB);
        wined3d_texture_invalidate_location(dst_texture, op->dst_sub_resource_idx, ~WINED3D_LOCATION_TEXTURE_RGB);

        context_release(context);
    }
    else
    {
        if (FAILED(texture2d_blt(texture_from_resource(op->dst_resource), op->dst_sub_resource_idx,
                &op->dst_box, texture_from_resource(op->src_resource), op->src_sub_resource_idx,
                &op->src_box, op->flags, &op->fx, op->filter)))
            FIXME("Blit failed.\n");
    }

error:
    if (op->src_resource)
        wined3d_resource_release(op->src_resource);
    wined3d_resource_release(op->dst_resource);
}