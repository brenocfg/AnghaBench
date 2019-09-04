#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct wined3d_string_buffer {int dummy; } ;
struct wined3d_shader_instruction {int /*<<< orphan*/ * src; TYPE_3__* ctx; struct wined3d_shader_dst_param* dst; } ;
struct TYPE_5__ {TYPE_1__* idx; } ;
struct wined3d_shader_dst_param {TYPE_2__ reg; } ;
struct TYPE_6__ {struct wined3d_string_buffer* buffer; } ;
struct TYPE_4__ {int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  shader_arb_get_dst_param (struct wined3d_shader_instruction const*,struct wined3d_shader_dst_param const*,char*) ; 
 int /*<<< orphan*/  shader_arb_get_src_param (struct wined3d_shader_instruction const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void pshader_hw_texdp3(const struct wined3d_shader_instruction *ins)
{
    const struct wined3d_shader_dst_param *dst = &ins->dst[0];
    char src0[50];
    char dst_str[50];
    struct wined3d_string_buffer *buffer = ins->ctx->buffer;

    /* Handle output register */
    shader_arb_get_dst_param(ins, dst, dst_str);
    shader_arb_get_src_param(ins, &ins->src[0], 0, src0);
    shader_addline(buffer, "DP3 %s, fragment.texcoord[%u], %s;\n", dst_str, dst->reg.idx[0].offset, src0);
}