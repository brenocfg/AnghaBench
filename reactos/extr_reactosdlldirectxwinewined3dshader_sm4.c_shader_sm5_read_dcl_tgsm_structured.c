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
struct TYPE_4__ {int byte_stride; int /*<<< orphan*/  structure_count; int /*<<< orphan*/  reg; } ;
struct TYPE_3__ {TYPE_2__ tgsm_structured; } ;
struct wined3d_shader_instruction {TYPE_1__ declaration; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  WINED3D_DATA_FLOAT ; 
 int /*<<< orphan*/  shader_sm4_read_dst_param (struct wined3d_sm4_data*,int /*<<< orphan*/  const**,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void shader_sm5_read_dcl_tgsm_structured(struct wined3d_shader_instruction *ins,
        DWORD opcode, DWORD opcode_token, const DWORD *tokens, unsigned int token_count,
        struct wined3d_sm4_data *priv)
{
    shader_sm4_read_dst_param(priv, &tokens, &tokens[token_count], WINED3D_DATA_FLOAT,
            &ins->declaration.tgsm_structured.reg);
    ins->declaration.tgsm_structured.byte_stride = *tokens++;
    ins->declaration.tgsm_structured.structure_count = *tokens;
    if (ins->declaration.tgsm_structured.byte_stride % 4)
        FIXME("Byte stride %u is not multiple of 4.\n", ins->declaration.tgsm_structured.byte_stride);
}