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
struct TYPE_3__ {void* resource_data_type; int /*<<< orphan*/  reg; void* resource_type; } ;
struct TYPE_4__ {TYPE_1__ semantic; } ;
struct wined3d_shader_instruction {scalar_t__ flags; TYPE_2__ declaration; } ;
typedef  enum wined3d_sm4_resource_type { ____Placeholder_wined3d_sm4_resource_type } wined3d_sm4_resource_type ;
typedef  enum wined3d_sm4_data_type { ____Placeholder_wined3d_sm4_data_type } wined3d_sm4_data_type ;
typedef  enum wined3d_data_type { ____Placeholder_wined3d_data_type } wined3d_data_type ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int ARRAY_SIZE (void**) ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 void* WINED3D_DATA_FLOAT ; 
 int WINED3D_DATA_RESOURCE ; 
 int WINED3D_DATA_UAV ; 
 void* WINED3D_SHADER_RESOURCE_NONE ; 
 scalar_t__ WINED3D_SM4_OP_DCL_RESOURCE ; 
 scalar_t__ WINED3D_SM4_RESOURCE_TYPE_MASK ; 
 scalar_t__ WINED3D_SM4_RESOURCE_TYPE_SHIFT ; 
 scalar_t__ WINED3D_SM5_UAV_FLAGS_MASK ; 
 scalar_t__ WINED3D_SM5_UAV_FLAGS_SHIFT ; 
 void** data_type_table ; 
 void** resource_type_table ; 
 int /*<<< orphan*/  shader_sm4_read_dst_param (struct wined3d_sm4_data*,scalar_t__ const**,scalar_t__ const*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void shader_sm4_read_dcl_resource(struct wined3d_shader_instruction *ins,
        DWORD opcode, DWORD opcode_token, const DWORD *tokens, unsigned int token_count,
        struct wined3d_sm4_data *priv)
{
    enum wined3d_sm4_resource_type resource_type;
    enum wined3d_sm4_data_type data_type;
    enum wined3d_data_type reg_data_type;
    DWORD components;

    resource_type = (opcode_token & WINED3D_SM4_RESOURCE_TYPE_MASK) >> WINED3D_SM4_RESOURCE_TYPE_SHIFT;
    if (!resource_type || (resource_type >= ARRAY_SIZE(resource_type_table)))
    {
        FIXME("Unhandled resource type %#x.\n", resource_type);
        ins->declaration.semantic.resource_type = WINED3D_SHADER_RESOURCE_NONE;
    }
    else
    {
        ins->declaration.semantic.resource_type = resource_type_table[resource_type];
    }
    reg_data_type = opcode == WINED3D_SM4_OP_DCL_RESOURCE ? WINED3D_DATA_RESOURCE : WINED3D_DATA_UAV;
    shader_sm4_read_dst_param(priv, &tokens, &tokens[token_count], reg_data_type, &ins->declaration.semantic.reg);

    components = *tokens++;
    if ((components & 0xfff0) != (components & 0xf) * 0x1110)
        FIXME("Components (%#x) have different data types.\n", components);
    data_type = components & 0xf;

    if (!data_type || (data_type >= ARRAY_SIZE(data_type_table)))
    {
        FIXME("Unhandled data type %#x.\n", data_type);
        ins->declaration.semantic.resource_data_type = WINED3D_DATA_FLOAT;
    }
    else
    {
        ins->declaration.semantic.resource_data_type = data_type_table[data_type];
    }

    if (reg_data_type == WINED3D_DATA_UAV)
        ins->flags = (opcode_token & WINED3D_SM5_UAV_FLAGS_MASK) >> WINED3D_SM5_UAV_FLAGS_SHIFT;
}