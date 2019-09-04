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
struct wined3d_shader_instruction {TYPE_1__* dst; TYPE_2__* ctx; } ;
struct color_fixup_desc {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  data_type; } ;
struct TYPE_5__ {int /*<<< orphan*/  buffer; } ;
struct TYPE_4__ {int /*<<< orphan*/  write_mask; TYPE_3__ reg; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  shader_glsl_color_correction_ext (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct color_fixup_desc) ; 
 int /*<<< orphan*/  shader_glsl_get_register_name (TYPE_3__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,struct wined3d_shader_instruction const*) ; 

__attribute__((used)) static void shader_glsl_color_correction(const struct wined3d_shader_instruction *ins, struct color_fixup_desc fixup)
{
    char reg_name[256];
    BOOL is_color;

    shader_glsl_get_register_name(&ins->dst[0].reg, ins->dst[0].reg.data_type, reg_name, &is_color, ins);
    shader_glsl_color_correction_ext(ins->ctx->buffer, reg_name, ins->dst[0].write_mask, fixup);
}