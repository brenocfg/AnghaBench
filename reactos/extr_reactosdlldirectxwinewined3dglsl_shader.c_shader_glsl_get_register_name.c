#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct wined3d_shader_version {int major; int /*<<< orphan*/  type; } ;
struct TYPE_19__ {int* immconst_data; } ;
struct wined3d_shader_register {int type; int immconst_type; TYPE_9__* idx; TYPE_8__ u; } ;
struct wined3d_shader_reg_maps {struct wined3d_shader_version shader_version; } ;
struct wined3d_shader_instruction {TYPE_6__* ctx; } ;
struct TYPE_13__ {int* input_reg_map; unsigned int declared_in_count; } ;
struct TYPE_14__ {TYPE_2__ ps; } ;
struct wined3d_shader {TYPE_4__* limits; TYPE_3__ u; } ;
struct TYPE_18__ {int buffers; } ;
struct wined3d_gl_info {int /*<<< orphan*/ * supported; TYPE_7__ limits; } ;
struct shader_glsl_ctx_priv {TYPE_1__* cur_vs_args; } ;
struct glsl_src_param {char* param_str; } ;
typedef  enum wined3d_data_type { ____Placeholder_wined3d_data_type } wined3d_data_type ;
struct TYPE_20__ {unsigned int offset; scalar_t__ rel_addr; } ;
struct TYPE_17__ {TYPE_5__* state; struct shader_glsl_ctx_priv* backend_data; struct wined3d_gl_info* gl_info; struct wined3d_shader_reg_maps* reg_maps; struct wined3d_shader* shader; } ;
struct TYPE_16__ {int /*<<< orphan*/  current_loop_reg; } ;
struct TYPE_15__ {int constant_float; } ;
struct TYPE_12__ {unsigned int swizzle_map; } ;
struct TYPE_11__ {int /*<<< orphan*/  check_float_constants; } ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 size_t ARB_SHADER_BIT_ENCODING ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*,...) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WARN (char*,int,int) ; 
#define  WINED3DSPR_ATTROUT 168 
#define  WINED3DSPR_COLOROUT 167 
#define  WINED3DSPR_CONST 166 
#define  WINED3DSPR_CONSTBOOL 165 
#define  WINED3DSPR_CONSTBUFFER 164 
#define  WINED3DSPR_CONSTINT 163 
#define  WINED3DSPR_DEPTHOUT 162 
#define  WINED3DSPR_DEPTHOUTGE 161 
#define  WINED3DSPR_DEPTHOUTLE 160 
#define  WINED3DSPR_FORKINSTID 159 
#define  WINED3DSPR_GSINSTID 158 
#define  WINED3DSPR_IDXTEMP 157 
#define  WINED3DSPR_IMMCONST 156 
#define  WINED3DSPR_IMMCONSTBUFFER 155 
#define  WINED3DSPR_INCONTROLPOINT 154 
#define  WINED3DSPR_INPUT 153 
#define  WINED3DSPR_JOININSTID 152 
#define  WINED3DSPR_LOCALTHREADID 151 
#define  WINED3DSPR_LOCALTHREADINDEX 150 
#define  WINED3DSPR_LOOP 149 
#define  WINED3DSPR_MISCTYPE 148 
#define  WINED3DSPR_OUTCONTROLPOINT 147 
#define  WINED3DSPR_OUTPOINTID 146 
#define  WINED3DSPR_PATCHCONST 145 
#define  WINED3DSPR_PRIMID 144 
#define  WINED3DSPR_RASTOUT 143 
#define  WINED3DSPR_SAMPLEMASK 142 
#define  WINED3DSPR_SAMPLER 141 
#define  WINED3DSPR_TEMP 140 
#define  WINED3DSPR_TESSCOORD 139 
#define  WINED3DSPR_TEXCRDOUT 138 
#define  WINED3DSPR_TEXTURE 137 
#define  WINED3DSPR_THREADGROUPID 136 
#define  WINED3DSPR_THREADID 135 
 int /*<<< orphan*/  WINED3DSP_WRITEMASK_0 ; 
