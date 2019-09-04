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
struct wined3d_resource {int format_flags; TYPE_1__* format; struct wined3d_device* device; } ;
struct wined3d_texture {struct wined3d_resource resource; } ;
struct wined3d_device {int dummy; } ;
struct wined3d_context {int /*<<< orphan*/  gl_info; } ;
struct wined3d_color_key {int dummy; } ;
struct wined3d_blitter {TYPE_2__* ops; struct wined3d_blitter* next; } ;
typedef  enum wined3d_texture_filter_type { ____Placeholder_wined3d_texture_filter_type } wined3d_texture_filter_type ;
typedef  enum wined3d_blit_op { ____Placeholder_wined3d_blit_op } wined3d_blit_op ;
struct TYPE_4__ {int /*<<< orphan*/  (* blitter_blit ) (struct wined3d_blitter*,int,struct wined3d_context*,struct wined3d_texture*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,struct wined3d_texture*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,struct wined3d_color_key const*,int) ;} ;
struct TYPE_3__ {scalar_t__ id; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int WINED3DFMT_FLAG_DEPTH ; 
 int WINED3DFMT_FLAG_STENCIL ; 
 int WINED3D_BLIT_OP_COLOR_BLIT ; 
 int WINED3D_BLIT_OP_DEPTH_BLIT ; 
 int WINED3D_BLIT_OP_RAW_BLIT ; 
 int /*<<< orphan*/  debug_d3dtexturefiltertype (int) ; 
 int /*<<< orphan*/  fbo_blitter_supported (int,int /*<<< orphan*/ ,struct wined3d_resource*,int /*<<< orphan*/ ,struct wined3d_resource*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct wined3d_blitter*,int,struct wined3d_context*,struct wined3d_texture*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,struct wined3d_texture*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,struct wined3d_color_key const*,int) ; 
 int /*<<< orphan*/  texture2d_blt_fbo (struct wined3d_device*,struct wined3d_context*,int,struct wined3d_texture*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,struct wined3d_texture*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  texture2d_depth_blt_fbo (struct wined3d_device*,struct wined3d_context*,struct wined3d_texture*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,struct wined3d_texture*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  wine_dbgstr_rect (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  wined3d_debug_location (int /*<<< orphan*/ ) ; 

__attribute__((used)) static DWORD fbo_blitter_blit(struct wined3d_blitter *blitter, enum wined3d_blit_op op,
        struct wined3d_context *context, struct wined3d_texture *src_texture, unsigned int src_sub_resource_idx,
        DWORD src_location, const RECT *src_rect, struct wined3d_texture *dst_texture,
        unsigned int dst_sub_resource_idx, DWORD dst_location, const RECT *dst_rect,
        const struct wined3d_color_key *colour_key, enum wined3d_texture_filter_type filter)
{
    struct wined3d_resource *src_resource, *dst_resource;
    enum wined3d_blit_op blit_op = op;
    struct wined3d_device *device;
    struct wined3d_blitter *next;

    TRACE("blitter %p, op %#x, context %p, src_texture %p, src_sub_resource_idx %u, src_location %s, src_rect %s, "
            "dst_texture %p, dst_sub_resource_idx %u, dst_location %s, dst_rect %s, colour_key %p, filter %s.\n",
            blitter, op, context, src_texture, src_sub_resource_idx, wined3d_debug_location(src_location),
            wine_dbgstr_rect(src_rect), dst_texture, dst_sub_resource_idx, wined3d_debug_location(dst_location),
            wine_dbgstr_rect(dst_rect), colour_key, debug_d3dtexturefiltertype(filter));

    src_resource = &src_texture->resource;
    dst_resource = &dst_texture->resource;

    device = dst_resource->device;

    if (blit_op == WINED3D_BLIT_OP_RAW_BLIT && dst_resource->format->id == src_resource->format->id)
    {
        if (dst_resource->format_flags & (WINED3DFMT_FLAG_DEPTH | WINED3DFMT_FLAG_STENCIL))
            blit_op = WINED3D_BLIT_OP_DEPTH_BLIT;
        else
            blit_op = WINED3D_BLIT_OP_COLOR_BLIT;
    }

    if (!fbo_blitter_supported(blit_op, context->gl_info,
            src_resource, src_location, dst_resource, dst_location))
    {
        if (!(next = blitter->next))
        {
            ERR("No blitter to handle blit op %#x.\n", op);
            return dst_location;
        }

        TRACE("Forwarding to blitter %p.\n", next);
        return next->ops->blitter_blit(next, op, context, src_texture, src_sub_resource_idx, src_location,
                src_rect, dst_texture, dst_sub_resource_idx, dst_location, dst_rect, colour_key, filter);
    }

    if (blit_op == WINED3D_BLIT_OP_COLOR_BLIT)
    {
        TRACE("Colour blit.\n");
        texture2d_blt_fbo(device, context, filter, src_texture, src_sub_resource_idx, src_location,
                src_rect, dst_texture, dst_sub_resource_idx, dst_location, dst_rect);
        return dst_location;
    }

    if (blit_op == WINED3D_BLIT_OP_DEPTH_BLIT)
    {
        TRACE("Depth/stencil blit.\n");
        texture2d_depth_blt_fbo(device, context, src_texture, src_sub_resource_idx, src_location,
                src_rect, dst_texture, dst_sub_resource_idx, dst_location, dst_rect);
        return dst_location;
    }

    ERR("This blitter does not implement blit op %#x.\n", blit_op);
    return dst_location;
}