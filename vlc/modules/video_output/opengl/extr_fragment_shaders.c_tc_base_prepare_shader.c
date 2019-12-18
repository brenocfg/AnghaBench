#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pl_var {scalar_t__ type; int dim_m; int dim_v; } ;
struct pl_shader_var {float* data; struct pl_var var; } ;
struct pl_shader_res {int num_variables; struct pl_shader_var* variables; } ;
struct TYPE_5__ {int FillColor; int* TexSize; int* pl_vars; int /*<<< orphan*/ * Texture; int /*<<< orphan*/  Coefficients; } ;
struct TYPE_7__ {unsigned int tex_count; scalar_t__ tex_target; TYPE_2__* vt; TYPE_1__ uloc; struct pl_shader_res* pl_sh_res; int /*<<< orphan*/  yuv_coefficients; scalar_t__ yuv_color; } ;
typedef  TYPE_3__ opengl_tex_converter_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* Uniform4f ) (int,float const,float const,float const,float const) ;int /*<<< orphan*/  (* Uniform3f ) (int,float const,float const,float const) ;int /*<<< orphan*/  (* Uniform2f ) (int,float const,float const) ;int /*<<< orphan*/  (* Uniform1f ) (int,float const) ;int /*<<< orphan*/  (* UniformMatrix2fv ) (int,int,int /*<<< orphan*/ ,float const*) ;int /*<<< orphan*/  (* UniformMatrix3fv ) (int,int,int /*<<< orphan*/ ,float const*) ;int /*<<< orphan*/  (* UniformMatrix4fv ) (int,int,int /*<<< orphan*/ ,float const*) ;int /*<<< orphan*/  (* Uniform1i ) (int /*<<< orphan*/ ,unsigned int) ;int /*<<< orphan*/  (* Uniform4fv ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;} ;
typedef  float GLsizei ;
typedef  int GLint ;

/* Variables and functions */
 int /*<<< orphan*/  GL_FALSE ; 
 scalar_t__ GL_TEXTURE_RECTANGLE ; 
 scalar_t__ PL_VAR_FLOAT ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub10 (int,float const,float const,float const) ; 
 int /*<<< orphan*/  stub11 (int,float const,float const,float const,float const) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  stub3 (int,float,float,float,float) ; 
 int /*<<< orphan*/  stub4 (int,float const,float const) ; 
 int /*<<< orphan*/  stub5 (int,int,int /*<<< orphan*/ ,float const*) ; 
 int /*<<< orphan*/  stub6 (int,int,int /*<<< orphan*/ ,float const*) ; 
 int /*<<< orphan*/  stub7 (int,int,int /*<<< orphan*/ ,float const*) ; 
 int /*<<< orphan*/  stub8 (int,float const) ; 
 int /*<<< orphan*/  stub9 (int,float const,float const) ; 

__attribute__((used)) static void
tc_base_prepare_shader(const opengl_tex_converter_t *tc,
                       const GLsizei *tex_width, const GLsizei *tex_height,
                       float alpha)
{
    (void) tex_width; (void) tex_height;

    if (tc->yuv_color)
        tc->vt->Uniform4fv(tc->uloc.Coefficients, 4, tc->yuv_coefficients);

    for (unsigned i = 0; i < tc->tex_count; ++i)
        tc->vt->Uniform1i(tc->uloc.Texture[i], i);

    tc->vt->Uniform4f(tc->uloc.FillColor, 1.0f, 1.0f, 1.0f, alpha);

    if (tc->tex_target == GL_TEXTURE_RECTANGLE)
    {
        for (unsigned i = 0; i < tc->tex_count; ++i)
            tc->vt->Uniform2f(tc->uloc.TexSize[i], tex_width[i],
                               tex_height[i]);
    }

#ifdef HAVE_LIBPLACEBO
    const struct pl_shader_res *res = tc->pl_sh_res;
    for (int i = 0; res && i < res->num_variables; i++) {
        GLint loc = tc->uloc.pl_vars[i];
        if (loc == -1) // uniform optimized out
            continue;

        struct pl_shader_var sv = res->variables[i];
        struct pl_var var = sv.var;
        // libplacebo doesn't need anything else anyway
        if (var.type != PL_VAR_FLOAT)
            continue;
        if (var.dim_m > 1 && var.dim_m != var.dim_v)
            continue;

        const float *f = sv.data;
        switch (var.dim_m) {
        case 4: tc->vt->UniformMatrix4fv(loc, 1, GL_FALSE, f); break;
        case 3: tc->vt->UniformMatrix3fv(loc, 1, GL_FALSE, f); break;
        case 2: tc->vt->UniformMatrix2fv(loc, 1, GL_FALSE, f); break;

        case 1:
            switch (var.dim_v) {
            case 1: tc->vt->Uniform1f(loc, f[0]); break;
            case 2: tc->vt->Uniform2f(loc, f[0], f[1]); break;
            case 3: tc->vt->Uniform3f(loc, f[0], f[1], f[2]); break;
            case 4: tc->vt->Uniform4f(loc, f[0], f[1], f[2], f[3]); break;
            }
            break;
        }
    }
#endif
}