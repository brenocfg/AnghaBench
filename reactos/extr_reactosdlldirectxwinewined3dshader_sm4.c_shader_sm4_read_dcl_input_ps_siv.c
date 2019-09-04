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
struct wined3d_sm4_data {int dummy; } ;
struct TYPE_3__ {int sysval_semantic; int /*<<< orphan*/  reg; } ;
struct TYPE_4__ {TYPE_1__ register_semantic; } ;
struct wined3d_shader_instruction {int flags; TYPE_2__ declaration; } ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  WINED3D_DATA_FLOAT ; 
 int WINED3D_SM4_INTERPOLATION_MODE_MASK ; 
 int WINED3D_SM4_INTERPOLATION_MODE_SHIFT ; 
 int /*<<< orphan*/  shader_sm4_read_dst_param (struct wined3d_sm4_data*,int const**,int const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void shader_sm4_read_dcl_input_ps_siv(struct wined3d_shader_instruction *ins,
        DWORD opcode, DWORD opcode_token, const DWORD *tokens, unsigned int token_count,
        struct wined3d_sm4_data *priv)
{
    ins->flags = (opcode_token & WINED3D_SM4_INTERPOLATION_MODE_MASK) >> WINED3D_SM4_INTERPOLATION_MODE_SHIFT;
    shader_sm4_read_dst_param(priv, &tokens, &tokens[token_count], WINED3D_DATA_FLOAT,
            &ins->declaration.register_semantic.reg);
    ins->declaration.register_semantic.sysval_semantic = *tokens;
}