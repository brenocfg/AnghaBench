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
struct TYPE_3__ {int /*<<< orphan*/  type; } ;
struct TYPE_4__ {TYPE_1__ primitive_type; } ;
struct wined3d_shader_instruction {TYPE_2__ declaration; } ;
typedef  enum wined3d_sm4_output_primitive_type { ____Placeholder_wined3d_sm4_output_primitive_type } wined3d_sm4_output_primitive_type ;
typedef  int DWORD ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  WINED3D_PT_UNDEFINED ; 
 int WINED3D_SM4_PRIMITIVE_TYPE_MASK ; 
 int WINED3D_SM4_PRIMITIVE_TYPE_SHIFT ; 
 int /*<<< orphan*/ * output_primitive_type_table ; 

__attribute__((used)) static void shader_sm4_read_dcl_output_topology(struct wined3d_shader_instruction *ins,
        DWORD opcode, DWORD opcode_token, const DWORD *tokens, unsigned int token_count,
        struct wined3d_sm4_data *priv)
{
    enum wined3d_sm4_output_primitive_type primitive_type;

    primitive_type = (opcode_token & WINED3D_SM4_PRIMITIVE_TYPE_MASK) >> WINED3D_SM4_PRIMITIVE_TYPE_SHIFT;
    if (primitive_type >= ARRAY_SIZE(output_primitive_type_table))
        ins->declaration.primitive_type.type = WINED3D_PT_UNDEFINED;
    else
        ins->declaration.primitive_type.type = output_primitive_type_table[primitive_type];

    if (ins->declaration.primitive_type.type == WINED3D_PT_UNDEFINED)
        FIXME("Unhandled output primitive type %#x.\n", primitive_type);
}