#define  WINED3D_DATA_FLOAT 134 
#define  WINED3D_DATA_INT 133 
#define  WINED3D_DATA_RESOURCE 132 
#define  WINED3D_DATA_SAMPLER 131 
#define  WINED3D_DATA_UINT 130 
#define  WINED3D_IMMCONST_SCALAR 129 
#define  WINED3D_IMMCONST_VEC4 128 
 int /*<<< orphan*/  WINED3D_SHADER_TYPE_DOMAIN ; 
 int /*<<< orphan*/  WINED3D_SHADER_TYPE_GEOMETRY ; 
 int /*<<< orphan*/  WINED3D_SHADER_TYPE_HULL ; 
 int /*<<< orphan*/  WINED3D_SHADER_TYPE_PIXEL ; 
 int /*<<< orphan*/  WINED3D_SHADER_TYPE_VERTEX ; 
 int /*<<< orphan*/  needs_legacy_glsl_syntax (struct wined3d_gl_info const*) ; 
 int /*<<< orphan*/  shader_constant_is_local (struct wined3d_shader const*,int) ; 
 int /*<<< orphan*/  shader_glsl_add_src_param (struct wined3d_shader_instruction const*,scalar_t__,int /*<<< orphan*/ ,struct glsl_src_param*) ; 
 int /*<<< orphan*/  shader_glsl_fixup_scalar_register_variable (char*,char*,struct wined3d_gl_info const*) ; 
 char* shader_glsl_get_prefix (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 unsigned int vec4_varyings (int,struct wined3d_gl_info const*) ; 
 int /*<<< orphan*/  wined3d_ftoa (float const,char*) ; 
 TYPE_10__ wined3d_settings ; 

__attribute__((used)) static void shader_glsl_get_register_name(const struct wined3d_shader_register *reg,
        enum wined3d_data_type data_type, char *register_name, BOOL *is_color,
        const struct wined3d_shader_instruction *ins)
{
    /* oPos, oFog and oPts in D3D */
    static const char * const hwrastout_reg_names[] = {"vs_out[10]", "vs_out[11].x", "vs_out[11].y"};

    const struct wined3d_shader *shader = ins->ctx->shader;
    const struct wined3d_shader_reg_maps *reg_maps = ins->ctx->reg_maps;
    const struct wined3d_shader_version *version = &reg_maps->shader_version;
    const struct wined3d_gl_info *gl_info = ins->ctx->gl_info;
    const char *prefix = shader_glsl_get_prefix(version->type);
    struct glsl_src_param rel_param0, rel_param1;
    char imm_str[4][17];

    if (reg->idx[0].offset != ~0U && reg->idx[0].rel_addr)
        shader_glsl_add_src_param(ins, reg->idx[0].rel_addr, WINED3DSP_WRITEMASK_0, &rel_param0);
    if (reg->idx[1].offset != ~0U && reg->idx[1].rel_addr)
        shader_glsl_add_src_param(ins, reg->idx[1].rel_addr, WINED3DSP_WRITEMASK_0, &rel_param1);
    *is_color = FALSE;

    switch (reg->type)
    {
        case WINED3DSPR_TEMP:
            sprintf(register_name, "R%u", reg->idx[0].offset);
            break;

        case WINED3DSPR_INPUT:
        case WINED3DSPR_INCONTROLPOINT:
            if (version->type == WINED3D_SHADER_TYPE_VERTEX)
            {
                struct shader_glsl_ctx_priv *priv = ins->ctx->backend_data;

                if (reg->idx[0].rel_addr)
                    FIXME("VS3 input registers relative addressing.\n");
                if (priv->cur_vs_args->swizzle_map & (1u << reg->idx[0].offset))
                    *is_color = TRUE;
                if (reg->idx[0].rel_addr)
                {
                    sprintf(register_name, "%s_in[%s + %u]",
                            prefix, rel_param0.param_str, reg->idx[0].offset);
                }
                else
                {
                    sprintf(register_name, "%s_in%u", prefix, reg->idx[0].offset);
                }
                break;
            }

            if (version->type == WINED3D_SHADER_TYPE_HULL
                    || version->type == WINED3D_SHADER_TYPE_DOMAIN
                    || version->type == WINED3D_SHADER_TYPE_GEOMETRY)
            {
                if (reg->idx[0].rel_addr)
                {
                    if (reg->idx[1].rel_addr)
                        sprintf(register_name, "shader_in[%s + %u].reg[%s + %u]",
                                rel_param0.param_str, reg->idx[0].offset,
                                rel_param1.param_str, reg->idx[1].offset);
                    else
                        sprintf(register_name, "shader_in[%s + %u].reg[%u]",
                                rel_param0.param_str, reg->idx[0].offset,
                                reg->idx[1].offset);
                }
                else if (reg->idx[1].rel_addr)
                    sprintf(register_name, "shader_in[%u].reg[%s + %u]", reg->idx[0].offset,
                            rel_param1.param_str, reg->idx[1].offset);
                else
                    sprintf(register_name, "shader_in[%u].reg[%u]",
                            reg->idx[0].offset, reg->idx[1].offset);
                break;
            }

            /* pixel shaders >= 3.0 */
            if (version->major >= 3)
            {
                DWORD idx = shader->u.ps.input_reg_map[reg->idx[0].offset];
                unsigned int in_count = vec4_varyings(version->major, gl_info);

                if (reg->idx[0].rel_addr)
                {
                    /* Removing a + 0 would be an obvious optimization, but
                     * OS X doesn't see the NOP operation there. */
                    if (idx)
                    {
                        if (needs_legacy_glsl_syntax(gl_info)
                                && shader->u.ps.declared_in_count > in_count)
                        {
                            sprintf(register_name,
                                    "((%s + %u) > %u ? (%s + %u) > %u ? gl_SecondaryColor : gl_Color : %s_in[%s + %u])",
                                    rel_param0.param_str, idx, in_count - 1, rel_param0.param_str, idx, in_count,
                                    prefix, rel_param0.param_str, idx);
                        }
                        else
                        {
                            sprintf(register_name, "%s_in[%s + %u]", prefix, rel_param0.param_str, idx);
                        }
                    }
                    else
                    {
                        if (needs_legacy_glsl_syntax(gl_info)
                                && shader->u.ps.declared_in_count > in_count)
                        {
                            sprintf(register_name, "((%s) > %u ? (%s) > %u ? gl_SecondaryColor : gl_Color : %s_in[%s])",
                                    rel_param0.param_str, in_count - 1, rel_param0.param_str, in_count,
                                    prefix, rel_param0.param_str);
                        }
                        else
                        {
                            sprintf(register_name, "%s_in[%s]", prefix, rel_param0.param_str);
                        }
                    }
                }
                else
                {
                    if (idx == in_count) sprintf(register_name, "gl_Color");
                    else if (idx == in_count + 1) sprintf(register_name, "gl_SecondaryColor");
                    else sprintf(register_name, "%s_in[%u]", prefix, idx);
                }
            }
            else
            {
                if (!reg->idx[0].offset)
                    strcpy(register_name, "ffp_varying_diffuse");
                else
                    strcpy(register_name, "ffp_varying_specular");
                break;
            }
            break;

        case WINED3DSPR_CONST:
            {
                /* Relative addressing */
                if (reg->idx[0].rel_addr)
                {
                    if (wined3d_settings.check_float_constants)
                        sprintf(register_name, "(%s + %u >= 0 && %s + %u < %u ? %s_c[%s + %u] : vec4(0.0))",
                                rel_param0.param_str, reg->idx[0].offset,
                                rel_param0.param_str, reg->idx[0].offset, shader->limits->constant_float,
                                prefix, rel_param0.param_str, reg->idx[0].offset);
                    else if (reg->idx[0].offset)
                        sprintf(register_name, "%s_c[%s + %u]", prefix, rel_param0.param_str, reg->idx[0].offset);
                    else
                        sprintf(register_name, "%s_c[%s]", prefix, rel_param0.param_str);
                }
                else
                {
                    if (shader_constant_is_local(shader, reg->idx[0].offset))
                        sprintf(register_name, "%s_lc%u", prefix, reg->idx[0].offset);
                    else
                        sprintf(register_name, "%s_c[%u]", prefix, reg->idx[0].offset);
                }
            }
            break;

        case WINED3DSPR_CONSTINT:
            sprintf(register_name, "%s_i[%u]", prefix, reg->idx[0].offset);
            break;

        case WINED3DSPR_CONSTBOOL:
            sprintf(register_name, "%s_b[%u]", prefix, reg->idx[0].offset);
            break;

        case WINED3DSPR_TEXTURE: /* case WINED3DSPR_ADDR: */
            if (version->type == WINED3D_SHADER_TYPE_PIXEL)
                sprintf(register_name, "T%u", reg->idx[0].offset);
            else
                sprintf(register_name, "A%u", reg->idx[0].offset);
            break;

        case WINED3DSPR_LOOP:
            sprintf(register_name, "aL%u", ins->ctx->state->current_loop_reg - 1);
            break;

        case WINED3DSPR_SAMPLER:
            sprintf(register_name, "%s_sampler%u", prefix, reg->idx[0].offset);
            break;

        case WINED3DSPR_COLOROUT:
            /* FIXME: should check dual_buffers when dual blending is enabled */
            if (reg->idx[0].offset >= gl_info->limits.buffers)
                WARN("Write to render target %u, only %d supported.\n",
                        reg->idx[0].offset, gl_info->limits.buffers);

            sprintf(register_name, needs_legacy_glsl_syntax(gl_info) ? "gl_FragData[%u]" : "ps_out%u",
                    reg->idx[0].offset);
            break;

        case WINED3DSPR_RASTOUT:
            sprintf(register_name, "%s", hwrastout_reg_names[reg->idx[0].offset]);
            break;

        case WINED3DSPR_DEPTHOUT:
        case WINED3DSPR_DEPTHOUTGE:
        case WINED3DSPR_DEPTHOUTLE:
            sprintf(register_name, "gl_FragDepth");
            break;

        case WINED3DSPR_ATTROUT:
            if (!reg->idx[0].offset)
                sprintf(register_name, "%s_out[8]", prefix);
            else
                sprintf(register_name, "%s_out[9]", prefix);
            break;

        case WINED3DSPR_TEXCRDOUT:
            /* Vertex shaders >= 3.0: WINED3DSPR_OUTPUT */
            if (reg->idx[0].rel_addr)
                sprintf(register_name, "%s_out[%s + %u]",
                        prefix, rel_param0.param_str, reg->idx[0].offset);
            else
                sprintf(register_name, "%s_out[%u]", prefix, reg->idx[0].offset);
            break;

        case WINED3DSPR_MISCTYPE:
            if (!reg->idx[0].offset)
            {
                /* vPos */
                sprintf(register_name, "vpos");
            }
            else if (reg->idx[0].offset == 1)
            {
                /* Note that gl_FrontFacing is a bool, while vFace is
                 * a float for which the sign determines front/back */
                sprintf(register_name, "(gl_FrontFacing ? 1.0 : -1.0)");
            }
            else
            {
                FIXME("Unhandled misctype register %u.\n", reg->idx[0].offset);
                sprintf(register_name, "unrecognized_register");
            }
            break;

        case WINED3DSPR_IMMCONST:
            switch (reg->immconst_type)
            {
                case WINED3D_IMMCONST_SCALAR:
                    switch (data_type)
                    {
                        case WINED3D_DATA_FLOAT:
                            if (gl_info->supported[ARB_SHADER_BIT_ENCODING])
                                sprintf(register_name, "uintBitsToFloat(%#xu)", reg->u.immconst_data[0]);
                            else
                                wined3d_ftoa(*(const float *)reg->u.immconst_data, register_name);
                            break;
                        case WINED3D_DATA_INT:
                            sprintf(register_name, "%#x", reg->u.immconst_data[0]);
                            break;
                        case WINED3D_DATA_RESOURCE:
                        case WINED3D_DATA_SAMPLER:
                        case WINED3D_DATA_UINT:
                            sprintf(register_name, "%#xu", reg->u.immconst_data[0]);
                            break;
                        default:
                            sprintf(register_name, "<unhandled data type %#x>", data_type);
                            break;
                    }
                    break;

                case WINED3D_IMMCONST_VEC4:
                    switch (data_type)
                    {
                        case WINED3D_DATA_FLOAT:
                            if (gl_info->supported[ARB_SHADER_BIT_ENCODING])
                            {
                                sprintf(register_name, "uintBitsToFloat(uvec4(%#xu, %#xu, %#xu, %#xu))",
                                        reg->u.immconst_data[0], reg->u.immconst_data[1],
                                        reg->u.immconst_data[2], reg->u.immconst_data[3]);
                            }
                            else
                            {
                                wined3d_ftoa(*(const float *)&reg->u.immconst_data[0], imm_str[0]);
                                wined3d_ftoa(*(const float *)&reg->u.immconst_data[1], imm_str[1]);
                                wined3d_ftoa(*(const float *)&reg->u.immconst_data[2], imm_str[2]);
                                wined3d_ftoa(*(const float *)&reg->u.immconst_data[3], imm_str[3]);
                                sprintf(register_name, "vec4(%s, %s, %s, %s)",
                                        imm_str[0], imm_str[1], imm_str[2], imm_str[3]);
                            }
                            break;
                        case WINED3D_DATA_INT:
                            sprintf(register_name, "ivec4(%#x, %#x, %#x, %#x)",
                                    reg->u.immconst_data[0], reg->u.immconst_data[1],
                                    reg->u.immconst_data[2], reg->u.immconst_data[3]);
                            break;
                        case WINED3D_DATA_RESOURCE:
                        case WINED3D_DATA_SAMPLER:
                        case WINED3D_DATA_UINT:
                            sprintf(register_name, "uvec4(%#xu, %#xu, %#xu, %#xu)",
                                    reg->u.immconst_data[0], reg->u.immconst_data[1],
                                    reg->u.immconst_data[2], reg->u.immconst_data[3]);
                            break;
                        default:
                            sprintf(register_name, "<unhandled data type %#x>", data_type);
                            break;
                    }
                    break;

                default:
                    FIXME("Unhandled immconst type %#x\n", reg->immconst_type);
                    sprintf(register_name, "<unhandled_immconst_type %#x>", reg->immconst_type);
            }
            break;

        case WINED3DSPR_CONSTBUFFER:
            if (reg->idx[1].rel_addr)
                sprintf(register_name, "%s_cb%u[%s + %u]",
                        prefix, reg->idx[0].offset, rel_param1.param_str, reg->idx[1].offset);
            else
                sprintf(register_name, "%s_cb%u[%u]", prefix, reg->idx[0].offset, reg->idx[1].offset);
            break;

        case WINED3DSPR_IMMCONSTBUFFER:
            if (reg->idx[0].rel_addr)
                sprintf(register_name, "%s_icb[%s + %u]", prefix, rel_param0.param_str, reg->idx[0].offset);
            else
                sprintf(register_name, "%s_icb[%u]", prefix, reg->idx[0].offset);
            break;

        case WINED3DSPR_PRIMID:
            if (version->type == WINED3D_SHADER_TYPE_GEOMETRY)
                sprintf(register_name, "gl_PrimitiveIDIn");
            else
                sprintf(register_name, "gl_PrimitiveID");
            break;

        case WINED3DSPR_IDXTEMP:
            if (reg->idx[1].rel_addr)
                sprintf(register_name, "X%u[%s + %u]", reg->idx[0].offset, rel_param1.param_str, reg->idx[1].offset);
            else
                sprintf(register_name, "X%u[%u]", reg->idx[0].offset, reg->idx[1].offset);
            break;

        case WINED3DSPR_LOCALTHREADINDEX:
            shader_glsl_fixup_scalar_register_variable(register_name,
                    "int(gl_LocalInvocationIndex)", gl_info);
            break;

        case WINED3DSPR_GSINSTID:
        case WINED3DSPR_OUTPOINTID:
            shader_glsl_fixup_scalar_register_variable(register_name,
                    "gl_InvocationID", gl_info);
            break;

        case WINED3DSPR_THREADID:
            sprintf(register_name, "ivec3(gl_GlobalInvocationID)");
            break;

        case WINED3DSPR_THREADGROUPID:
            sprintf(register_name, "ivec3(gl_WorkGroupID)");
            break;

        case WINED3DSPR_LOCALTHREADID:
            sprintf(register_name, "ivec3(gl_LocalInvocationID)");
            break;

        case WINED3DSPR_FORKINSTID:
        case WINED3DSPR_JOININSTID:
            shader_glsl_fixup_scalar_register_variable(register_name,
                    "phase_instance_id", gl_info);
            break;

        case WINED3DSPR_TESSCOORD:
            sprintf(register_name, "gl_TessCoord");
            break;

        case WINED3DSPR_OUTCONTROLPOINT:
            if (reg->idx[0].rel_addr)
            {
                if (reg->idx[1].rel_addr)
                    sprintf(register_name, "shader_out[%s + %u].reg[%s + %u]",
                            rel_param0.param_str, reg->idx[0].offset,
                            rel_param1.param_str, reg->idx[1].offset);
                else
                    sprintf(register_name, "shader_out[%s + %u].reg[%u]",
                            rel_param0.param_str, reg->idx[0].offset,
                            reg->idx[1].offset);
            }
            else if (reg->idx[1].rel_addr)
            {
                sprintf(register_name, "shader_out[%u].reg[%s + %u]",
                        reg->idx[0].offset, rel_param1.param_str,
                        reg->idx[1].offset);
            }
            else
            {
                sprintf(register_name, "shader_out[%u].reg[%u]",
                        reg->idx[0].offset, reg->idx[1].offset);
            }
            break;

        case WINED3DSPR_PATCHCONST:
            if (version->type == WINED3D_SHADER_TYPE_HULL)
                sprintf(register_name, "hs_out[%u]", reg->idx[0].offset);
            else
                sprintf(register_name, "vpc[%u]", reg->idx[0].offset);
            break;

        case WINED3DSPR_SAMPLEMASK:
            sprintf(register_name, "sample_mask");
            break;

        default:
            FIXME("Unhandled register type %#x.\n", reg->type);
            sprintf(register_name, "unrecognized_register");
            break;
    }
}