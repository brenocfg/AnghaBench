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
struct wined3d_gl_info {int quirks; } ;
struct ffp_frag_settings {int fog; scalar_t__ sRGB_write; TYPE_1__* op; scalar_t__ color_key_enabled; scalar_t__ emul_clipplanes; } ;
struct color_fixup_masks {int dummy; } ;
struct TYPE_2__ {int cop; int carg0; int carg1; int carg2; int aop; int aarg0; int aarg1; int aarg2; scalar_t__ projected; scalar_t__ tmp_dst; int /*<<< orphan*/  color_fixup; int /*<<< orphan*/  tex_type; } ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  int DWORD ;
typedef  int BYTE ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ARB_FFP_CONST_BUMPMAT (unsigned int) ; 
 int /*<<< orphan*/  ARB_FFP_CONST_COLOR_KEY_HIGH ; 
 int /*<<< orphan*/  ARB_FFP_CONST_COLOR_KEY_LOW ; 
 int /*<<< orphan*/  ARB_FFP_CONST_CONSTANT (unsigned int) ; 
 int /*<<< orphan*/  ARB_FFP_CONST_LUMINANCE (unsigned int) ; 
 int /*<<< orphan*/  ARB_FFP_CONST_SPECULAR_ENABLE ; 
 int /*<<< orphan*/  ARB_FFP_CONST_TFACTOR ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int FALSE ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_FRAGMENT_PROGRAM_ARB ; 
 unsigned int MAX_TEXTURES ; 
 int TRUE ; 
 int /*<<< orphan*/  WINED3DSP_WRITEMASK_ALL ; 
 int WINED3DTA_CONSTANT ; 
 int WINED3DTA_SELECTMASK ; 
 int WINED3DTA_TEMP ; 
 int WINED3DTA_TEXTURE ; 
 int WINED3DTA_TFACTOR ; 
#define  WINED3D_FFP_PS_FOG_EXP 136 
#define  WINED3D_FFP_PS_FOG_EXP2 135 
#define  WINED3D_FFP_PS_FOG_LINEAR 134 
#define  WINED3D_FFP_PS_FOG_OFF 133 
 scalar_t__ WINED3D_PROJECTION_COUNT3 ; 
 scalar_t__ WINED3D_PROJECTION_COUNT4 ; 
 scalar_t__ WINED3D_PROJECTION_NONE ; 
 int WINED3D_QUIRK_BROKEN_ARB_FOG ; 
