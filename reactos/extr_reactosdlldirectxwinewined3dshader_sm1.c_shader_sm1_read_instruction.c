#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wined3d_sm1_opcode_info {scalar_t__ handler_idx; unsigned int dst_count; unsigned int param_count; } ;
struct wined3d_sm1_data {int /*<<< orphan*/ * src_rel_addr; int /*<<< orphan*/ * src_param; int /*<<< orphan*/  pred_rel_addr; int /*<<< orphan*/  pred_param; int /*<<< orphan*/  dst_rel_addr; int /*<<< orphan*/  dst_param; } ;
struct TYPE_2__ {int /*<<< orphan*/  semantic; } ;
struct wined3d_shader_instruction {scalar_t__ handler_idx; int flags; int coissue; int dst_count; unsigned int src_count; int /*<<< orphan*/ * predicate; TYPE_1__ declaration; int /*<<< orphan*/  texel_offset; int /*<<< orphan*/ * src; int /*<<< orphan*/ * dst; } ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int) ; 
 scalar_t__ WINED3DSIH_DCL ; 
 scalar_t__ WINED3DSIH_DEF ; 
 scalar_t__ WINED3DSIH_DEFB ; 
 scalar_t__ WINED3DSIH_DEFI ; 
 scalar_t__ WINED3DSIH_TABLE_SIZE ; 
 int /*<<< orphan*/  WINED3D_DATA_FLOAT ; 
 int /*<<< orphan*/  WINED3D_DATA_INT ; 
 int /*<<< orphan*/  WINED3D_DATA_UINT ; 
 int /*<<< orphan*/  WINED3D_IMMCONST_SCALAR ; 
 int /*<<< orphan*/  WINED3D_IMMCONST_VEC4 ; 
 int WINED3D_SM1_COISSUE ; 
 int WINED3D_SM1_INSTRUCTION_FLAGS_MASK ; 
 int WINED3D_SM1_INSTRUCTION_FLAGS_SHIFT ; 
 int WINED3D_SM1_INSTRUCTION_PREDICATED ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct wined3d_sm1_opcode_info* shader_get_opcode (struct wined3d_sm1_data*,int) ; 
 int /*<<< orphan*/  shader_skip_opcode (struct wined3d_sm1_data*,struct wined3d_sm1_opcode_info const*,int) ; 
 int /*<<< orphan*/  shader_skip_unrecognized (struct wined3d_sm1_data*,int const*) ; 
 int /*<<< orphan*/  shader_sm1_read_comment (int const**) ; 
 int /*<<< orphan*/  shader_sm1_read_dst_param (struct wined3d_sm1_data*,int const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shader_sm1_read_immconst (int const**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_sm1_read_semantic (int const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shader_sm1_read_src_param (struct wined3d_sm1_data*,int const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shader_sm1_validate_instruction (struct wined3d_shader_instruction*) ; 

__attribute__((used)) static void shader_sm1_read_instruction(void *data, const DWORD **ptr, struct wined3d_shader_instruction *ins)
{
    const struct wined3d_sm1_opcode_info *opcode_info;
    struct wined3d_sm1_data *priv = data;
    DWORD opcode_token;
    unsigned int i;
    const DWORD *p;

    shader_sm1_read_comment(ptr);

    opcode_token = *(*ptr)++;
    if (!(opcode_info = shader_get_opcode(priv, opcode_token)))
    {
        FIXME("Unrecognized opcode: token=0x%08x.\n", opcode_token);
        ins->handler_idx = WINED3DSIH_TABLE_SIZE;
        *ptr += shader_skip_unrecognized(priv, *ptr);
        return;
    }

    ins->handler_idx = opcode_info->handler_idx;
    ins->flags = (opcode_token & WINED3D_SM1_INSTRUCTION_FLAGS_MASK) >> WINED3D_SM1_INSTRUCTION_FLAGS_SHIFT;
    ins->coissue = opcode_token & WINED3D_SM1_COISSUE;
    ins->predicate = opcode_token & WINED3D_SM1_INSTRUCTION_PREDICATED ? &priv->pred_param : NULL;
    ins->dst_count = opcode_info->dst_count ? 1 : 0;
    ins->dst = &priv->dst_param;
    ins->src_count = opcode_info->param_count - opcode_info->dst_count;
    ins->src = priv->src_param;
    memset(&ins->texel_offset, 0, sizeof(ins->texel_offset));

    p = *ptr;
    *ptr += shader_skip_opcode(priv, opcode_info, opcode_token);

    if (ins->handler_idx == WINED3DSIH_DCL)
    {
        shader_sm1_read_semantic(&p, &ins->declaration.semantic);
    }
    else if (ins->handler_idx == WINED3DSIH_DEF)
    {
        shader_sm1_read_dst_param(priv, &p, &priv->dst_param, &priv->dst_rel_addr);
        shader_sm1_read_immconst(&p, &priv->src_param[0], WINED3D_IMMCONST_VEC4, WINED3D_DATA_FLOAT);
    }
    else if (ins->handler_idx == WINED3DSIH_DEFB)
    {
        shader_sm1_read_dst_param(priv, &p, &priv->dst_param, &priv->dst_rel_addr);
        shader_sm1_read_immconst(&p, &priv->src_param[0], WINED3D_IMMCONST_SCALAR, WINED3D_DATA_UINT);
    }
    else if (ins->handler_idx == WINED3DSIH_DEFI)
    {
        shader_sm1_read_dst_param(priv, &p, &priv->dst_param, &priv->dst_rel_addr);
        shader_sm1_read_immconst(&p, &priv->src_param[0], WINED3D_IMMCONST_VEC4, WINED3D_DATA_INT);
    }
    else
    {
        /* Destination token */
        if (ins->dst_count)
            shader_sm1_read_dst_param(priv, &p, &priv->dst_param, &priv->dst_rel_addr);

        /* Predication token */
        if (ins->predicate)
            shader_sm1_read_src_param(priv, &p, &priv->pred_param, &priv->pred_rel_addr);

        /* Other source tokens */
        for (i = 0; i < ins->src_count; ++i)
            shader_sm1_read_src_param(priv, &p, &priv->src_param[i], &priv->src_rel_addr[i]);
    }

    shader_sm1_validate_instruction(ins);
}