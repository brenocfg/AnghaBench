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
struct wined3d_shader_resource_info {int dummy; } ;
struct wined3d_shader_register {scalar_t__ type; TYPE_1__* idx; } ;
struct wined3d_shader_reg_maps {struct wined3d_shader_resource_info const* uav_resource_info; struct wined3d_shader_resource_info const* resource_info; } ;
struct wined3d_shader_instruction {TYPE_2__* ctx; } ;
struct TYPE_4__ {struct wined3d_shader_reg_maps* reg_maps; } ;
struct TYPE_3__ {unsigned int offset; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct wined3d_shader_resource_info const*) ; 
 int /*<<< orphan*/  ERR (char*,unsigned int) ; 
 int /*<<< orphan*/  FIXME (char*,scalar_t__) ; 
 scalar_t__ WINED3DSPR_RESOURCE ; 
 scalar_t__ WINED3DSPR_UAV ; 

__attribute__((used)) static const struct wined3d_shader_resource_info *shader_glsl_get_resource_info(
        const struct wined3d_shader_instruction *ins, const struct wined3d_shader_register *reg)
{
    const struct wined3d_shader_reg_maps *reg_maps = ins->ctx->reg_maps;
    unsigned int idx = reg->idx[0].offset;

    if (reg->type == WINED3DSPR_RESOURCE)
    {
        if (idx >= ARRAY_SIZE(reg_maps->resource_info))
        {
            ERR("Invalid resource index %u.\n", idx);
            return NULL;
        }
        return &reg_maps->resource_info[idx];
    }

    if (reg->type == WINED3DSPR_UAV)
    {
        if (idx >= ARRAY_SIZE(reg_maps->uav_resource_info))
        {
            ERR("Invalid UAV index %u.\n", idx);
            return NULL;
        }
        return &reg_maps->uav_resource_info[idx];
    }

    FIXME("Unhandled register type %#x.\n", reg->type);
    return NULL;
}