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
struct shader_arb_ctx_priv {scalar_t__ target_version; } ;
struct TYPE_4__ {int modifiers; } ;
struct TYPE_3__ {struct shader_arb_ctx_priv* backend_data; struct wined3d_string_buffer* buffer; } ;

/* Variables and functions */
 scalar_t__ NV2 ; 
 int WINED3DSPDM_SATURATE ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,char*,char*,...) ; 
 int /*<<< orphan*/  shader_arb_get_dst_param (struct wined3d_shader_instruction const*,TYPE_2__*,char*) ; 
 int /*<<< orphan*/  shader_arb_get_modifier (struct wined3d_shader_instruction const*) ; 
 int /*<<< orphan*/  shader_arb_get_src_param (struct wined3d_shader_instruction const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strstr (char*,char*) ; 

__attribute__((used)) static void shader_hw_sgn(const struct wined3d_shader_instruction *ins)
{
    struct wined3d_string_buffer *buffer = ins->ctx->buffer;
    char dst_name[50];
    char src_name[50];
    struct shader_arb_ctx_priv *ctx = ins->ctx->backend_data;

    shader_arb_get_dst_param(ins, &ins->dst[0], dst_name);
    shader_arb_get_src_param(ins, &ins->src[0], 0, src_name);

    /* SGN is only valid in vertex shaders */
    if(ctx->target_version >= NV2) {
        shader_addline(buffer, "SSG%s %s, %s;\n", shader_arb_get_modifier(ins), dst_name, src_name);
        return;
    }

    /* If SRC > 0.0, -SRC < SRC = TRUE, otherwise false.
     * if SRC < 0.0,  SRC < -SRC = TRUE. If neither is true, src = 0.0
     */
    if(ins->dst[0].modifiers & WINED3DSPDM_SATURATE) {
        shader_addline(buffer, "SLT %s, -%s, %s;\n", dst_name, src_name, src_name);
    } else {
        /* src contains TA? Write to the dest first. This won't overwrite our destination.
         * Then use TA, and calculate the final result
         *
         * Not reading from TA? Store the first result in TA to avoid overwriting the
         * destination if src reg = dst reg
         */
        if(strstr(src_name, "TA"))
        {
            shader_addline(buffer, "SLT %s,  %s, -%s;\n", dst_name, src_name, src_name);
            shader_addline(buffer, "SLT TA, -%s, %s;\n", src_name, src_name);
            shader_addline(buffer, "ADD %s, %s, -TA;\n", dst_name, dst_name);
        }
        else
        {
            shader_addline(buffer, "SLT TA, -%s, %s;\n", src_name, src_name);
            shader_addline(buffer, "SLT %s,  %s, -%s;\n", dst_name, src_name, src_name);
            shader_addline(buffer, "ADD %s, TA, -%s;\n", dst_name, dst_name);
        }
    }
}