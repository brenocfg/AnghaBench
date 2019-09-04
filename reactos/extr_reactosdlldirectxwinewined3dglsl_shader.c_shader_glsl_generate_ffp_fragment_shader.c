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
struct wined3d_string_buffer {int /*<<< orphan*/  buffer; } ;
typedef  struct wined3d_gl_info {scalar_t__* supported; } const wined3d_gl_info ;
struct wined3d_context {struct wined3d_gl_info const* gl_info; } ;
struct shader_glsl_priv {int /*<<< orphan*/  string_buffers; struct wined3d_string_buffer shader_buffer; } ;
struct ffp_frag_settings {int alpha_test_func; int flatshading; unsigned int texcoords_initialized; int /*<<< orphan*/  fog; scalar_t__ sRGB_write; TYPE_1__* op; scalar_t__ color_key_enabled; scalar_t__ emul_clipplanes; scalar_t__ pointsprite; } ;
typedef  enum wined3d_cmp_func { ____Placeholder_wined3d_cmp_func } wined3d_cmp_func ;
typedef  int UINT ;
struct TYPE_2__ {int cop; int carg0; int carg1; int carg2; int aop; int aarg0; int aarg1; int aarg2; int tex_type; scalar_t__ projected; scalar_t__ tmp_dst; int /*<<< orphan*/  color_fixup; } ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  int DWORD ;
typedef  unsigned int BYTE ;
typedef  int BOOL ;

/* Variables and functions */
 size_t ARB_SHADING_LANGUAGE_420PACK ; 
 size_t ARB_TEXTURE_RECTANGLE ; 
 int FALSE ; 
 int /*<<< orphan*/  FIXME (char*,scalar_t__) ; 
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_FRAGMENT_SHADER ; 
 unsigned int MAX_TEXTURES ; 
 int TRUE ; 
 int /*<<< orphan*/  WINED3DSP_WRITEMASK_ALL ; 
 int WINED3DTA_CONSTANT ; 
 int WINED3DTA_SELECTMASK ; 
 int WINED3DTA_TEMP ; 
 int WINED3DTA_TEXTURE ; 
 int WINED3DTA_TFACTOR ; 
 int WINED3D_CMP_ALWAYS ; 
 int /*<<< orphan*/  WINED3D_FFP_PS_FOG_OFF ; 
#define  WINED3D_GL_RES_TYPE_TEX_1D 137 
#define  WINED3D_GL_RES_TYPE_TEX_2D 136 
#define  WINED3D_GL_RES_TYPE_TEX_3D 135 
#define  WINED3D_GL_RES_TYPE_TEX_CUBE 134 
#define  WINED3D_GL_RES_TYPE_TEX_RECT 133 
 scalar_t__ WINED3D_PROJECTION_COUNT3 ; 
 scalar_t__ WINED3D_PROJECTION_COUNT4 ; 
 scalar_t__ WINED3D_PROJECTION_NONE ; 
