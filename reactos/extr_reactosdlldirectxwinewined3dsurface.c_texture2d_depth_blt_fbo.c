#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_11__ {int format_flags; TYPE_1__* format; } ;
struct wined3d_texture {unsigned int level_count; TYPE_10__ resource; } ;
struct TYPE_15__ {int /*<<< orphan*/  (* glBlitFramebuffer ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_13__ {int /*<<< orphan*/  (* p_glDisable ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glStencilMask ) (unsigned int) ;int /*<<< orphan*/  (* p_glDepthMask ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_14__ {TYPE_2__ gl; } ;
struct wined3d_gl_info {TYPE_4__ fbo_ops; TYPE_3__ gl_ops; scalar_t__* supported; } ;
struct wined3d_device {int dummy; } ;
struct wined3d_context {struct wined3d_gl_info* gl_info; } ;
struct TYPE_16__ {int /*<<< orphan*/  bottom; int /*<<< orphan*/  right; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct TYPE_12__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_5__ RECT ;
typedef  int GLbitfield ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ,...) ; 
 size_t EXT_STENCIL_TWO_SIDE ; 
 int GL_DEPTH_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_DRAW_FRAMEBUFFER ; 
 int /*<<< orphan*/  GL_NEAREST ; 
 int /*<<< orphan*/  GL_NONE ; 
 int /*<<< orphan*/  GL_READ_FRAMEBUFFER ; 
 int /*<<< orphan*/  GL_SCISSOR_TEST ; 
 int GL_STENCIL_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_STENCIL_TEST_TWO_SIDE_EXT ; 
 int /*<<< orphan*/  GL_TRUE ; 
 int /*<<< orphan*/  STATE_FRAMEBUFFER ; 
 int /*<<< orphan*/  STATE_RENDER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,struct wined3d_device const*,struct wined3d_texture*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wined3d_texture*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int WINED3DFMT_FLAG_DEPTH ; 
 int WINED3DFMT_FLAG_STENCIL ; 
 int /*<<< orphan*/  WINED3D_RS_SCISSORTESTENABLE ; 
 int /*<<< orphan*/  WINED3D_RS_STENCILWRITEMASK ; 
 int /*<<< orphan*/  WINED3D_RS_TWOSIDEDSTENCILMODE ; 
 int /*<<< orphan*/  WINED3D_RS_ZWRITEENABLE ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 int /*<<< orphan*/  context_apply_fbo_state_blit (struct wined3d_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_10__*,unsigned int,int) ; 
 int /*<<< orphan*/  context_check_fbo_status (struct wined3d_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  context_invalidate_state (struct wined3d_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  context_set_draw_buffer (struct wined3d_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_d3dformat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (unsigned int) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  texture2d_is_full_rect (struct wined3d_texture*,unsigned int,TYPE_5__ const*) ; 
 int /*<<< orphan*/  wine_dbgstr_rect (TYPE_5__ const*) ; 
 int /*<<< orphan*/  wined3d_debug_location (int) ; 
 int /*<<< orphan*/  wined3d_texture_load_location (struct wined3d_texture*,unsigned int,struct wined3d_context*,int) ; 
 int /*<<< orphan*/  wined3d_texture_prepare_location (struct wined3d_texture*,unsigned int,struct wined3d_context*,int) ; 

__attribute__((used)) static void texture2d_depth_blt_fbo(const struct wined3d_device *device, struct wined3d_context *context,
        struct wined3d_texture *src_texture, unsigned int src_sub_resource_idx, DWORD src_location,
        const RECT *src_rect, struct wined3d_texture *dst_texture, unsigned int dst_sub_resource_idx,
        DWORD dst_location, const RECT *dst_rect)
{
    const struct wined3d_gl_info *gl_info = context->gl_info;
    DWORD src_mask, dst_mask;
    GLbitfield gl_mask;

    TRACE("device %p, src_texture %p, src_sub_resource_idx %u, src_location %s, src_rect %s, "
            "dst_texture %p, dst_sub_resource_idx %u, dst_location %s, dst_rect %s.\n", device,
            src_texture, src_sub_resource_idx, wined3d_debug_location(src_location), wine_dbgstr_rect(src_rect),
            dst_texture, dst_sub_resource_idx, wined3d_debug_location(dst_location), wine_dbgstr_rect(dst_rect));

    src_mask = src_texture->resource.format_flags & (WINED3DFMT_FLAG_DEPTH | WINED3DFMT_FLAG_STENCIL);
    dst_mask = dst_texture->resource.format_flags & (WINED3DFMT_FLAG_DEPTH | WINED3DFMT_FLAG_STENCIL);

    if (src_mask != dst_mask)
    {
        ERR("Incompatible formats %s and %s.\n",
                debug_d3dformat(src_texture->resource.format->id),
                debug_d3dformat(dst_texture->resource.format->id));
        return;
    }

    if (!src_mask)
    {
        ERR("Not a depth / stencil format: %s.\n",
                debug_d3dformat(src_texture->resource.format->id));
        return;
    }

    gl_mask = 0;
    if (src_mask & WINED3DFMT_FLAG_DEPTH)
        gl_mask |= GL_DEPTH_BUFFER_BIT;
    if (src_mask & WINED3DFMT_FLAG_STENCIL)
        gl_mask |= GL_STENCIL_BUFFER_BIT;

    /* Make sure the locations are up-to-date. Loading the destination
     * surface isn't required if the entire surface is overwritten. */
    wined3d_texture_load_location(src_texture, src_sub_resource_idx, context, src_location);
    if (!texture2d_is_full_rect(dst_texture, dst_sub_resource_idx % dst_texture->level_count, dst_rect))
        wined3d_texture_load_location(dst_texture, dst_sub_resource_idx, context, dst_location);
    else
        wined3d_texture_prepare_location(dst_texture, dst_sub_resource_idx, context, dst_location);

    context_apply_fbo_state_blit(context, GL_READ_FRAMEBUFFER, NULL, 0,
            &src_texture->resource, src_sub_resource_idx, src_location);
    context_check_fbo_status(context, GL_READ_FRAMEBUFFER);

    context_apply_fbo_state_blit(context, GL_DRAW_FRAMEBUFFER, NULL, 0,
            &dst_texture->resource, dst_sub_resource_idx, dst_location);
    context_set_draw_buffer(context, GL_NONE);
    context_check_fbo_status(context, GL_DRAW_FRAMEBUFFER);
    context_invalidate_state(context, STATE_FRAMEBUFFER);

    if (gl_mask & GL_DEPTH_BUFFER_BIT)
    {
        gl_info->gl_ops.gl.p_glDepthMask(GL_TRUE);
        context_invalidate_state(context, STATE_RENDER(WINED3D_RS_ZWRITEENABLE));
    }
    if (gl_mask & GL_STENCIL_BUFFER_BIT)
    {
        if (context->gl_info->supported[EXT_STENCIL_TWO_SIDE])
        {
            gl_info->gl_ops.gl.p_glDisable(GL_STENCIL_TEST_TWO_SIDE_EXT);
            context_invalidate_state(context, STATE_RENDER(WINED3D_RS_TWOSIDEDSTENCILMODE));
        }
        gl_info->gl_ops.gl.p_glStencilMask(~0U);
        context_invalidate_state(context, STATE_RENDER(WINED3D_RS_STENCILWRITEMASK));
    }

    gl_info->gl_ops.gl.p_glDisable(GL_SCISSOR_TEST);
    context_invalidate_state(context, STATE_RENDER(WINED3D_RS_SCISSORTESTENABLE));

    gl_info->fbo_ops.glBlitFramebuffer(src_rect->left, src_rect->top, src_rect->right, src_rect->bottom,
            dst_rect->left, dst_rect->top, dst_rect->right, dst_rect->bottom, gl_mask, GL_NEAREST);
    checkGLcall("glBlitFramebuffer()");
}