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
struct TYPE_8__ {char* name; } ;
struct pl_shader_var {TYPE_3__ var; } ;
struct pl_shader_res {int num_variables; struct pl_shader_var* variables; } ;
struct TYPE_6__ {int Coefficients; int* Texture; int* TexSize; int FillColor; int* pl_vars; } ;
struct TYPE_9__ {unsigned int tex_count; scalar_t__ tex_target; TYPE_2__* vt; TYPE_1__ uloc; struct pl_shader_res* pl_sh_res; scalar_t__ yuv_color; } ;
typedef  TYPE_4__ opengl_tex_converter_t ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_7__ {int (* GetUniformLocation ) (int /*<<< orphan*/ ,char*) ;} ;
typedef  int /*<<< orphan*/  GLuint ;

/* Variables and functions */
 scalar_t__ GL_TEXTURE_RECTANGLE ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 
 int stub1 (int /*<<< orphan*/ ,char*) ; 
 int stub2 (int /*<<< orphan*/ ,char*) ; 
 int stub3 (int /*<<< orphan*/ ,char*) ; 
 int stub4 (int /*<<< orphan*/ ,char*) ; 
 int stub5 (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
tc_base_fetch_locations(opengl_tex_converter_t *tc, GLuint program)
{
    if (tc->yuv_color)
    {
        tc->uloc.Coefficients = tc->vt->GetUniformLocation(program,
                                                            "Coefficients");
        if (tc->uloc.Coefficients == -1)
            return VLC_EGENERIC;
    }

    for (unsigned int i = 0; i < tc->tex_count; ++i)
    {
        char name[sizeof("TextureX")];
        snprintf(name, sizeof(name), "Texture%1u", i);
        tc->uloc.Texture[i] = tc->vt->GetUniformLocation(program, name);
        if (tc->uloc.Texture[i] == -1)
            return VLC_EGENERIC;
        if (tc->tex_target == GL_TEXTURE_RECTANGLE)
        {
            snprintf(name, sizeof(name), "TexSize%1u", i);
            tc->uloc.TexSize[i] = tc->vt->GetUniformLocation(program, name);
            if (tc->uloc.TexSize[i] == -1)
                return VLC_EGENERIC;
        }
    }

    tc->uloc.FillColor = tc->vt->GetUniformLocation(program, "FillColor");
    if (tc->uloc.FillColor == -1)
        return VLC_EGENERIC;

#ifdef HAVE_LIBPLACEBO
    const struct pl_shader_res *res = tc->pl_sh_res;
    for (int i = 0; res && i < res->num_variables; i++) {
        struct pl_shader_var sv = res->variables[i];
        tc->uloc.pl_vars[i] = tc->vt->GetUniformLocation(program, sv.var.name);
    }
#endif

    return VLC_SUCCESS;
}