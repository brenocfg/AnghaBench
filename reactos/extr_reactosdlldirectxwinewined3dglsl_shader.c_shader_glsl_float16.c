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
struct wined3d_shader_instruction {scalar_t__ handler_idx; TYPE_2__* ctx; int /*<<< orphan*/ * src; struct wined3d_shader_dst_param* dst; } ;
struct TYPE_3__ {int /*<<< orphan*/  data_type; } ;
struct wined3d_shader_dst_param {unsigned int write_mask; TYPE_1__ reg; } ;
struct glsl_src_param {int /*<<< orphan*/  param_str; } ;
struct TYPE_4__ {int /*<<< orphan*/  buffer; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 scalar_t__ WINED3DSIH_F16TOF32 ; 
 unsigned int WINED3DSP_WRITEMASK_0 ; 
 int /*<<< orphan*/  shader_addline (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_glsl_add_src_param (struct wined3d_shader_instruction const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct glsl_src_param*) ; 
 int /*<<< orphan*/  shader_glsl_append_dst_ext (int /*<<< orphan*/ ,struct wined3d_shader_instruction const*,struct wined3d_shader_dst_param*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void shader_glsl_float16(const struct wined3d_shader_instruction *ins)
{
    struct wined3d_shader_dst_param dst;
    struct glsl_src_param src;
    DWORD write_mask;
    const char *fmt;
    unsigned int i;

    fmt = ins->handler_idx == WINED3DSIH_F16TOF32
            ? "unpackHalf2x16(%s).x);\n" : "packHalf2x16(vec2(%s, 0.0)));\n";

    dst = ins->dst[0];
    for (i = 0; i < 4; ++i)
    {
        dst.write_mask = ins->dst[0].write_mask & (WINED3DSP_WRITEMASK_0 << i);
        if (!(write_mask = shader_glsl_append_dst_ext(ins->ctx->buffer, ins,
                &dst, dst.reg.data_type)))
            continue;

        shader_glsl_add_src_param(ins, &ins->src[0], write_mask, &src);
        shader_addline(ins->ctx->buffer, fmt, src.param_str);
    }
}