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
struct wined3d_shader_instruction {int flags; TYPE_3__* src; int /*<<< orphan*/ * dst; } ;
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_5__ {TYPE_1__* idx; } ;
struct TYPE_6__ {TYPE_2__ reg; } ;
struct TYPE_4__ {int /*<<< orphan*/  offset; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  TEX_BIAS ; 
 int /*<<< orphan*/  TEX_LOD ; 
 int /*<<< orphan*/  TEX_PROJ ; 
 int WINED3DSI_TEXLD_BIAS ; 
 int WINED3DSI_TEXLD_PROJECT ; 
 int /*<<< orphan*/  shader_arb_get_dst_param (struct wined3d_shader_instruction const*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  shader_arb_get_src_param (struct wined3d_shader_instruction const*,TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  shader_hw_sample (struct wined3d_shader_instruction const*,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void shader_hw_texldl(const struct wined3d_shader_instruction *ins)
{
    DWORD sampler_idx = ins->src[1].reg.idx[0].offset;
    char reg_dest[40];
    char reg_coord[40];
    WORD flags = TEX_LOD;

    shader_arb_get_dst_param(ins, &ins->dst[0], reg_dest);
    shader_arb_get_src_param(ins, &ins->src[0], 0, reg_coord);

    if (ins->flags & WINED3DSI_TEXLD_PROJECT) flags |= TEX_PROJ;
    if (ins->flags & WINED3DSI_TEXLD_BIAS) flags |= TEX_BIAS;

    shader_hw_sample(ins, sampler_idx, reg_dest, reg_coord, flags, NULL, NULL);
}