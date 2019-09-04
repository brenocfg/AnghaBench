#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct wined3d_string_buffer {int /*<<< orphan*/  buffer; } ;
struct TYPE_8__ {int /*<<< orphan*/  type; } ;
struct wined3d_shader_reg_maps {unsigned int tgsm_count; TYPE_7__* uav_resource_info; TYPE_5__* tgsm; TYPE_1__ shader_version; } ;
struct wined3d_shader_instruction {scalar_t__ handler_idx; int /*<<< orphan*/ * src; TYPE_6__* dst; TYPE_2__* ctx; } ;
struct shader_glsl_ctx_priv {int /*<<< orphan*/  string_buffers; } ;
struct glsl_src_param {int /*<<< orphan*/  param_str; } ;
struct TYPE_14__ {unsigned int stride; } ;
struct TYPE_11__ {scalar_t__ type; TYPE_3__* idx; } ;
struct TYPE_13__ {unsigned int write_mask; TYPE_4__ reg; } ;
struct TYPE_12__ {unsigned int stride; } ;
struct TYPE_10__ {unsigned int offset; } ;
struct TYPE_9__ {struct wined3d_string_buffer* buffer; struct shader_glsl_ctx_priv* backend_data; struct wined3d_shader_reg_maps* reg_maps; } ;
typedef  unsigned int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_7__*) ; 
 int /*<<< orphan*/  ERR (char*,unsigned int) ; 
 scalar_t__ WINED3DSIH_STORE_STRUCTURED ; 
 scalar_t__ WINED3DSPR_GROUPSHAREDMEM ; 
 unsigned int WINED3DSP_WRITEMASK_0 ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,char const*,...) ; 
 int /*<<< orphan*/  shader_glsl_add_src_param (struct wined3d_shader_instruction const*,int /*<<< orphan*/ *,unsigned int,struct glsl_src_param*) ; 
 char* shader_glsl_get_prefix (int /*<<< orphan*/ ) ; 
 struct wined3d_string_buffer* string_buffer_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_buffer_release (int /*<<< orphan*/ ,struct wined3d_string_buffer*) ; 

__attribute__((used)) static void shader_glsl_store_raw_structured(const struct wined3d_shader_instruction *ins)
{
    const char *prefix = shader_glsl_get_prefix(ins->ctx->reg_maps->shader_version.type);
    const struct wined3d_shader_reg_maps *reg_maps = ins->ctx->reg_maps;
    struct shader_glsl_ctx_priv *priv = ins->ctx->backend_data;
    struct wined3d_string_buffer *buffer = ins->ctx->buffer;
    struct glsl_src_param structure_idx, offset, data;
    unsigned int i, resource_idx, stride, src_idx = 0;
    struct wined3d_string_buffer *address;
    DWORD write_mask;
    BOOL is_tgsm;

    resource_idx = ins->dst[0].reg.idx[0].offset;
    is_tgsm = ins->dst[0].reg.type == WINED3DSPR_GROUPSHAREDMEM;
    if (is_tgsm)
    {
        if (resource_idx >= reg_maps->tgsm_count)
        {
            ERR("Invalid TGSM index %u.\n", resource_idx);
            return;
        }
        stride = reg_maps->tgsm[resource_idx].stride;
    }
    else
    {
        if (resource_idx >= ARRAY_SIZE(reg_maps->uav_resource_info))
        {
            ERR("Invalid UAV index %u.\n", resource_idx);
            return;
        }
        stride = reg_maps->uav_resource_info[resource_idx].stride;
    }

    address = string_buffer_get(priv->string_buffers);
    if (ins->handler_idx == WINED3DSIH_STORE_STRUCTURED)
    {
        shader_glsl_add_src_param(ins, &ins->src[src_idx++], WINED3DSP_WRITEMASK_0, &structure_idx);
        shader_addline(address, "%s * %u + ", structure_idx.param_str, stride);
    }
    shader_glsl_add_src_param(ins, &ins->src[src_idx++], WINED3DSP_WRITEMASK_0, &offset);
    shader_addline(address, "%s / 4", offset.param_str);

    for (i = 0; i < 4; ++i)
    {
        if (!(write_mask = ins->dst[0].write_mask & (WINED3DSP_WRITEMASK_0 << i)))
            continue;

        shader_glsl_add_src_param(ins, &ins->src[src_idx], write_mask, &data);

        if (is_tgsm)
            shader_addline(buffer, "%s_g%u[%s + %u] = %s;\n",
                    prefix, resource_idx, address->buffer, i, data.param_str);
        else
            shader_addline(buffer, "imageStore(%s_image%u, %s + %u, uvec4(%s, 0, 0, 0));\n",
                    prefix, resource_idx, address->buffer, i, data.param_str);
    }

    string_buffer_release(priv->string_buffers, address);
}