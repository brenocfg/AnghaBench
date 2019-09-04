#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  (* p_glDisable ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glLoadIdentity ) () ;int /*<<< orphan*/  (* p_glMatrixMode ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glTexEnvf ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float) ;int /*<<< orphan*/  (* p_glTexEnvi ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_8__ {TYPE_2__ gl; } ;
struct TYPE_6__ {int textures; } ;
struct wined3d_gl_info {TYPE_3__ gl_ops; scalar_t__* supported; TYPE_1__ limits; } ;
struct wined3d_device {int dummy; } ;
struct wined3d_context {scalar_t__ blit_w; scalar_t__ blit_h; unsigned int* rev_tex_unit_map; scalar_t__ last_was_ffp_blit; struct wined3d_gl_info* gl_info; } ;
struct TYPE_9__ {scalar_t__ cx; scalar_t__ cy; } ;
typedef  TYPE_4__ SIZE ;

/* Variables and functions */
 size_t ARB_TEXTURE_CUBE_MAP ; 
 size_t ARB_TEXTURE_RECTANGLE ; 
 int /*<<< orphan*/  ERR (char*) ; 
 size_t EXT_SECONDARY_COLOR ; 
 size_t EXT_TEXTURE_LOD_BIAS ; 
 int /*<<< orphan*/  GL_COLOR_SUM_EXT ; 
 int /*<<< orphan*/  GL_FOG ; 
 int /*<<< orphan*/  GL_LIGHTING ; 
 int /*<<< orphan*/  GL_MODELVIEW ; 
 int /*<<< orphan*/  GL_REPLACE ; 
 int /*<<< orphan*/  GL_TEXTURE ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  GL_TEXTURE_3D ; 
 int /*<<< orphan*/  GL_TEXTURE_CUBE_MAP_ARB ; 
 int /*<<< orphan*/  GL_TEXTURE_ENV ; 
 int /*<<< orphan*/  GL_TEXTURE_ENV_MODE ; 
 int /*<<< orphan*/  GL_TEXTURE_FILTER_CONTROL_EXT ; 
 int /*<<< orphan*/  GL_TEXTURE_LOD_BIAS_EXT ; 
 int /*<<< orphan*/  GL_TEXTURE_RECTANGLE_ARB ; 
 unsigned int MAX_TEXTURES ; 
 int /*<<< orphan*/  STATE_RENDER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATE_SAMPLER (unsigned int) ; 
 int /*<<< orphan*/  STATE_TEXTURESTAGE (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATE_TRANSFORM (int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 size_t WINED3D_GL_LEGACY_CONTEXT ; 
 int /*<<< orphan*/  WINED3D_RS_FOGENABLE ; 
 int /*<<< orphan*/  WINED3D_RS_LIGHTING ; 
 int /*<<< orphan*/  WINED3D_RS_SPECULARENABLE ; 
 int /*<<< orphan*/  WINED3D_TSS_COLOR_OP ; 
 int /*<<< orphan*/  WINED3D_TS_PROJECTION ; 
 int /*<<< orphan*/  WINED3D_TS_WORLD_MATRIX (int /*<<< orphan*/ ) ; 
 unsigned int WINED3D_UNMAPPED_STAGE ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 int /*<<< orphan*/  context_active_texture (struct wined3d_context*,struct wined3d_gl_info const*,unsigned int) ; 
 int /*<<< orphan*/  context_apply_blit_projection (struct wined3d_context*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  context_apply_blit_state (struct wined3d_context*,struct wined3d_device const*) ; 
 int /*<<< orphan*/  context_get_rt_size (struct wined3d_context*,TYPE_4__*) ; 
 int /*<<< orphan*/  context_invalidate_state (struct wined3d_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDisableWINE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub10 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub11 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  stub12 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub13 () ; 
 int /*<<< orphan*/  stub14 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub15 () ; 
 int /*<<< orphan*/  stub16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub17 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub9 (int /*<<< orphan*/ ) ; 

void context_apply_ffp_blit_state(struct wined3d_context *context, const struct wined3d_device *device)
{
    const struct wined3d_gl_info *gl_info = context->gl_info;
    unsigned int i, sampler;

    if (!gl_info->supported[WINED3D_GL_LEGACY_CONTEXT])
        ERR("Applying fixed-function state without legacy context support.\n");

    if (context->last_was_ffp_blit)
    {
        SIZE rt_size;

        context_get_rt_size(context, &rt_size);
        if (context->blit_w != rt_size.cx || context->blit_h != rt_size.cy)
            context_apply_blit_projection(context, rt_size.cx, rt_size.cy);
        context_apply_blit_state(context, device);

        checkGLcall("ffp blit state application");
        return;
    }
    context->last_was_ffp_blit = TRUE;

    context_apply_blit_state(context, device);

    /* Disable all textures. The caller can then bind a texture it wants to blit
     * from. */
    for (i = gl_info->limits.textures - 1; i > 0 ; --i)
    {
        context_active_texture(context, gl_info, i);

        if (gl_info->supported[ARB_TEXTURE_CUBE_MAP])
            gl_info->gl_ops.gl.p_glDisable(GL_TEXTURE_CUBE_MAP_ARB);
        gl_info->gl_ops.gl.p_glDisable(GL_TEXTURE_3D);
        if (gl_info->supported[ARB_TEXTURE_RECTANGLE])
            gl_info->gl_ops.gl.p_glDisable(GL_TEXTURE_RECTANGLE_ARB);
        gl_info->gl_ops.gl.p_glDisable(GL_TEXTURE_2D);

        gl_info->gl_ops.gl.p_glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

        sampler = context->rev_tex_unit_map[i];
        if (sampler != WINED3D_UNMAPPED_STAGE)
        {
            if (sampler < MAX_TEXTURES)
                context_invalidate_state(context, STATE_TEXTURESTAGE(sampler, WINED3D_TSS_COLOR_OP));
            context_invalidate_state(context, STATE_SAMPLER(sampler));
        }
    }

    context_active_texture(context, gl_info, 0);

    if (gl_info->supported[ARB_TEXTURE_CUBE_MAP])
        gl_info->gl_ops.gl.p_glDisable(GL_TEXTURE_CUBE_MAP_ARB);
    gl_info->gl_ops.gl.p_glDisable(GL_TEXTURE_3D);
    if (gl_info->supported[ARB_TEXTURE_RECTANGLE])
        gl_info->gl_ops.gl.p_glDisable(GL_TEXTURE_RECTANGLE_ARB);
    gl_info->gl_ops.gl.p_glDisable(GL_TEXTURE_2D);

    gl_info->gl_ops.gl.p_glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    if (gl_info->supported[EXT_TEXTURE_LOD_BIAS])
        gl_info->gl_ops.gl.p_glTexEnvf(GL_TEXTURE_FILTER_CONTROL_EXT, GL_TEXTURE_LOD_BIAS_EXT, 0.0f);

    gl_info->gl_ops.gl.p_glMatrixMode(GL_TEXTURE);
    gl_info->gl_ops.gl.p_glLoadIdentity();

    /* Setup transforms. */
    gl_info->gl_ops.gl.p_glMatrixMode(GL_MODELVIEW);
    gl_info->gl_ops.gl.p_glLoadIdentity();
    context_invalidate_state(context, STATE_TRANSFORM(WINED3D_TS_WORLD_MATRIX(0)));
    context_apply_blit_projection(context, context->blit_w, context->blit_h);
    context_invalidate_state(context, STATE_TRANSFORM(WINED3D_TS_PROJECTION));

    /* Other misc states. */
    gl_info->gl_ops.gl.p_glDisable(GL_LIGHTING);
    context_invalidate_state(context, STATE_RENDER(WINED3D_RS_LIGHTING));
    glDisableWINE(GL_FOG);
    context_invalidate_state(context, STATE_RENDER(WINED3D_RS_FOGENABLE));

    if (gl_info->supported[EXT_SECONDARY_COLOR])
    {
        gl_info->gl_ops.gl.p_glDisable(GL_COLOR_SUM_EXT);
        context_invalidate_state(context, STATE_RENDER(WINED3D_RS_SPECULARENABLE));
    }
    checkGLcall("ffp blit state application");
}