#define  WINED3D_TOP_BLEND_FACTOR_ALPHA 132 
#define  WINED3D_TOP_BLEND_TEXTURE_ALPHA 131 
#define  WINED3D_TOP_BLEND_TEXTURE_ALPHA_PM 130 
#define  WINED3D_TOP_BUMPENVMAP 129 
#define  WINED3D_TOP_BUMPENVMAP_LUMINANCE 128 
 int WINED3D_TOP_DISABLE ; 
 int WINED3D_TOP_SELECT_ARG1 ; 
 int WINED3D_TOP_SELECT_ARG2 ; 
 int /*<<< orphan*/  declare_in_varying (struct wined3d_gl_info const*,struct wined3d_string_buffer*,int,char*,...) ; 
 int /*<<< orphan*/  glCreateShader (int /*<<< orphan*/ ) ; 
 int needs_legacy_glsl_syntax (struct wined3d_gl_info const*) ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,...) ; 
 int /*<<< orphan*/  shader_glsl_add_version_declaration (struct wined3d_string_buffer*,struct wined3d_gl_info const*) ; 
 int /*<<< orphan*/  shader_glsl_append_imm_vec4 (struct wined3d_string_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_glsl_append_sampler_binding_qualifier (struct wined3d_string_buffer*,struct wined3d_context const*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  shader_glsl_color_correction_ext (struct wined3d_string_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_glsl_compile (struct wined3d_gl_info const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_glsl_ffp_fragment_op (struct wined3d_string_buffer*,unsigned int,int,int,scalar_t__,int,int,int,int) ; 
 int /*<<< orphan*/  shader_glsl_generate_alpha_test (struct wined3d_string_buffer*,struct wined3d_gl_info const*,int) ; 
 int /*<<< orphan*/  shader_glsl_generate_fog_code (struct wined3d_string_buffer*,struct wined3d_gl_info const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_glsl_generate_srgb_write_correction (struct wined3d_string_buffer*,struct wined3d_gl_info const*) ; 
 scalar_t__ shader_glsl_use_explicit_attrib_location (struct wined3d_gl_info const*) ; 
 scalar_t__ shader_glsl_use_layout_binding_qualifier (struct wined3d_gl_info const*) ; 
 int /*<<< orphan*/  string_buffer_clear (struct wined3d_string_buffer*) ; 
 struct wined3d_string_buffer* string_buffer_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  string_buffer_release (int /*<<< orphan*/ *,struct wined3d_string_buffer*) ; 
 int /*<<< orphan*/  string_buffer_sprintf (struct wined3d_string_buffer*,char*,unsigned int) ; 
 int /*<<< orphan*/  wined3d_srgb_const0 ; 
 int /*<<< orphan*/  wined3d_srgb_const1 ; 

__attribute__((used)) static GLuint shader_glsl_generate_ffp_fragment_shader(struct shader_glsl_priv *priv,
        const struct ffp_frag_settings *settings, const struct wined3d_context *context)
{
    const char *output = needs_legacy_glsl_syntax(context->gl_info) ? "gl_FragData[0]" : "ps_out0";
    struct wined3d_string_buffer *tex_reg_name = string_buffer_get(&priv->string_buffers);
    enum wined3d_cmp_func alpha_test_func = settings->alpha_test_func + 1;
    struct wined3d_string_buffer *buffer = &priv->shader_buffer;
    BYTE lum_map = 0, bump_map = 0, tex_map = 0, tss_const_map = 0;
    const struct wined3d_gl_info *gl_info = context->gl_info;
    const BOOL legacy_syntax = needs_legacy_glsl_syntax(gl_info);
    BOOL tempreg_used = FALSE, tfactor_used = FALSE;
    UINT lowest_disabled_stage;
    GLuint shader_id;
    DWORD arg0, arg1, arg2;
    unsigned int stage;

    string_buffer_clear(buffer);

    /* Find out which textures are read */
    for (stage = 0; stage < MAX_TEXTURES; ++stage)
    {
        if (settings->op[stage].cop == WINED3D_TOP_DISABLE)
            break;

        arg0 = settings->op[stage].carg0 & WINED3DTA_SELECTMASK;
        arg1 = settings->op[stage].carg1 & WINED3DTA_SELECTMASK;
        arg2 = settings->op[stage].carg2 & WINED3DTA_SELECTMASK;

        if (arg0 == WINED3DTA_TEXTURE || arg1 == WINED3DTA_TEXTURE || arg2 == WINED3DTA_TEXTURE
                || (stage == 0 && settings->color_key_enabled))
            tex_map |= 1u << stage;
        if (arg0 == WINED3DTA_TFACTOR || arg1 == WINED3DTA_TFACTOR || arg2 == WINED3DTA_TFACTOR)
            tfactor_used = TRUE;
        if (arg0 == WINED3DTA_TEMP || arg1 == WINED3DTA_TEMP || arg2 == WINED3DTA_TEMP)
            tempreg_used = TRUE;
        if (settings->op[stage].tmp_dst)
            tempreg_used = TRUE;
        if (arg0 == WINED3DTA_CONSTANT || arg1 == WINED3DTA_CONSTANT || arg2 == WINED3DTA_CONSTANT)
            tss_const_map |= 1u << stage;

        switch (settings->op[stage].cop)
        {
            case WINED3D_TOP_BUMPENVMAP_LUMINANCE:
                lum_map |= 1u << stage;
                /* fall through */
            case WINED3D_TOP_BUMPENVMAP:
                bump_map |= 1u << stage;
                /* fall through */
            case WINED3D_TOP_BLEND_TEXTURE_ALPHA:
            case WINED3D_TOP_BLEND_TEXTURE_ALPHA_PM:
                tex_map |= 1u << stage;
                break;

            case WINED3D_TOP_BLEND_FACTOR_ALPHA:
                tfactor_used = TRUE;
                break;

            default:
                break;
        }

        if (settings->op[stage].aop == WINED3D_TOP_DISABLE)
            continue;

        arg0 = settings->op[stage].aarg0 & WINED3DTA_SELECTMASK;
        arg1 = settings->op[stage].aarg1 & WINED3DTA_SELECTMASK;
        arg2 = settings->op[stage].aarg2 & WINED3DTA_SELECTMASK;

        if (arg0 == WINED3DTA_TEXTURE || arg1 == WINED3DTA_TEXTURE || arg2 == WINED3DTA_TEXTURE)
            tex_map |= 1u << stage;
        if (arg0 == WINED3DTA_TFACTOR || arg1 == WINED3DTA_TFACTOR || arg2 == WINED3DTA_TFACTOR)
            tfactor_used = TRUE;
        if (arg0 == WINED3DTA_TEMP || arg1 == WINED3DTA_TEMP || arg2 == WINED3DTA_TEMP)
            tempreg_used = TRUE;
        if (arg0 == WINED3DTA_CONSTANT || arg1 == WINED3DTA_CONSTANT || arg2 == WINED3DTA_CONSTANT)
            tss_const_map |= 1u << stage;
    }
    lowest_disabled_stage = stage;

    shader_glsl_add_version_declaration(buffer, gl_info);

    if (shader_glsl_use_explicit_attrib_location(gl_info))
        shader_addline(buffer, "#extension GL_ARB_explicit_attrib_location : enable\n");
    if (gl_info->supported[ARB_SHADING_LANGUAGE_420PACK])
        shader_addline(buffer, "#extension GL_ARB_shading_language_420pack : enable\n");
    if (gl_info->supported[ARB_TEXTURE_RECTANGLE])
        shader_addline(buffer, "#extension GL_ARB_texture_rectangle : enable\n");

    if (!needs_legacy_glsl_syntax(gl_info))
    {
        if (shader_glsl_use_explicit_attrib_location(gl_info))
            shader_addline(buffer, "layout(location = 0) ");
        shader_addline(buffer, "out vec4 ps_out0;\n");
    }

    shader_addline(buffer, "vec4 tmp0, tmp1;\n");
    shader_addline(buffer, "vec4 ret;\n");
    if (tempreg_used || settings->sRGB_write)
        shader_addline(buffer, "vec4 temp_reg = vec4(0.0);\n");
    shader_addline(buffer, "vec4 arg0, arg1, arg2;\n");

    for (stage = 0; stage < MAX_TEXTURES; ++stage)
    {
        const char *sampler_type;

        if (tss_const_map & (1u << stage))
            shader_addline(buffer, "uniform vec4 tss_const%u;\n", stage);

        if (!(tex_map & (1u << stage)))
            continue;

        switch (settings->op[stage].tex_type)
        {
            case WINED3D_GL_RES_TYPE_TEX_1D:
                sampler_type = "1D";
                break;
            case WINED3D_GL_RES_TYPE_TEX_2D:
                sampler_type = "2D";
                break;
            case WINED3D_GL_RES_TYPE_TEX_3D:
                sampler_type = "3D";
                break;
            case WINED3D_GL_RES_TYPE_TEX_CUBE:
                sampler_type = "Cube";
                break;
            case WINED3D_GL_RES_TYPE_TEX_RECT:
                sampler_type = "2DRect";
                break;
            default:
                FIXME("Unhandled sampler type %#x.\n", settings->op[stage].tex_type);
                sampler_type = NULL;
                break;
        }
        if (sampler_type)
        {
            if (shader_glsl_use_layout_binding_qualifier(gl_info))
                shader_glsl_append_sampler_binding_qualifier(buffer, context, NULL, stage);
            shader_addline(buffer, "uniform sampler%s ps_sampler%u;\n", sampler_type, stage);
        }

        shader_addline(buffer, "vec4 tex%u;\n", stage);

        if (!(bump_map & (1u << stage)))
            continue;
        shader_addline(buffer, "uniform mat2 bumpenv_mat%u;\n", stage);

        if (!(lum_map & (1u << stage)))
            continue;
        shader_addline(buffer, "uniform float bumpenv_lum_scale%u;\n", stage);
        shader_addline(buffer, "uniform float bumpenv_lum_offset%u;\n", stage);
    }
    if (tfactor_used)
        shader_addline(buffer, "uniform vec4 tex_factor;\n");
    if (settings->color_key_enabled)
        shader_addline(buffer, "uniform vec4 color_key[2];\n");
    shader_addline(buffer, "uniform vec4 specular_enable;\n");

    if (settings->sRGB_write)
    {
        shader_addline(buffer, "const vec4 srgb_const0 = ");
        shader_glsl_append_imm_vec4(buffer, wined3d_srgb_const0);
        shader_addline(buffer, ";\n");
        shader_addline(buffer, "const vec4 srgb_const1 = ");
        shader_glsl_append_imm_vec4(buffer, wined3d_srgb_const1);
        shader_addline(buffer, ";\n");
    }

    shader_addline(buffer, "uniform struct\n{\n");
    shader_addline(buffer, "    vec4 color;\n");
    shader_addline(buffer, "    float density;\n");
    shader_addline(buffer, "    float end;\n");
    shader_addline(buffer, "    float scale;\n");
    shader_addline(buffer, "} ffp_fog;\n");

    if (alpha_test_func != WINED3D_CMP_ALWAYS)
        shader_addline(buffer, "uniform float alpha_test_ref;\n");

    if (legacy_syntax)
    {
        shader_addline(buffer, "vec4 ffp_varying_diffuse;\n");
        shader_addline(buffer, "vec4 ffp_varying_specular;\n");
        shader_addline(buffer, "vec4 ffp_varying_texcoord[%u];\n", MAX_TEXTURES);
        shader_addline(buffer, "vec4 ffp_texcoord[%u];\n", MAX_TEXTURES);
        shader_addline(buffer, "float ffp_varying_fogcoord;\n");
    }
    else
    {
        declare_in_varying(gl_info, buffer, settings->flatshading, "vec4 ffp_varying_diffuse;\n");
        declare_in_varying(gl_info, buffer, settings->flatshading, "vec4 ffp_varying_specular;\n");
        declare_in_varying(gl_info, buffer, FALSE, "vec4 ffp_varying_texcoord[%u];\n", MAX_TEXTURES);
        shader_addline(buffer, "vec4 ffp_texcoord[%u];\n", MAX_TEXTURES);
        declare_in_varying(gl_info, buffer, FALSE, "float ffp_varying_fogcoord;\n");
    }

    shader_addline(buffer, "void main()\n{\n");

    if (legacy_syntax)
    {
        shader_addline(buffer, "ffp_varying_diffuse = gl_Color;\n");
        shader_addline(buffer, "ffp_varying_specular = gl_SecondaryColor;\n");
    }

    for (stage = 0; stage < MAX_TEXTURES; ++stage)
    {
        if (tex_map & (1u << stage))
        {
            if (settings->pointsprite)
                shader_addline(buffer, "ffp_texcoord[%u] = vec4(gl_PointCoord.xy, 0.0, 0.0);\n", stage);
            else if (settings->texcoords_initialized & (1u << stage))
                shader_addline(buffer, "ffp_texcoord[%u] = %s[%u];\n",
                        stage, legacy_syntax ? "gl_TexCoord" : "ffp_varying_texcoord", stage);
            else
                shader_addline(buffer, "ffp_texcoord[%u] = vec4(0.0);\n", stage);
        }
    }

    if (legacy_syntax && settings->fog != WINED3D_FFP_PS_FOG_OFF)
        shader_addline(buffer, "ffp_varying_fogcoord = gl_FogFragCoord;\n");

    if (lowest_disabled_stage < 7 && settings->emul_clipplanes)
        shader_addline(buffer, "if (any(lessThan(ffp_texcoord[7], vec4(0.0)))) discard;\n");

    /* Generate texture sampling instructions */
    for (stage = 0; stage < MAX_TEXTURES && settings->op[stage].cop != WINED3D_TOP_DISABLE; ++stage)
    {
        const char *texture_function, *coord_mask;
        BOOL proj;

        if (!(tex_map & (1u << stage)))
            continue;

        if (settings->op[stage].projected == WINED3D_PROJECTION_NONE)
        {
            proj = FALSE;
        }
        else if (settings->op[stage].projected == WINED3D_PROJECTION_COUNT4
                || settings->op[stage].projected == WINED3D_PROJECTION_COUNT3)
        {
            proj = TRUE;
        }
        else
        {
            FIXME("Unexpected projection mode %d\n", settings->op[stage].projected);
            proj = TRUE;
        }

        if (settings->op[stage].tex_type == WINED3D_GL_RES_TYPE_TEX_CUBE)
            proj = FALSE;

        switch (settings->op[stage].tex_type)
        {
            case WINED3D_GL_RES_TYPE_TEX_1D:
                if (proj)
                {
                    texture_function = "texture1DProj";
                    coord_mask = "xw";
                }
                else
                {
                    texture_function = "texture1D";
                    coord_mask = "x";
                }
                break;
            case WINED3D_GL_RES_TYPE_TEX_2D:
                if (proj)
                {
                    texture_function = "texture2DProj";
                    coord_mask = "xyw";
                }
                else
                {
                    texture_function = "texture2D";
                    coord_mask = "xy";
                }
                break;
            case WINED3D_GL_RES_TYPE_TEX_3D:
                if (proj)
                {
                    texture_function = "texture3DProj";
                    coord_mask = "xyzw";
                }
                else
                {
                    texture_function = "texture3D";
                    coord_mask = "xyz";
                }
                break;
            case WINED3D_GL_RES_TYPE_TEX_CUBE:
                texture_function = "textureCube";
                coord_mask = "xyz";
                break;
            case WINED3D_GL_RES_TYPE_TEX_RECT:
                if (proj)
                {
                    texture_function = "texture2DRectProj";
                    coord_mask = "xyw";
                }
                else
                {
                    texture_function = "texture2DRect";
                    coord_mask = "xy";
                }
                break;
            default:
                FIXME("Unhandled texture type %#x.\n", settings->op[stage].tex_type);
                texture_function = "";
                coord_mask = "xyzw";
                break;
        }
        if (!legacy_syntax)
            texture_function = proj ? "textureProj" : "texture";

        if (stage > 0
                && (settings->op[stage - 1].cop == WINED3D_TOP_BUMPENVMAP
                || settings->op[stage - 1].cop == WINED3D_TOP_BUMPENVMAP_LUMINANCE))
        {
            shader_addline(buffer, "ret.xy = bumpenv_mat%u * tex%u.xy;\n", stage - 1, stage - 1);

            /* With projective textures, texbem only divides the static
             * texture coordinate, not the displacement, so multiply the
             * displacement with the dividing parameter before passing it to
             * TXP. */
            if (settings->op[stage].projected != WINED3D_PROJECTION_NONE)
            {
                if (settings->op[stage].projected == WINED3D_PROJECTION_COUNT4)
                {
                    shader_addline(buffer, "ret.xy = (ret.xy * ffp_texcoord[%u].w) + ffp_texcoord[%u].xy;\n",
                            stage, stage);
                    shader_addline(buffer, "ret.zw = ffp_texcoord[%u].ww;\n", stage);
                }
                else
                {
                    shader_addline(buffer, "ret.xy = (ret.xy * ffp_texcoord[%u].z) + ffp_texcoord[%u].xy;\n",
                            stage, stage);
                    shader_addline(buffer, "ret.zw = ffp_texcoord[%u].zz;\n", stage);
                }
            }
            else
            {
                shader_addline(buffer, "ret = ffp_texcoord[%u] + ret.xyxy;\n", stage);
            }

            shader_addline(buffer, "tex%u = %s(ps_sampler%u, ret.%s);\n",
                    stage, texture_function, stage, coord_mask);

            if (settings->op[stage - 1].cop == WINED3D_TOP_BUMPENVMAP_LUMINANCE)
                shader_addline(buffer, "tex%u *= clamp(tex%u.z * bumpenv_lum_scale%u + bumpenv_lum_offset%u, 0.0, 1.0);\n",
                        stage, stage - 1, stage - 1, stage - 1);
        }
        else if (settings->op[stage].projected == WINED3D_PROJECTION_COUNT3)
        {
            shader_addline(buffer, "tex%u = %s(ps_sampler%u, ffp_texcoord[%u].xyz);\n",
                    stage, texture_function, stage, stage);
        }
        else
        {
            shader_addline(buffer, "tex%u = %s(ps_sampler%u, ffp_texcoord[%u].%s);\n",
                    stage, texture_function, stage, stage, coord_mask);
        }

        string_buffer_sprintf(tex_reg_name, "tex%u", stage);
        shader_glsl_color_correction_ext(buffer, tex_reg_name->buffer, WINED3DSP_WRITEMASK_ALL,
                settings->op[stage].color_fixup);
    }

    if (settings->color_key_enabled)
    {
        shader_addline(buffer, "if (all(greaterThanEqual(tex0, color_key[0])) && all(lessThan(tex0, color_key[1])))\n");
        shader_addline(buffer, "    discard;\n");
    }

    shader_addline(buffer, "ret = ffp_varying_diffuse;\n");

    /* Generate the main shader */
    for (stage = 0; stage < MAX_TEXTURES; ++stage)
    {
        BOOL op_equal;

        if (settings->op[stage].cop == WINED3D_TOP_DISABLE)
            break;

        if (settings->op[stage].cop == WINED3D_TOP_SELECT_ARG1
                && settings->op[stage].aop == WINED3D_TOP_SELECT_ARG1)
            op_equal = settings->op[stage].carg1 == settings->op[stage].aarg1;
        else if (settings->op[stage].cop == WINED3D_TOP_SELECT_ARG1
                && settings->op[stage].aop == WINED3D_TOP_SELECT_ARG2)
            op_equal = settings->op[stage].carg1 == settings->op[stage].aarg2;
        else if (settings->op[stage].cop == WINED3D_TOP_SELECT_ARG2
                && settings->op[stage].aop == WINED3D_TOP_SELECT_ARG1)
            op_equal = settings->op[stage].carg2 == settings->op[stage].aarg1;
        else if (settings->op[stage].cop == WINED3D_TOP_SELECT_ARG2
                && settings->op[stage].aop == WINED3D_TOP_SELECT_ARG2)
            op_equal = settings->op[stage].carg2 == settings->op[stage].aarg2;
        else
            op_equal = settings->op[stage].aop == settings->op[stage].cop
                    && settings->op[stage].carg0 == settings->op[stage].aarg0
                    && settings->op[stage].carg1 == settings->op[stage].aarg1
                    && settings->op[stage].carg2 == settings->op[stage].aarg2;

        if (settings->op[stage].aop == WINED3D_TOP_DISABLE)
        {
            shader_glsl_ffp_fragment_op(buffer, stage, TRUE, FALSE, settings->op[stage].tmp_dst,
                    settings->op[stage].cop, settings->op[stage].carg0,
                    settings->op[stage].carg1, settings->op[stage].carg2);
        }
        else if (op_equal)
        {
            shader_glsl_ffp_fragment_op(buffer, stage, TRUE, TRUE, settings->op[stage].tmp_dst,
                    settings->op[stage].cop, settings->op[stage].carg0,
                    settings->op[stage].carg1, settings->op[stage].carg2);
        }
        else if (settings->op[stage].cop != WINED3D_TOP_BUMPENVMAP
                && settings->op[stage].cop != WINED3D_TOP_BUMPENVMAP_LUMINANCE)
        {
            shader_glsl_ffp_fragment_op(buffer, stage, TRUE, FALSE, settings->op[stage].tmp_dst,
                    settings->op[stage].cop, settings->op[stage].carg0,
                    settings->op[stage].carg1, settings->op[stage].carg2);
            shader_glsl_ffp_fragment_op(buffer, stage, FALSE, TRUE, settings->op[stage].tmp_dst,
                    settings->op[stage].aop, settings->op[stage].aarg0,
                    settings->op[stage].aarg1, settings->op[stage].aarg2);
        }
    }

    shader_addline(buffer, "%s = ffp_varying_specular * specular_enable + ret;\n", output);

    if (settings->sRGB_write)
        shader_glsl_generate_srgb_write_correction(buffer, gl_info);

    shader_glsl_generate_fog_code(buffer, gl_info, settings->fog);

    shader_glsl_generate_alpha_test(buffer, gl_info, alpha_test_func);

    shader_addline(buffer, "}\n");

    shader_id = GL_EXTCALL(glCreateShader(GL_FRAGMENT_SHADER));
    shader_glsl_compile(gl_info, shader_id, buffer->buffer);

    string_buffer_release(&priv->string_buffers, tex_reg_name);
    return shader_id;
}