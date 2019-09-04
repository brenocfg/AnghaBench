#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct wined3d_string_buffer {int dummy; } ;
struct wined3d_shader_tex_mx {int* texcoord_w; scalar_t__ current_row; } ;
struct wined3d_shader_instruction {int /*<<< orphan*/ * src; TYPE_4__* dst; TYPE_1__* ctx; } ;
struct glsl_src_param {int /*<<< orphan*/  param_str; } ;
struct TYPE_7__ {TYPE_2__* idx; } ;
struct TYPE_8__ {TYPE_3__ reg; } ;
struct TYPE_6__ {int offset; } ;
struct TYPE_5__ {struct wined3d_shader_tex_mx* tex_mx; struct wined3d_string_buffer* buffer; } ;
typedef  int DWORD ;

/* Variables and functions */
 int WINED3DSP_WRITEMASK_0 ; 
 int WINED3DSP_WRITEMASK_1 ; 
 int WINED3DSP_WRITEMASK_2 ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_glsl_add_src_param (struct wined3d_shader_instruction const*,int /*<<< orphan*/ *,int,struct glsl_src_param*) ; 

__attribute__((used)) static void shader_glsl_texm3x3pad(const struct wined3d_shader_instruction *ins)
{
    DWORD src_mask = WINED3DSP_WRITEMASK_0 | WINED3DSP_WRITEMASK_1 | WINED3DSP_WRITEMASK_2;
    struct wined3d_string_buffer *buffer = ins->ctx->buffer;
    struct wined3d_shader_tex_mx *tex_mx = ins->ctx->tex_mx;
    DWORD reg = ins->dst[0].reg.idx[0].offset;
    struct glsl_src_param src0_param;

    shader_glsl_add_src_param(ins, &ins->src[0], src_mask, &src0_param);
    shader_addline(buffer, "tmp0.%c = dot(T%u.xyz, %s);\n", 'x' + tex_mx->current_row, reg, src0_param.param_str);
    tex_mx->texcoord_w[tex_mx->current_row++] = reg;
}