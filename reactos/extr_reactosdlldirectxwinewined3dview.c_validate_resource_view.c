#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ level_idx; int level_count; unsigned int layer_count; unsigned int layer_idx; } ;
struct TYPE_12__ {unsigned int start_idx; unsigned int count; } ;
struct TYPE_14__ {TYPE_6__ texture; TYPE_5__ buffer; } ;
struct wined3d_view_desc {scalar_t__ format_id; int flags; TYPE_7__ u; } ;
struct wined3d_texture {unsigned int layer_count; scalar_t__ level_count; } ;
struct wined3d_resource {scalar_t__ type; struct wined3d_format const* format; int /*<<< orphan*/  usage; TYPE_2__* device; } ;
struct wined3d_gl_info {int dummy; } ;
struct wined3d_format {scalar_t__ id; unsigned int byte_count; } ;
struct TYPE_11__ {unsigned int size; } ;
struct TYPE_10__ {int structure_byte_stride; } ;
struct wined3d_buffer {TYPE_4__ resource; TYPE_3__ desc; } ;
struct TYPE_9__ {TYPE_1__* adapter; } ;
struct TYPE_8__ {struct wined3d_gl_info gl_info; } ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ WINED3DFMT_R32_TYPELESS ; 
 scalar_t__ WINED3DFMT_R32_UINT ; 
 scalar_t__ WINED3DFMT_UNKNOWN ; 
 scalar_t__ WINED3D_RTYPE_BUFFER ; 
 scalar_t__ WINED3D_RTYPE_TEXTURE_3D ; 
 int WINED3D_VIEW_BUFFER_RAW ; 
 struct wined3d_buffer* buffer_from_resource (struct wined3d_resource*) ; 
 int /*<<< orphan*/  debug_d3dformat (scalar_t__) ; 
 struct wined3d_texture* texture_from_resource (struct wined3d_resource*) ; 
 scalar_t__ wined3d_format_is_typeless (struct wined3d_format const*) ; 
 int /*<<< orphan*/  wined3d_formats_are_srgb_variants (scalar_t__,scalar_t__) ; 
 struct wined3d_format* wined3d_get_format (struct wined3d_gl_info const*,scalar_t__,int /*<<< orphan*/ ) ; 
 unsigned int wined3d_texture_get_level_depth (struct wined3d_texture*,scalar_t__) ; 

__attribute__((used)) static const struct wined3d_format *validate_resource_view(const struct wined3d_view_desc *desc,
        struct wined3d_resource *resource, BOOL mip_slice, BOOL allow_srgb_toggle)
{
    const struct wined3d_gl_info *gl_info = &resource->device->adapter->gl_info;
    const struct wined3d_format *format;

    format = wined3d_get_format(gl_info, desc->format_id, resource->usage);
    if (resource->type == WINED3D_RTYPE_BUFFER && (desc->flags & WINED3D_VIEW_BUFFER_RAW))
    {
        if (format->id != WINED3DFMT_R32_TYPELESS)
        {
            WARN("Invalid format %s for raw buffer view.\n", debug_d3dformat(format->id));
            return NULL;
        }

        format = wined3d_get_format(gl_info, WINED3DFMT_R32_UINT, resource->usage);
    }

    if (wined3d_format_is_typeless(format))
    {
        WARN("Trying to create view for typeless format %s.\n", debug_d3dformat(format->id));
        return NULL;
    }

    if (resource->type == WINED3D_RTYPE_BUFFER)
    {
        struct wined3d_buffer *buffer = buffer_from_resource(resource);
        unsigned int buffer_size, element_size;

        if (buffer->desc.structure_byte_stride)
        {
            if (desc->format_id != WINED3DFMT_UNKNOWN)
            {
                WARN("Invalid format %s for structured buffer view.\n", debug_d3dformat(desc->format_id));
                return NULL;
            }

            format = wined3d_get_format(gl_info, WINED3DFMT_R32_UINT, resource->usage);
            element_size = buffer->desc.structure_byte_stride;
        }
        else
        {
            element_size = format->byte_count;
        }

        if (!element_size)
            return NULL;

        buffer_size = buffer->resource.size / element_size;
        if (desc->u.buffer.start_idx >= buffer_size
                || desc->u.buffer.count > buffer_size - desc->u.buffer.start_idx)
            return NULL;
    }
    else
    {
        struct wined3d_texture *texture = texture_from_resource(resource);
        unsigned int depth_or_layer_count;

        if (resource->format->id != format->id && !wined3d_format_is_typeless(resource->format)
                && (!allow_srgb_toggle || !wined3d_formats_are_srgb_variants(resource->format->id, format->id)))
        {
            WARN("Trying to create incompatible view for non typeless format %s.\n",
                    debug_d3dformat(format->id));
            return NULL;
        }

        if (mip_slice && resource->type == WINED3D_RTYPE_TEXTURE_3D)
            depth_or_layer_count = wined3d_texture_get_level_depth(texture, desc->u.texture.level_idx);
        else
            depth_or_layer_count = texture->layer_count;

        if (!desc->u.texture.level_count
                || (mip_slice && desc->u.texture.level_count != 1)
                || desc->u.texture.level_idx >= texture->level_count
                || desc->u.texture.level_count > texture->level_count - desc->u.texture.level_idx
                || !desc->u.texture.layer_count
                || desc->u.texture.layer_idx >= depth_or_layer_count
                || desc->u.texture.layer_count > depth_or_layer_count - desc->u.texture.layer_idx)
            return NULL;
    }

    return format;
}