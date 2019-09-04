#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_13__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_1__* format; } ;
struct wined3d_texture {unsigned int level_count; TYPE_4__* swapchain; TYPE_13__ resource; } ;
struct TYPE_19__ {int /*<<< orphan*/  (* p_glFlush ) () ;int /*<<< orphan*/  (* p_glDisable ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glColorMask ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glReadBuffer ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_20__ {TYPE_5__ gl; } ;
struct TYPE_17__ {int /*<<< orphan*/  (* glBlitFramebuffer ) (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct wined3d_gl_info {TYPE_6__ gl_ops; TYPE_3__ fbo_ops; } ;
struct wined3d_device {int dummy; } ;
struct TYPE_16__ {unsigned int sub_resource_idx; struct wined3d_texture* texture; } ;
struct wined3d_context {int /*<<< orphan*/  win_handle; struct wined3d_gl_info* gl_info; int /*<<< orphan*/  valid; TYPE_2__ current_rt; } ;
typedef  enum wined3d_texture_filter_type { ____Placeholder_wined3d_texture_filter_type } wined3d_texture_filter_type ;
struct TYPE_21__ {scalar_t__ bottom; scalar_t__ right; scalar_t__ top; scalar_t__ left; } ;
struct TYPE_18__ {struct wined3d_texture* front_buffer; } ;
struct TYPE_15__ {scalar_t__ id; } ;
typedef  TYPE_7__ RECT ;
typedef  int /*<<< orphan*/  GLenum ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GL_COLOR_ATTACHMENT0 ; 
 int /*<<< orphan*/  GL_COLOR_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_DRAW_FRAMEBUFFER ; 
 int /*<<< orphan*/  GL_LINEAR ; 
 int /*<<< orphan*/  GL_NEAREST ; 
 int /*<<< orphan*/  GL_READ_FRAMEBUFFER ; 
 int /*<<< orphan*/  GL_SCISSOR_TEST ; 
 int /*<<< orphan*/  GL_TRUE ; 
 int MAX_RENDER_TARGETS ; 
 int /*<<< orphan*/  STATE_FRAMEBUFFER ; 
 int /*<<< orphan*/  STATE_RENDER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,struct wined3d_texture*,...) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 scalar_t__ WINED3D_LOCATION_DRAWABLE ; 
 scalar_t__ WINED3D_LOCATION_RB_RESOLVED ; 
 int /*<<< orphan*/  WINED3D_RS_COLORWRITE (int) ; 
 int /*<<< orphan*/  WINED3D_RS_SCISSORTESTENABLE ; 
#define  WINED3D_TEXF_LINEAR 130 
#define  WINED3D_TEXF_NONE 129 
#define  WINED3D_TEXF_POINT 128 
 scalar_t__ abs (scalar_t__) ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 struct wined3d_context* context_acquire (struct wined3d_device const*,struct wined3d_texture*,unsigned int) ; 
 int /*<<< orphan*/  context_apply_fbo_state_blit (struct wined3d_context*,int /*<<< orphan*/ ,TYPE_13__*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  context_check_fbo_status (struct wined3d_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  context_invalidate_state (struct wined3d_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  context_release (struct wined3d_context*) ; 
 int /*<<< orphan*/  context_restore (struct wined3d_context*,struct wined3d_texture*,unsigned int) ; 
 int /*<<< orphan*/  context_set_draw_buffer (struct wined3d_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_d3dtexturefiltertype (int) ; 
 scalar_t__ is_multisample_location (struct wined3d_texture*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 () ; 
 int /*<<< orphan*/  texture2d_is_full_rect (struct wined3d_texture*,unsigned int,TYPE_7__ const*) ; 
 int /*<<< orphan*/  wine_dbgstr_rect (TYPE_7__ const*) ; 
 int /*<<< orphan*/  wined3d_debug_location (scalar_t__) ; 
 int /*<<< orphan*/  wined3d_texture_get_gl_buffer (struct wined3d_texture*) ; 
 int /*<<< orphan*/  wined3d_texture_load_location (struct wined3d_texture*,unsigned int,struct wined3d_context*,scalar_t__) ; 
 int /*<<< orphan*/  wined3d_texture_prepare_location (struct wined3d_texture*,unsigned int,struct wined3d_context*,scalar_t__) ; 
 int /*<<< orphan*/  wined3d_texture_translate_drawable_coords (struct wined3d_texture*,int /*<<< orphan*/ ,TYPE_7__*) ; 

__attribute__((used)) static void texture2d_blt_fbo(const struct wined3d_device *device, struct wined3d_context *context,
        enum wined3d_texture_filter_type filter, struct wined3d_texture *src_texture,
        unsigned int src_sub_resource_idx, DWORD src_location, const RECT *src_rect,
        struct wined3d_texture *dst_texture, unsigned int dst_sub_resource_idx, DWORD dst_location,
        const RECT *dst_rect)
{
    struct wined3d_texture *required_texture, *restore_texture;
    unsigned int required_idx, restore_idx;
    const struct wined3d_gl_info *gl_info;
    GLenum gl_filter;
    GLenum buffer;
    RECT s, d;
    int i;

    TRACE("device %p, context %p, filter %s, src_texture %p, src_sub_resource_idx %u, src_location %s, "
            "src_rect %s, dst_texture %p, dst_sub_resource_idx %u, dst_location %s, dst_rect %s.\n",
            device, context, debug_d3dtexturefiltertype(filter), src_texture, src_sub_resource_idx,
            wined3d_debug_location(src_location), wine_dbgstr_rect(src_rect), dst_texture,
            dst_sub_resource_idx, wined3d_debug_location(dst_location), wine_dbgstr_rect(dst_rect));

    switch (filter)
    {
        case WINED3D_TEXF_LINEAR:
            gl_filter = GL_LINEAR;
            break;

        default:
            FIXME("Unsupported filter mode %s (%#x).\n", debug_d3dtexturefiltertype(filter), filter);
        case WINED3D_TEXF_NONE:
        case WINED3D_TEXF_POINT:
            gl_filter = GL_NEAREST;
            break;
    }

    /* Resolve the source surface first if needed. */
    if (is_multisample_location(src_texture, src_location)
            && (src_texture->resource.format->id != dst_texture->resource.format->id
                || abs(src_rect->bottom - src_rect->top) != abs(dst_rect->bottom - dst_rect->top)
                || abs(src_rect->right - src_rect->left) != abs(dst_rect->right - dst_rect->left)))
        src_location = WINED3D_LOCATION_RB_RESOLVED;

    /* Make sure the locations are up-to-date. Loading the destination
     * surface isn't required if the entire surface is overwritten. (And is
     * in fact harmful if we're being called by surface_load_location() with
     * the purpose of loading the destination surface.) */
    wined3d_texture_load_location(src_texture, src_sub_resource_idx, context, src_location);
    if (!texture2d_is_full_rect(dst_texture, dst_sub_resource_idx % dst_texture->level_count, dst_rect))
        wined3d_texture_load_location(dst_texture, dst_sub_resource_idx, context, dst_location);
    else
        wined3d_texture_prepare_location(dst_texture, dst_sub_resource_idx, context, dst_location);


    if (src_location == WINED3D_LOCATION_DRAWABLE)
    {
        required_texture = src_texture;
        required_idx = src_sub_resource_idx;
    }
    else if (dst_location == WINED3D_LOCATION_DRAWABLE)
    {
        required_texture = dst_texture;
        required_idx = dst_sub_resource_idx;
    }
    else
    {
        required_texture = NULL;
        required_idx = 0;
    }

    restore_texture = context->current_rt.texture;
    restore_idx = context->current_rt.sub_resource_idx;
    if (restore_texture != required_texture || restore_idx != required_idx)
        context = context_acquire(device, required_texture, required_idx);
    else
        restore_texture = NULL;

    if (!context->valid)
    {
        context_release(context);
        WARN("Invalid context, skipping blit.\n");
        return;
    }

    gl_info = context->gl_info;

    if (src_location == WINED3D_LOCATION_DRAWABLE)
    {
        TRACE("Source texture %p is onscreen.\n", src_texture);
        buffer = wined3d_texture_get_gl_buffer(src_texture);
        s = *src_rect;
        wined3d_texture_translate_drawable_coords(src_texture, context->win_handle, &s);
        src_rect = &s;
    }
    else
    {
        TRACE("Source texture %p is offscreen.\n", src_texture);
        buffer = GL_COLOR_ATTACHMENT0;
    }

    context_apply_fbo_state_blit(context, GL_READ_FRAMEBUFFER,
            &src_texture->resource, src_sub_resource_idx, NULL, 0, src_location);
    gl_info->gl_ops.gl.p_glReadBuffer(buffer);
    checkGLcall("glReadBuffer()");
    context_check_fbo_status(context, GL_READ_FRAMEBUFFER);

    if (dst_location == WINED3D_LOCATION_DRAWABLE)
    {
        TRACE("Destination texture %p is onscreen.\n", dst_texture);
        buffer = wined3d_texture_get_gl_buffer(dst_texture);
        d = *dst_rect;
        wined3d_texture_translate_drawable_coords(dst_texture, context->win_handle, &d);
        dst_rect = &d;
    }
    else
    {
        TRACE("Destination texture %p is offscreen.\n", dst_texture);
        buffer = GL_COLOR_ATTACHMENT0;
    }

    context_apply_fbo_state_blit(context, GL_DRAW_FRAMEBUFFER,
            &dst_texture->resource, dst_sub_resource_idx, NULL, 0, dst_location);
    context_set_draw_buffer(context, buffer);
    context_check_fbo_status(context, GL_DRAW_FRAMEBUFFER);
    context_invalidate_state(context, STATE_FRAMEBUFFER);

    gl_info->gl_ops.gl.p_glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    for (i = 0; i < MAX_RENDER_TARGETS; ++i)
        context_invalidate_state(context, STATE_RENDER(WINED3D_RS_COLORWRITE(i)));

    gl_info->gl_ops.gl.p_glDisable(GL_SCISSOR_TEST);
    context_invalidate_state(context, STATE_RENDER(WINED3D_RS_SCISSORTESTENABLE));

    gl_info->fbo_ops.glBlitFramebuffer(src_rect->left, src_rect->top, src_rect->right, src_rect->bottom,
            dst_rect->left, dst_rect->top, dst_rect->right, dst_rect->bottom, GL_COLOR_BUFFER_BIT, gl_filter);
    checkGLcall("glBlitFramebuffer()");

    if (dst_location == WINED3D_LOCATION_DRAWABLE && dst_texture->swapchain->front_buffer == dst_texture)
        gl_info->gl_ops.gl.p_glFlush();

    if (restore_texture)
        context_restore(context, restore_texture, restore_idx);
}