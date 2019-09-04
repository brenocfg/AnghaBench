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
struct wined3d_string_buffer {int dummy; } ;
struct wined3d_shader_instruction {TYPE_2__* dst; int /*<<< orphan*/ * src; TYPE_1__* ctx; } ;
struct TYPE_4__ {int /*<<< orphan*/  reg; } ;
struct TYPE_3__ {struct wined3d_string_buffer* buffer; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,char*,char*,...) ; 
 int /*<<< orphan*/  shader_arb_get_dst_param (struct wined3d_shader_instruction const*,TYPE_2__*,char*) ; 
 int /*<<< orphan*/  shader_arb_get_modifier (struct wined3d_shader_instruction const*) ; 
 int /*<<< orphan*/  shader_arb_get_register_name (struct wined3d_shader_instruction const*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shader_arb_get_src_param (struct wined3d_shader_instruction const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void shader_hw_dsy(const struct wined3d_shader_instruction *ins)
{
    struct wined3d_string_buffer *buffer = ins->ctx->buffer;
    char src[50];
    char dst[50];
    char dst_name[50];
    BOOL is_color;

    shader_arb_get_dst_param(ins, &ins->dst[0], dst);
    shader_arb_get_src_param(ins, &ins->src[0], 0, src);
    shader_arb_get_register_name(ins, &ins->dst[0].reg, dst_name, &is_color);

    shader_addline(buffer, "DDY %s, %s;\n", dst, src);
    shader_addline(buffer, "MUL%s %s, %s, ycorrection.y;\n", shader_arb_get_modifier(ins), dst, dst_name);
}