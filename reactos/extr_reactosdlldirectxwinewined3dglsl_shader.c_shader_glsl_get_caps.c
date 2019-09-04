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
struct TYPE_3__ {unsigned int glsl_vs_float_constants; unsigned int glsl_ps_float_constants; int /*<<< orphan*/  glsl_varyings; } ;
struct wined3d_gl_info {TYPE_1__ limits; scalar_t__* supported; } ;
struct shader_caps {float ps_1x_max_value; int wined3d_caps; int /*<<< orphan*/  varying_count; void* ps_uniform_count; void* vs_uniform_count; void* ps_version; void* vs_version; void* cs_version; void* gs_version; void* ds_version; void* hs_version; } ;
struct TYPE_4__ {int /*<<< orphan*/  max_sm_cs; int /*<<< orphan*/  max_sm_ps; int /*<<< orphan*/  max_sm_gs; int /*<<< orphan*/  max_sm_ds; int /*<<< orphan*/  max_sm_hs; int /*<<< orphan*/  max_sm_vs; } ;

/* Variables and functions */
 size_t ARB_FRAGMENT_SHADER ; 
 size_t ARB_VERTEX_SHADER ; 
 float FLT_MAX ; 
 int /*<<< orphan*/  TRACE (char*,unsigned int) ; 
 int /*<<< orphan*/  WINED3D_MAX_PS_CONSTS_F ; 
 int /*<<< orphan*/  WINED3D_MAX_VS_CONSTS_F ; 
 int WINED3D_SHADER_CAP_SRGB_WRITE ; 
 int WINED3D_SHADER_CAP_VS_CLIPPING ; 
 void* min (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int shader_glsl_get_shader_model (struct wined3d_gl_info const*) ; 
 TYPE_2__ wined3d_settings ; 

__attribute__((used)) static void shader_glsl_get_caps(const struct wined3d_gl_info *gl_info, struct shader_caps *caps)
{
    unsigned int shader_model = shader_glsl_get_shader_model(gl_info);

    TRACE("Shader model %u.\n", shader_model);

    caps->vs_version = min(wined3d_settings.max_sm_vs, shader_model);
    caps->hs_version = min(wined3d_settings.max_sm_hs, shader_model);
    caps->ds_version = min(wined3d_settings.max_sm_ds, shader_model);
    caps->gs_version = min(wined3d_settings.max_sm_gs, shader_model);
    caps->ps_version = min(wined3d_settings.max_sm_ps, shader_model);
    caps->cs_version = min(wined3d_settings.max_sm_cs, shader_model);

    caps->vs_version = gl_info->supported[ARB_VERTEX_SHADER] ? caps->vs_version : 0;
    caps->ps_version = gl_info->supported[ARB_FRAGMENT_SHADER] ? caps->ps_version : 0;

    caps->vs_uniform_count = min(WINED3D_MAX_VS_CONSTS_F, gl_info->limits.glsl_vs_float_constants);
    caps->ps_uniform_count = min(WINED3D_MAX_PS_CONSTS_F, gl_info->limits.glsl_ps_float_constants);
    caps->varying_count = gl_info->limits.glsl_varyings;

    /* FIXME: The following line is card dependent. -8.0 to 8.0 is the
     * Direct3D minimum requirement.
     *
     * Both GL_ARB_fragment_program and GLSL require a "maximum representable magnitude"
     * of colors to be 2^10, and 2^32 for other floats. Should we use 1024 here?
     *
     * The problem is that the refrast clamps temporary results in the shader to
     * [-MaxValue;+MaxValue]. If the card's max value is bigger than the one we advertize here,
     * then applications may miss the clamping behavior. On the other hand, if it is smaller,
     * the shader will generate incorrect results too. Unfortunately, GL deliberately doesn't
     * offer a way to query this.
     */
    if (shader_model >= 4)
        caps->ps_1x_max_value = FLT_MAX;
    else
        caps->ps_1x_max_value = 1024.0f;

    /* Ideally we'd only set caps like sRGB writes here if supported by both
     * the shader backend and the fragment pipe, but we can get called before
     * shader_glsl_alloc(). */
    caps->wined3d_caps = WINED3D_SHADER_CAP_VS_CLIPPING
            | WINED3D_SHADER_CAP_SRGB_WRITE;
}