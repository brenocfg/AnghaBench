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
struct wined3d_shader_instruction {TYPE_3__* ctx; struct wined3d_shader_dst_param* dst; } ;
struct wined3d_shader_dst_param {int dummy; } ;
struct TYPE_6__ {TYPE_2__* reg_maps; struct wined3d_string_buffer* buffer; } ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
struct TYPE_5__ {TYPE_1__ shader_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARB_ONE ; 
 int /*<<< orphan*/  ARB_ZERO ; 
 char* arb_get_helper_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,char const*,...) ; 
 int /*<<< orphan*/  shader_arb_get_dst_param (struct wined3d_shader_instruction const*,struct wined3d_shader_dst_param const*,char*) ; 

__attribute__((used)) static void pshader_hw_texdepth(const struct wined3d_shader_instruction *ins)
{
    const struct wined3d_shader_dst_param *dst = &ins->dst[0];
    struct wined3d_string_buffer *buffer = ins->ctx->buffer;
    char dst_name[50];
    const char *zero = arb_get_helper_value(ins->ctx->reg_maps->shader_version.type, ARB_ZERO);
    const char *one = arb_get_helper_value(ins->ctx->reg_maps->shader_version.type, ARB_ONE);

    /* texdepth has an implicit destination, the fragment depth value. It's only parameter,
     * which is essentially an input, is the destination register because it is the first
     * parameter. According to the msdn, this must be register r5, but let's keep it more flexible
     * here(writemasks/swizzles are not valid on texdepth)
     */
    shader_arb_get_dst_param(ins, dst, dst_name);

    /* According to the msdn, the source register(must be r5) is unusable after
     * the texdepth instruction, so we're free to modify it
     */
    shader_addline(buffer, "MIN %s.y, %s.y, %s;\n", dst_name, dst_name, one);

    /* How to deal with the special case dst_name.g == 0? if r != 0, then
     * the r * (1 / 0) will give infinity, which is clamped to 1.0, the correct
     * result. But if r = 0.0, then 0 * inf = 0, which is incorrect.
     */
    shader_addline(buffer, "RCP %s.y, %s.y;\n", dst_name, dst_name);
    shader_addline(buffer, "MUL TA.x, %s.x, %s.y;\n", dst_name, dst_name);
    shader_addline(buffer, "MIN TA.x, TA.x, %s;\n", one);
    shader_addline(buffer, "MAX result.depth, TA.x, %s;\n", zero);
}