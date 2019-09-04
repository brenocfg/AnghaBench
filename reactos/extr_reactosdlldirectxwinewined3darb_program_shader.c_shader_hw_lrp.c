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
struct wined3d_shader_instruction {int /*<<< orphan*/ * src; int /*<<< orphan*/ * dst; TYPE_3__* ctx; } ;
struct TYPE_6__ {TYPE_2__* reg_maps; struct wined3d_string_buffer* buffer; } ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
struct TYPE_5__ {TYPE_1__ shader_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,char*,char*,...) ; 
 int /*<<< orphan*/  shader_arb_get_dst_param (struct wined3d_shader_instruction const*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  shader_arb_get_modifier (struct wined3d_shader_instruction const*) ; 
 int /*<<< orphan*/  shader_arb_get_src_param (struct wined3d_shader_instruction const*,int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  shader_hw_map2gl (struct wined3d_shader_instruction const*) ; 
 scalar_t__ shader_is_pshader_version (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void shader_hw_lrp(const struct wined3d_shader_instruction *ins)
{
    struct wined3d_string_buffer *buffer = ins->ctx->buffer;
    char dst_name[50];
    char src_name[3][50];

    /* ARB_fragment_program has a convenient LRP instruction */
    if(shader_is_pshader_version(ins->ctx->reg_maps->shader_version.type)) {
        shader_hw_map2gl(ins);
        return;
    }

    shader_arb_get_dst_param(ins, &ins->dst[0], dst_name);
    shader_arb_get_src_param(ins, &ins->src[0], 0, src_name[0]);
    shader_arb_get_src_param(ins, &ins->src[1], 1, src_name[1]);
    shader_arb_get_src_param(ins, &ins->src[2], 2, src_name[2]);

    shader_addline(buffer, "SUB TA, %s, %s;\n", src_name[1], src_name[2]);
    shader_addline(buffer, "MAD%s %s, %s, TA, %s;\n", shader_arb_get_modifier(ins),
                   dst_name, src_name[0], src_name[2]);
}