#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct wined3d_string_buffer {int dummy; } ;
struct TYPE_10__ {scalar_t__ type; TYPE_3__* idx; } ;
struct wined3d_shader_src_param {TYPE_4__ reg; } ;
struct TYPE_12__ {int /*<<< orphan*/  type; } ;
struct wined3d_shader_reg_maps {TYPE_6__ shader_version; int /*<<< orphan*/  sampler_map; TYPE_5__* resource_info; } ;
struct wined3d_shader_instruction {scalar_t__ flags; struct wined3d_shader_src_param* src; struct wined3d_shader_dst_param* dst; TYPE_1__* ctx; } ;
struct TYPE_8__ {int data_type; } ;
struct wined3d_shader_dst_param {TYPE_2__ reg; } ;
struct wined3d_gl_info {scalar_t__* supported; } ;
typedef  enum wined3d_shader_resource_type { ____Placeholder_wined3d_shader_resource_type } wined3d_shader_resource_type ;
typedef  enum wined3d_data_type { ____Placeholder_wined3d_data_type } wined3d_data_type ;
struct TYPE_11__ {int type; } ;
struct TYPE_9__ {unsigned int offset; } ;
struct TYPE_7__ {struct wined3d_string_buffer* buffer; struct wined3d_gl_info* gl_info; struct wined3d_shader_reg_maps* reg_maps; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 size_t ARB_SAMPLE_SHADING ; 
 size_t ARB_SHADER_TEXTURE_IMAGE_SAMPLES ; 
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR (char*,int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*,...) ; 
 scalar_t__ WINED3DSI_SAMPLE_INFO_UINT ; 
 scalar_t__ WINED3DSPR_RASTERIZER ; 
 int WINED3D_DATA_UINT ; 
 int /*<<< orphan*/  WINED3D_SAMPLER_DEFAULT ; 
 int /*<<< orphan*/  resource_type_info ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,...) ; 
 int /*<<< orphan*/  shader_glsl_append_dst_ext (struct wined3d_string_buffer*,struct wined3d_shader_instruction const*,struct wined3d_shader_dst_param const*,int) ; 
 unsigned int shader_glsl_find_sampler (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_glsl_get_prefix (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_glsl_get_swizzle (struct wined3d_shader_src_param const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void shader_glsl_sample_info(const struct wined3d_shader_instruction *ins)
{
    const struct wined3d_shader_reg_maps *reg_maps = ins->ctx->reg_maps;
    const struct wined3d_gl_info *gl_info = ins->ctx->gl_info;
    struct wined3d_string_buffer *buffer = ins->ctx->buffer;
    const struct wined3d_shader_dst_param *dst = ins->dst;
    const struct wined3d_shader_src_param *src = ins->src;
    enum wined3d_shader_resource_type resource_type;
    enum wined3d_data_type dst_data_type;
    unsigned int resource_idx, bind_idx;
    char dst_swizzle[6];
    DWORD write_mask;

    dst_data_type = dst->reg.data_type;
    if (ins->flags == WINED3DSI_SAMPLE_INFO_UINT)
        dst_data_type = WINED3D_DATA_UINT;
    else if (ins->flags)
        FIXME("Unhandled flags %#x.\n", ins->flags);

    write_mask = shader_glsl_append_dst_ext(buffer, ins, dst, dst_data_type);
    shader_glsl_get_swizzle(src, FALSE, write_mask, dst_swizzle);

    if (dst_data_type == WINED3D_DATA_UINT)
        shader_addline(buffer, "uvec4(");
    else
        shader_addline(buffer, "vec4(");

    if (src->reg.type == WINED3DSPR_RASTERIZER)
    {
        if (gl_info->supported[ARB_SAMPLE_SHADING])
        {
            shader_addline(buffer, "gl_NumSamples");
        }
        else
        {
            FIXME("OpenGL implementation does not support ARB_sample_shading.\n");
            shader_addline(buffer, "1");
        }
    }
    else
    {
        resource_idx = src->reg.idx[0].offset;
        resource_type = reg_maps->resource_info[resource_idx].type;
        if (resource_type >= ARRAY_SIZE(resource_type_info))
        {
            ERR("Unexpected resource type %#x.\n", resource_type);
            return;
        }
        bind_idx = shader_glsl_find_sampler(&reg_maps->sampler_map, resource_idx, WINED3D_SAMPLER_DEFAULT);

        if (gl_info->supported[ARB_SHADER_TEXTURE_IMAGE_SAMPLES])
        {
            shader_addline(buffer, "textureSamples(%s_sampler%u)",
                    shader_glsl_get_prefix(reg_maps->shader_version.type), bind_idx);
        }
        else
        {
            FIXME("textureSamples() is not supported.\n");
            shader_addline(buffer, "1");
        }
    }

    shader_addline(buffer, ", 0, 0, 0)%s);\n", dst_swizzle);
}