#define  WINED3D_TOP_BLEND_FACTOR_ALPHA 132 
#define  WINED3D_TOP_BLEND_TEXTURE_ALPHA 131 
#define  WINED3D_TOP_BLEND_TEXTURE_ALPHA_PM 130 
#define  WINED3D_TOP_BUMPENVMAP 129 
#define  WINED3D_TOP_BUMPENVMAP_LUMINANCE 128 
 int WINED3D_TOP_DISABLE ; 
 int WINED3D_TOP_SELECT_ARG1 ; 
 int WINED3D_TOP_SELECT_ARG2 ; 
 int /*<<< orphan*/  arbfp_add_linear_fog (struct wined3d_string_buffer*,char*,char*) ; 
 int /*<<< orphan*/  arbfp_add_sRGB_correction (struct wined3d_string_buffer*,char*,char*,char*,char*,char*,int) ; 
 char* arbfp_texture_target (int /*<<< orphan*/ ) ; 
 struct color_fixup_masks calc_color_correction (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_color_correction (struct wined3d_string_buffer*,char*,char*,char*,char*,int /*<<< orphan*/ ,struct color_fixup_masks) ; 
 int /*<<< orphan*/  gen_ffp_instr (struct wined3d_string_buffer*,unsigned int,int,int,scalar_t__,int,int,int,int) ; 
 int /*<<< orphan*/  glBindProgramARB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glGenProgramsARB (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,...) ; 
 int /*<<< orphan*/  shader_arb_append_imm_vec4 (struct wined3d_string_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_arb_compile (struct wined3d_gl_info const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 
 int /*<<< orphan*/  string_buffer_free (struct wined3d_string_buffer*) ; 
 int /*<<< orphan*/  string_buffer_init (struct wined3d_string_buffer*) ; 
 int /*<<< orphan*/  wined3d_srgb_const0 ; 
 int /*<<< orphan*/  wined3d_srgb_const1 ; 

__attribute__((used)) static GLuint gen_arbfp_ffp_shader(const struct ffp_frag_settings *settings, const struct wined3d_gl_info *gl_info)
{
    BYTE tex_read = 0, bump_used = 0, luminance_used = 0, constant_used = 0;
    BOOL tempreg_used = FALSE, tfactor_used = FALSE;
    unsigned int stage, lowest_disabled_stage;
    struct wined3d_string_buffer buffer;
    struct color_fixup_masks masks;
    BOOL custom_linear_fog = FALSE;
    const char *textype, *instr;
    DWORD arg0, arg1, arg2;
    char colorcor_dst[8];
    BOOL op_equal;
    GLuint ret;

    if (!string_buffer_init(&buffer))
    {
        ERR("Failed to initialize shader buffer.\n");
        return 0;
    }

    shader_addline(&buffer, "!!ARBfp1.0\n");

    if (settings->color_key_enabled)
    {
        shader_addline(&buffer, "PARAM color_key_low = program.env[%u];\n", ARB_FFP_CONST_COLOR_KEY_LOW);
        shader_addline(&buffer, "PARAM color_key_high = program.env[%u];\n", ARB_FFP_CONST_COLOR_KEY_HIGH);
        tex_read |= 1;
    }

    /* Find out which textures are read */
    for (stage = 0; stage < MAX_TEXTURES; ++stage)
    {
        if (settings->op[stage].cop == WINED3D_TOP_DISABLE)
            break;

        arg0 = settings->op[stage].carg0 & WINED3DTA_SELECTMASK;
        arg1 = settings->op[stage].carg1 & WINED3DTA_SELECTMASK;
        arg2 = settings->op[stage].carg2 & WINED3DTA_SELECTMASK;

        if (arg0 == WINED3DTA_TEXTURE || arg1 == WINED3DTA_TEXTURE || arg2 == WINED3DTA_TEXTURE)
            tex_read |= 1u << stage;
        if (settings->op[stage].tmp_dst)
            tempreg_used = TRUE;
        if (arg0 == WINED3DTA_TEMP || arg1 == WINED3DTA_TEMP || arg2 == WINED3DTA_TEMP)
            tempreg_used = TRUE;
        if (arg0 == WINED3DTA_TFACTOR || arg1 == WINED3DTA_TFACTOR || arg2 == WINED3DTA_TFACTOR)
            tfactor_used = TRUE;
        if (arg0 == WINED3DTA_CONSTANT || arg1 == WINED3DTA_CONSTANT || arg2 == WINED3DTA_CONSTANT)
            constant_used |= 1u << stage;

        switch (settings->op[stage].cop)
        {
            case WINED3D_TOP_BUMPENVMAP_LUMINANCE:
                luminance_used |= 1u << stage;
                /* fall through */
            case WINED3D_TOP_BUMPENVMAP:
                bump_used |= 1u << stage;
                /* fall through */
            case WINED3D_TOP_BLEND_TEXTURE_ALPHA:
            case WINED3D_TOP_BLEND_TEXTURE_ALPHA_PM:
                tex_read |= 1u << stage;
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
            tex_read |= 1u << stage;
        if (arg0 == WINED3DTA_TEMP || arg1 == WINED3DTA_TEMP || arg2 == WINED3DTA_TEMP)
            tempreg_used = TRUE;
        if (arg0 == WINED3DTA_TFACTOR || arg1 == WINED3DTA_TFACTOR || arg2 == WINED3DTA_TFACTOR)
            tfactor_used = TRUE;
        if (arg0 == WINED3DTA_CONSTANT || arg1 == WINED3DTA_CONSTANT || arg2 == WINED3DTA_CONSTANT)
            constant_used |= 1u << stage;
    }
    lowest_disabled_stage = stage;

    switch (settings->fog)
    {
        case WINED3D_FFP_PS_FOG_OFF:                                                         break;
        case WINED3D_FFP_PS_FOG_LINEAR:
            if (gl_info->quirks & WINED3D_QUIRK_BROKEN_ARB_FOG)
            {
                custom_linear_fog = TRUE;
                break;
            }
            shader_addline(&buffer, "OPTION ARB_fog_linear;\n");
            break;

        case WINED3D_FFP_PS_FOG_EXP:    shader_addline(&buffer, "OPTION ARB_fog_exp;\n");    break;
        case WINED3D_FFP_PS_FOG_EXP2:   shader_addline(&buffer, "OPTION ARB_fog_exp2;\n");   break;
        default: FIXME("Unexpected fog setting %d\n", settings->fog);
    }

    shader_addline(&buffer, "PARAM const = {1, 2, 4, 0.5};\n");
    shader_addline(&buffer, "TEMP TMP;\n");
    shader_addline(&buffer, "TEMP ret;\n");
    if (tempreg_used || settings->sRGB_write) shader_addline(&buffer, "TEMP tempreg;\n");
    shader_addline(&buffer, "TEMP arg0;\n");
    shader_addline(&buffer, "TEMP arg1;\n");
    shader_addline(&buffer, "TEMP arg2;\n");
    for (stage = 0; stage < MAX_TEXTURES; ++stage)
    {
        if (constant_used & (1u << stage))
            shader_addline(&buffer, "PARAM const%u = program.env[%u];\n", stage, ARB_FFP_CONST_CONSTANT(stage));

        if (!(tex_read & (1u << stage)))
            continue;

        shader_addline(&buffer, "TEMP tex%u;\n", stage);

        if (!(bump_used & (1u << stage)))
            continue;
        shader_addline(&buffer, "PARAM bumpmat%u = program.env[%u];\n", stage, ARB_FFP_CONST_BUMPMAT(stage));

        if (!(luminance_used & (1u << stage)))
            continue;
        shader_addline(&buffer, "PARAM luminance%u = program.env[%u];\n", stage, ARB_FFP_CONST_LUMINANCE(stage));
    }
    if (tfactor_used)
        shader_addline(&buffer, "PARAM tfactor = program.env[%u];\n", ARB_FFP_CONST_TFACTOR);
    shader_addline(&buffer, "PARAM specular_enable = program.env[%u];\n", ARB_FFP_CONST_SPECULAR_ENABLE);

    if (settings->sRGB_write)
    {
        shader_addline(&buffer, "PARAM srgb_consts0 = ");
        shader_arb_append_imm_vec4(&buffer, wined3d_srgb_const0);
        shader_addline(&buffer, ";\n");
        shader_addline(&buffer, "PARAM srgb_consts1 = ");
        shader_arb_append_imm_vec4(&buffer, wined3d_srgb_const1);
        shader_addline(&buffer, ";\n");
    }

    if (lowest_disabled_stage < 7 && settings->emul_clipplanes)
        shader_addline(&buffer, "KIL fragment.texcoord[7];\n");

    if (tempreg_used || settings->sRGB_write)
        shader_addline(&buffer, "MOV tempreg, 0.0;\n");

    /* Generate texture sampling instructions */
    for (stage = 0; stage < MAX_TEXTURES && settings->op[stage].cop != WINED3D_TOP_DISABLE; ++stage)
    {
        if (!(tex_read & (1u << stage)))
            continue;

        textype = arbfp_texture_target(settings->op[stage].tex_type);

        if (settings->op[stage].projected == WINED3D_PROJECTION_NONE)
        {
            instr = "TEX";
        }
        else if (settings->op[stage].projected == WINED3D_PROJECTION_COUNT4
                || settings->op[stage].projected == WINED3D_PROJECTION_COUNT3)
        {
            instr = "TXP";
        }
        else
        {
            FIXME("Unexpected projection mode %d\n", settings->op[stage].projected);
            instr = "TXP";
        }

        if (stage > 0
                && (settings->op[stage - 1].cop == WINED3D_TOP_BUMPENVMAP
                || settings->op[stage - 1].cop == WINED3D_TOP_BUMPENVMAP_LUMINANCE))
        {
            shader_addline(&buffer, "SWZ arg1, bumpmat%u, x, z, 0, 0;\n", stage - 1);
            shader_addline(&buffer, "DP3 ret.x, arg1, tex%u;\n", stage - 1);
            shader_addline(&buffer, "SWZ arg1, bumpmat%u, y, w, 0, 0;\n", stage - 1);
            shader_addline(&buffer, "DP3 ret.y, arg1, tex%u;\n", stage - 1);

            /* With projective textures, texbem only divides the static
             * texture coordinate, not the displacement, so multiply the
             * displacement with the dividing parameter before passing it to
             * TXP. */
            if (settings->op[stage].projected != WINED3D_PROJECTION_NONE)
            {
                if (settings->op[stage].projected == WINED3D_PROJECTION_COUNT4)
                {
                    shader_addline(&buffer, "MOV ret.w, fragment.texcoord[%u].w;\n", stage);
                    shader_addline(&buffer, "MUL ret.xyz, ret, fragment.texcoord[%u].w, fragment.texcoord[%u];\n",
                            stage, stage);
                }
                else
                {
                    shader_addline(&buffer, "MOV ret.w, fragment.texcoord[%u].z;\n", stage);
                    shader_addline(&buffer, "MAD ret.xyz, ret, fragment.texcoord[%u].z, fragment.texcoord[%u];\n",
                            stage, stage);
                }
            }
            else
            {
                shader_addline(&buffer, "ADD ret, ret, fragment.texcoord[%u];\n", stage);
            }

            shader_addline(&buffer, "%s tex%u, ret, texture[%u], %s;\n",
                    instr, stage, stage, textype);
            if (settings->op[stage - 1].cop == WINED3D_TOP_BUMPENVMAP_LUMINANCE)
            {
                shader_addline(&buffer, "MAD_SAT ret.x, tex%u.z, luminance%u.x, luminance%u.y;\n",
                               stage - 1, stage - 1, stage - 1);
                shader_addline(&buffer, "MUL tex%u, tex%u, ret.x;\n", stage, stage);
            }
        }
        else if (settings->op[stage].projected == WINED3D_PROJECTION_COUNT3)
        {
            shader_addline(&buffer, "MOV ret, fragment.texcoord[%u];\n", stage);
            shader_addline(&buffer, "MOV ret.w, ret.z;\n");
            shader_addline(&buffer, "%s tex%u, ret, texture[%u], %s;\n",
                            instr, stage, stage, textype);
        }
        else
        {
            shader_addline(&buffer, "%s tex%u, fragment.texcoord[%u], texture[%u], %s;\n",
                            instr, stage, stage, stage, textype);
        }

        sprintf(colorcor_dst, "tex%u", stage);
        masks = calc_color_correction(settings->op[stage].color_fixup, WINED3DSP_WRITEMASK_ALL);
        gen_color_correction(&buffer, colorcor_dst, colorcor_dst, "const.x", "const.y",
                settings->op[stage].color_fixup, masks);
    }

    if (settings->color_key_enabled)
    {
        shader_addline(&buffer, "SLT TMP, tex0, color_key_low;\n"); /* below low key */
        shader_addline(&buffer, "SGE ret, tex0, color_key_high;\n"); /* above high key */
        shader_addline(&buffer, "ADD TMP, TMP, ret;\n"); /* or */
        shader_addline(&buffer, "DP4 TMP.b, TMP, TMP;\n"); /* on any channel */
        shader_addline(&buffer, "SGE TMP, -TMP.b, 0.0;\n"); /* logical not */
        shader_addline(&buffer, "KIL -TMP;\n"); /* discard if true */
    }

    shader_addline(&buffer, "MOV ret, fragment.color.primary;\n");

    /* Generate the main shader */
    for (stage = 0; stage < MAX_TEXTURES; ++stage)
    {
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
            op_equal = settings->op[stage].aop   == settings->op[stage].cop
                    && settings->op[stage].carg0 == settings->op[stage].aarg0
                    && settings->op[stage].carg1 == settings->op[stage].aarg1
                    && settings->op[stage].carg2 == settings->op[stage].aarg2;

        if (settings->op[stage].aop == WINED3D_TOP_DISABLE)
        {
            gen_ffp_instr(&buffer, stage, TRUE, FALSE, settings->op[stage].tmp_dst,
                          settings->op[stage].cop, settings->op[stage].carg0,
                          settings->op[stage].carg1, settings->op[stage].carg2);
        }
        else if (op_equal)
        {
            gen_ffp_instr(&buffer, stage, TRUE, TRUE, settings->op[stage].tmp_dst,
                          settings->op[stage].cop, settings->op[stage].carg0,
                          settings->op[stage].carg1, settings->op[stage].carg2);
        }
        else if (settings->op[stage].cop != WINED3D_TOP_BUMPENVMAP
                && settings->op[stage].cop != WINED3D_TOP_BUMPENVMAP_LUMINANCE)
        {
            gen_ffp_instr(&buffer, stage, TRUE, FALSE, settings->op[stage].tmp_dst,
                          settings->op[stage].cop, settings->op[stage].carg0,
                          settings->op[stage].carg1, settings->op[stage].carg2);
            gen_ffp_instr(&buffer, stage, FALSE, TRUE, settings->op[stage].tmp_dst,
                          settings->op[stage].aop, settings->op[stage].aarg0,
                          settings->op[stage].aarg1, settings->op[stage].aarg2);
        }
    }

    if (settings->sRGB_write || custom_linear_fog)
    {
        shader_addline(&buffer, "MAD ret, fragment.color.secondary, specular_enable, ret;\n");
        if (settings->sRGB_write)
            arbfp_add_sRGB_correction(&buffer, "ret", "arg0", "arg1", "arg2", "tempreg", FALSE);
        if (custom_linear_fog)
            arbfp_add_linear_fog(&buffer, "ret", "arg0");
        shader_addline(&buffer, "MOV result.color, ret;\n");
    }
    else
    {
        shader_addline(&buffer, "MAD result.color, fragment.color.secondary, specular_enable, ret;\n");
    }

    /* Footer */
    shader_addline(&buffer, "END\n");

    /* Generate the shader */
    GL_EXTCALL(glGenProgramsARB(1, &ret));
    GL_EXTCALL(glBindProgramARB(GL_FRAGMENT_PROGRAM_ARB, ret));
    shader_arb_compile(gl_info, GL_FRAGMENT_PROGRAM_ARB, buffer.buffer);

    string_buffer_free(&buffer);
    return ret;
}