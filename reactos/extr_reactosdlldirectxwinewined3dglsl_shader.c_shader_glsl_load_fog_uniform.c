#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wined3d_state {int /*<<< orphan*/ * render_states; } ;
struct wined3d_gl_info {int dummy; } ;
struct wined3d_context {struct wined3d_gl_info* gl_info; } ;
struct wined3d_color {int /*<<< orphan*/  r; } ;
struct TYPE_2__ {int /*<<< orphan*/  fog_scale_location; int /*<<< orphan*/  fog_end_location; int /*<<< orphan*/  fog_density_location; int /*<<< orphan*/  fog_color_location; } ;
struct glsl_shader_prog_link {TYPE_1__ ps; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 size_t WINED3D_RS_FOGCOLOR ; 
 size_t WINED3D_RS_FOGDENSITY ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 int /*<<< orphan*/  get_fog_start_end (struct wined3d_context const*,struct wined3d_state const*,float*,float*) ; 
 int /*<<< orphan*/  glUniform1f (int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  glUniform4fv (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wined3d_color_from_d3dcolor (struct wined3d_color*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void shader_glsl_load_fog_uniform(const struct wined3d_context *context,
        const struct wined3d_state *state, struct glsl_shader_prog_link *prog)
{
    const struct wined3d_gl_info *gl_info = context->gl_info;
    struct wined3d_color color;
    float start, end, scale;
    union
    {
        DWORD d;
        float f;
    } tmpvalue;

    wined3d_color_from_d3dcolor(&color, state->render_states[WINED3D_RS_FOGCOLOR]);
    GL_EXTCALL(glUniform4fv(prog->ps.fog_color_location, 1, &color.r));
    tmpvalue.d = state->render_states[WINED3D_RS_FOGDENSITY];
    GL_EXTCALL(glUniform1f(prog->ps.fog_density_location, tmpvalue.f));
    get_fog_start_end(context, state, &start, &end);
    scale = 1.0f / (end - start);
    GL_EXTCALL(glUniform1f(prog->ps.fog_end_location, end));
    GL_EXTCALL(glUniform1f(prog->ps.fog_scale_location, scale));
    checkGLcall("fog emulation uniforms");
}