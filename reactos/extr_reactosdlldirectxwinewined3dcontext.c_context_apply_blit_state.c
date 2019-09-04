#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_3__* format; int /*<<< orphan*/  draw_binding; } ;
struct wined3d_texture {TYPE_10__ resource; } ;
struct TYPE_18__ {int /*<<< orphan*/  (* p_glViewport ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ;int /*<<< orphan*/  (* p_glColorMask ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glDisable ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_19__ {TYPE_5__ gl; } ;
struct wined3d_gl_info {TYPE_6__ gl_ops; scalar_t__* supported; } ;
struct wined3d_device {int /*<<< orphan*/  shader_priv; TYPE_1__* shader_backend; } ;
struct TYPE_15__ {int /*<<< orphan*/  sub_resource_idx; struct wined3d_texture* texture; } ;
struct wined3d_context {int draw_buffers_mask; scalar_t__ blit_w; scalar_t__ blit_h; unsigned int* rev_tex_unit_map; void* viewport_count; void* last_was_rhw; void* last_was_blit; TYPE_4__* current_fbo; TYPE_2__ current_rt; scalar_t__ render_offscreen; struct wined3d_gl_info* gl_info; } ;
struct TYPE_21__ {scalar_t__ offscreen_rendering_mode; } ;
struct TYPE_20__ {scalar_t__ cx; scalar_t__ cy; } ;
struct TYPE_17__ {int rt_mask; } ;
struct TYPE_16__ {scalar_t__ id; } ;
struct TYPE_14__ {int /*<<< orphan*/  (* shader_disable ) (int /*<<< orphan*/ ,struct wined3d_context*) ;} ;
typedef  TYPE_7__ SIZE ;
typedef  int DWORD ;

/* Variables and functions */
 size_t ARB_CLIP_CONTROL ; 
 size_t ARB_FRAMEBUFFER_SRGB ; 
 size_t ARB_POINT_SPRITE ; 
 size_t ARB_SAMPLER_OBJECTS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GL_ALPHA_TEST ; 
 int /*<<< orphan*/  GL_BLEND ; 
 int /*<<< orphan*/  GL_CULL_FACE ; 
 int /*<<< orphan*/  GL_DEPTH_TEST ; 
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_FRAMEBUFFER ; 
 int /*<<< orphan*/  GL_FRAMEBUFFER_SRGB ; 
 int /*<<< orphan*/  GL_LOWER_LEFT ; 
 int /*<<< orphan*/  GL_NEGATIVE_ONE_TO_ONE ; 
 int /*<<< orphan*/  GL_POINT_SPRITE_ARB ; 
 int /*<<< orphan*/  GL_SCISSOR_TEST ; 
 int /*<<< orphan*/  GL_STENCIL_TEST ; 
 int /*<<< orphan*/  GL_TRUE ; 
 unsigned int MAX_RENDER_TARGETS ; 
 unsigned int MAX_TEXTURES ; 
 scalar_t__ ORM_FBO ; 
 int /*<<< orphan*/  STATE_FRAMEBUFFER ; 
 int /*<<< orphan*/  STATE_RENDER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATE_SAMPLER (unsigned int) ; 
 int /*<<< orphan*/  STATE_TEXTURESTAGE (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATE_TRANSFORM (scalar_t__) ; 
 int /*<<< orphan*/  STATE_VDECL ; 
 int /*<<< orphan*/  STATE_VIEWPORT ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 void* TRUE ; 
 scalar_t__ WINED3DFMT_NULL ; 
 size_t WINED3D_GL_LEGACY_CONTEXT ; 
 void* WINED3D_MAX_VIEWPORTS ; 
 int /*<<< orphan*/  WINED3D_RS_ALPHABLENDENABLE ; 
 int /*<<< orphan*/  WINED3D_RS_ALPHATESTENABLE ; 
 int /*<<< orphan*/  WINED3D_RS_CLIPPING ; 
 int /*<<< orphan*/  WINED3D_RS_COLORWRITE (unsigned int) ; 
 int /*<<< orphan*/  WINED3D_RS_CULLMODE ; 
 int /*<<< orphan*/  WINED3D_RS_POINTSPRITEENABLE ; 
 int /*<<< orphan*/  WINED3D_RS_SCISSORTESTENABLE ; 
 int /*<<< orphan*/  WINED3D_RS_SRGBWRITEENABLE ; 
 int /*<<< orphan*/  WINED3D_RS_STENCILENABLE ; 
 int /*<<< orphan*/  WINED3D_RS_ZENABLE ; 
 int /*<<< orphan*/  WINED3D_TSS_COLOR_OP ; 
 scalar_t__ WINED3D_TS_TEXTURE0 ; 
 unsigned int WINED3D_UNMAPPED_STAGE ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 int /*<<< orphan*/  context_active_texture (struct wined3d_context*,struct wined3d_gl_info const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  context_apply_draw_buffers (struct wined3d_context*,int) ; 
 int /*<<< orphan*/  context_apply_fbo_state_blit (struct wined3d_context*,int /*<<< orphan*/ ,TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  context_bind_fbo (struct wined3d_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  context_check_fbo_status (struct wined3d_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  context_enable_clip_distances (struct wined3d_context*,int /*<<< orphan*/ ) ; 
 int context_generate_rt_mask_from_resource (TYPE_10__*) ; 
 int context_generate_rt_mask_no_fbo (struct wined3d_context*,TYPE_10__*) ; 
 int /*<<< orphan*/  context_get_rt_size (struct wined3d_context*,TYPE_7__*) ; 
 int /*<<< orphan*/  context_invalidate_state (struct wined3d_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBindSampler (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClipControl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub10 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub11 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub12 (int /*<<< orphan*/ ,struct wined3d_context*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub9 (int /*<<< orphan*/ ) ; 
 TYPE_8__ wined3d_settings ; 
 int /*<<< orphan*/  wined3d_texture_load (struct wined3d_texture*,struct wined3d_context*,int /*<<< orphan*/ ) ; 

void context_apply_blit_state(struct wined3d_context *context, const struct wined3d_device *device)
{
    const struct wined3d_gl_info *gl_info = context->gl_info;
    struct wined3d_texture *rt = context->current_rt.texture;
    DWORD rt_mask, *cur_mask;
    unsigned int i, sampler;
    SIZE rt_size;

    TRACE("Setting up context %p for blitting.\n", context);

    if (wined3d_settings.offscreen_rendering_mode == ORM_FBO)
    {
        if (context->render_offscreen)
        {
            wined3d_texture_load(rt, context, FALSE);

            context_apply_fbo_state_blit(context, GL_FRAMEBUFFER, &rt->resource,
                    context->current_rt.sub_resource_idx, NULL, 0, rt->resource.draw_binding);
            if (rt->resource.format->id != WINED3DFMT_NULL)
                rt_mask = 1;
            else
                rt_mask = 0;
        }
        else
        {
            context->current_fbo = NULL;
            context_bind_fbo(context, GL_FRAMEBUFFER, 0);
            rt_mask = context_generate_rt_mask_from_resource(&rt->resource);
        }
    }
    else
    {
        rt_mask = context_generate_rt_mask_no_fbo(context, &rt->resource);
    }

    cur_mask = context->current_fbo ? &context->current_fbo->rt_mask : &context->draw_buffers_mask;

    if (rt_mask != *cur_mask)
    {
        context_apply_draw_buffers(context, rt_mask);
        *cur_mask = rt_mask;
    }

    if (wined3d_settings.offscreen_rendering_mode == ORM_FBO)
    {
        context_check_fbo_status(context, GL_FRAMEBUFFER);
    }
    context_invalidate_state(context, STATE_FRAMEBUFFER);

    context_get_rt_size(context, &rt_size);

    if (context->last_was_blit)
    {
        if (context->blit_w != rt_size.cx || context->blit_h != rt_size.cy)
        {
            gl_info->gl_ops.gl.p_glViewport(0, 0, rt_size.cx, rt_size.cy);
            context->viewport_count = WINED3D_MAX_VIEWPORTS;
            context->blit_w = rt_size.cx;
            context->blit_h = rt_size.cy;
            /* No need to dirtify here, the states are still dirtified because
             * they weren't applied since the last context_apply_blit_state()
             * call. */
        }
        checkGLcall("blit state application");
        TRACE("Context is already set up for blitting, nothing to do.\n");
        return;
    }
    context->last_was_blit = TRUE;

    if (gl_info->supported[ARB_SAMPLER_OBJECTS])
        GL_EXTCALL(glBindSampler(0, 0));
    context_active_texture(context, gl_info, 0);

    sampler = context->rev_tex_unit_map[0];
    if (sampler != WINED3D_UNMAPPED_STAGE)
    {
        if (sampler < MAX_TEXTURES)
        {
            context_invalidate_state(context, STATE_TRANSFORM(WINED3D_TS_TEXTURE0 + sampler));
            context_invalidate_state(context, STATE_TEXTURESTAGE(sampler, WINED3D_TSS_COLOR_OP));
        }
        context_invalidate_state(context, STATE_SAMPLER(sampler));
    }

    if (gl_info->supported[WINED3D_GL_LEGACY_CONTEXT])
    {
        gl_info->gl_ops.gl.p_glDisable(GL_ALPHA_TEST);
        context_invalidate_state(context, STATE_RENDER(WINED3D_RS_ALPHATESTENABLE));
    }
    gl_info->gl_ops.gl.p_glDisable(GL_DEPTH_TEST);
    context_invalidate_state(context, STATE_RENDER(WINED3D_RS_ZENABLE));
    gl_info->gl_ops.gl.p_glDisable(GL_BLEND);
    context_invalidate_state(context, STATE_RENDER(WINED3D_RS_ALPHABLENDENABLE));
    gl_info->gl_ops.gl.p_glDisable(GL_CULL_FACE);
    context_invalidate_state(context, STATE_RENDER(WINED3D_RS_CULLMODE));
    gl_info->gl_ops.gl.p_glDisable(GL_STENCIL_TEST);
    context_invalidate_state(context, STATE_RENDER(WINED3D_RS_STENCILENABLE));
    gl_info->gl_ops.gl.p_glDisable(GL_SCISSOR_TEST);
    context_invalidate_state(context, STATE_RENDER(WINED3D_RS_SCISSORTESTENABLE));
    if (gl_info->supported[ARB_POINT_SPRITE])
    {
        gl_info->gl_ops.gl.p_glDisable(GL_POINT_SPRITE_ARB);
        context_invalidate_state(context, STATE_RENDER(WINED3D_RS_POINTSPRITEENABLE));
    }
    if (gl_info->supported[ARB_FRAMEBUFFER_SRGB])
    {
        gl_info->gl_ops.gl.p_glDisable(GL_FRAMEBUFFER_SRGB);
        context_invalidate_state(context, STATE_RENDER(WINED3D_RS_SRGBWRITEENABLE));
    }
    gl_info->gl_ops.gl.p_glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    for (i = 0; i < MAX_RENDER_TARGETS; ++i)
        context_invalidate_state(context, STATE_RENDER(WINED3D_RS_COLORWRITE(i)));

    context->last_was_rhw = TRUE;
    context_invalidate_state(context, STATE_VDECL); /* because of last_was_rhw = TRUE */

    context_enable_clip_distances(context, 0);
    context_invalidate_state(context, STATE_RENDER(WINED3D_RS_CLIPPING));

    /* FIXME: Make draw_textured_quad() able to work with a upper left origin. */
    if (gl_info->supported[ARB_CLIP_CONTROL])
        GL_EXTCALL(glClipControl(GL_LOWER_LEFT, GL_NEGATIVE_ONE_TO_ONE));
    gl_info->gl_ops.gl.p_glViewport(0, 0, rt_size.cx, rt_size.cy);
    context->viewport_count = WINED3D_MAX_VIEWPORTS;
    context_invalidate_state(context, STATE_VIEWPORT);

    device->shader_backend->shader_disable(device->shader_priv, context);

    context->blit_w = rt_size.cx;
    context->blit_h = rt_size.cy;

    checkGLcall("blit state application");
}