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
struct wined3d_texture {float* pow2_matrix; } ;
struct wined3d_state {struct wined3d_texture** textures; } ;
struct wined3d_gl_info {int dummy; } ;
struct glsl_ps_program {TYPE_1__* np2_fixup_info; int /*<<< orphan*/  np2_fixup_location; } ;
typedef  int UINT ;
struct TYPE_2__ {int active; unsigned char* idx; int /*<<< orphan*/  num_consts; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 int MAX_FRAGMENT_SAMPLERS ; 
 int /*<<< orphan*/  glUniform4fv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float*) ; 

__attribute__((used)) static void shader_glsl_load_np2fixup_constants(const struct glsl_ps_program *ps,
        const struct wined3d_gl_info *gl_info, const struct wined3d_state *state)
{
    struct
    {
        float sx, sy;
    }
    np2fixup_constants[MAX_FRAGMENT_SAMPLERS];
    UINT fixup = ps->np2_fixup_info->active;
    UINT i;

    for (i = 0; fixup; fixup >>= 1, ++i)
    {
        const struct wined3d_texture *tex = state->textures[i];
        unsigned char idx = ps->np2_fixup_info->idx[i];

        if (!tex)
        {
            ERR("Nonexistent texture is flagged for NP2 texcoord fixup.\n");
            continue;
        }

        np2fixup_constants[idx].sx = tex->pow2_matrix[0];
        np2fixup_constants[idx].sy = tex->pow2_matrix[5];
    }

    GL_EXTCALL(glUniform4fv(ps->np2_fixup_location, ps->np2_fixup_info->num_consts, &np2fixup_constants[0].sx));
}