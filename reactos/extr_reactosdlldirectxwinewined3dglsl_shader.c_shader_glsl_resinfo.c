#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;

/* Type definitions */
struct wined3d_string_buffer {int dummy; } ;
struct wined3d_shader_version {int /*<<< orphan*/  type; } ;
struct wined3d_shader_instruction {scalar_t__ flags; TYPE_8__* src; TYPE_9__* dst; TYPE_7__* ctx; } ;
struct wined3d_gl_info {scalar_t__* supported; } ;
struct glsl_src_param {char* param_str; } ;
typedef  enum wined3d_shader_resource_type { ____Placeholder_wined3d_shader_resource_type } wined3d_shader_resource_type ;
typedef  enum wined3d_shader_register_type { ____Placeholder_wined3d_shader_register_type } wined3d_shader_register_type ;
typedef  enum wined3d_data_type { ____Placeholder_wined3d_data_type } wined3d_data_type ;
struct TYPE_14__ {int data_type; } ;
struct TYPE_22__ {TYPE_1__ reg; } ;
struct TYPE_16__ {int type; TYPE_2__* idx; } ;
struct TYPE_21__ {TYPE_3__ reg; } ;
struct TYPE_20__ {TYPE_6__* reg_maps; struct wined3d_string_buffer* buffer; struct wined3d_gl_info* gl_info; } ;
struct TYPE_19__ {TYPE_5__* uav_resource_info; int /*<<< orphan*/  sampler_map; TYPE_4__* resource_info; struct wined3d_shader_version shader_version; } ;
struct TYPE_18__ {int type; } ;
struct TYPE_17__ {int type; } ;
struct TYPE_15__ {unsigned int offset; } ;
struct TYPE_13__ {int resinfo_size; } ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 size_t ARB_TEXTURE_QUERY_LEVELS ; 
 int ARRAY_SIZE (TYPE_11__*) ; 
 int /*<<< orphan*/  ERR (char*,int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*,...) ; 
 scalar_t__ WINED3DSI_RESINFO_UINT ; 
 int WINED3DSPR_RESOURCE ; 
 int WINED3DSPR_UAV ; 
 int /*<<< orphan*/  WINED3DSP_WRITEMASK_0 ; 
 int WINED3D_DATA_UINT ; 
 int /*<<< orphan*/  WINED3D_SAMPLER_DEFAULT ; 
 scalar_t__ is_mipmapped (int) ; 
 TYPE_11__* resource_type_info ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,...) ; 
 int /*<<< orphan*/  shader_glsl_add_src_param (struct wined3d_shader_instruction const*,TYPE_8__*,int /*<<< orphan*/ ,struct glsl_src_param*) ; 
 int /*<<< orphan*/  shader_glsl_append_dst_ext (struct wined3d_string_buffer*,struct wined3d_shader_instruction const*,TYPE_9__*,int) ; 
 unsigned int shader_glsl_find_sampler (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_glsl_get_prefix (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_glsl_get_swizzle (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void shader_glsl_resinfo(const struct wined3d_shader_instruction *ins)
{
    const struct wined3d_shader_version *version = &ins->ctx->reg_maps->shader_version;
    const struct wined3d_gl_info *gl_info = ins->ctx->gl_info;
    struct wined3d_string_buffer *buffer = ins->ctx->buffer;
    enum wined3d_shader_resource_type resource_type;
    enum wined3d_shader_register_type reg_type;
    unsigned int resource_idx, bind_idx, i;
    enum wined3d_data_type dst_data_type;
    struct glsl_src_param lod_param;
    BOOL supports_mipmaps;
    char dst_swizzle[6];
    DWORD write_mask;

    dst_data_type = ins->dst[0].reg.data_type;
    if (ins->flags == WINED3DSI_RESINFO_UINT)
        dst_data_type = WINED3D_DATA_UINT;
    else if (ins->flags)
        FIXME("Unhandled flags %#x.\n", ins->flags);

    reg_type = ins->src[1].reg.type;
    resource_idx = ins->src[1].reg.idx[0].offset;
    shader_glsl_add_src_param(ins, &ins->src[0], WINED3DSP_WRITEMASK_0, &lod_param);
    if (reg_type == WINED3DSPR_RESOURCE)
    {
        resource_type = ins->ctx->reg_maps->resource_info[resource_idx].type;
        bind_idx = shader_glsl_find_sampler(&ins->ctx->reg_maps->sampler_map,
                resource_idx, WINED3D_SAMPLER_DEFAULT);
    }
    else
    {
        resource_type = ins->ctx->reg_maps->uav_resource_info[resource_idx].type;
        bind_idx = resource_idx;
    }

    if (resource_type >= ARRAY_SIZE(resource_type_info))
    {
        ERR("Unexpected resource type %#x.\n", resource_type);
        return;
    }

    write_mask = shader_glsl_append_dst_ext(buffer, ins, &ins->dst[0], dst_data_type);
    shader_glsl_get_swizzle(&ins->src[1], FALSE, write_mask, dst_swizzle);

    if (dst_data_type == WINED3D_DATA_UINT)
        shader_addline(buffer, "uvec4(");
    else
        shader_addline(buffer, "vec4(");

    if (reg_type == WINED3DSPR_RESOURCE)
    {
        shader_addline(buffer, "textureSize(%s_sampler%u",
                shader_glsl_get_prefix(version->type), bind_idx);
    }
    else
    {
        shader_addline(buffer, "imageSize(%s_image%u",
                shader_glsl_get_prefix(version->type), bind_idx);
    }

    supports_mipmaps = is_mipmapped(resource_type) && reg_type != WINED3DSPR_UAV;
    if (supports_mipmaps)
        shader_addline(buffer, ", %s", lod_param.param_str);
    shader_addline(buffer, "), ");

    for (i = 0; i < 3 - resource_type_info[resource_type].resinfo_size; ++i)
        shader_addline(buffer, "0, ");

    if (supports_mipmaps)
    {
        if (gl_info->supported[ARB_TEXTURE_QUERY_LEVELS])
        {
            shader_addline(buffer, "textureQueryLevels(%s_sampler%u)",
                    shader_glsl_get_prefix(version->type), bind_idx);
        }
        else
        {
            FIXME("textureQueryLevels is not supported, returning 1 level.\n");
            shader_addline(buffer, "1");
        }
    }
    else
    {
        shader_addline(buffer, "1");
    }

    shader_addline(buffer, ")%s);\n", dst_swizzle);
}