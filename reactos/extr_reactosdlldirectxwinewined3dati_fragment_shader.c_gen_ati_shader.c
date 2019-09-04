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
struct TYPE_2__ {unsigned int textures; } ;
struct wined3d_gl_info {TYPE_1__ limits; } ;
struct color_fixup_desc {scalar_t__ x_source; scalar_t__ y_source; scalar_t__ y_sign_fixup; scalar_t__ x_sign_fixup; } ;
struct texture_stage_op {int cop; scalar_t__ projected; int aop; int /*<<< orphan*/  aarg2; int /*<<< orphan*/  aarg1; int /*<<< orphan*/  aarg0; struct color_fixup_desc color_fixup; int /*<<< orphan*/  carg2; int /*<<< orphan*/  carg1; int /*<<< orphan*/  carg0; scalar_t__ tmp_dst; } ;
typedef  enum atifs_constant_value { ____Placeholder_atifs_constant_value } atifs_constant_value ;
typedef  unsigned int GLuint ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int ATIFS_CONSTANT_BUMP ; 
 int ATIFS_CONSTANT_STAGE ; 
 int ATIFS_CONSTANT_TFACTOR ; 
 int ATIFS_CONSTANT_UNUSED ; 
 unsigned int ATIFS_CONST_BUMPMAT (unsigned int) ; 
 size_t ATIFS_CONST_TFACTOR ; 
 scalar_t__ CHANNEL_SOURCE_X ; 
 scalar_t__ CHANNEL_SOURCE_Y ; 
 int /*<<< orphan*/  ERR (char*) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FIXME (char*,...) ; 
 unsigned int GL_2X_BIT_ATI ; 
 unsigned int GL_4X_BIT_ATI ; 
 int /*<<< orphan*/  GL_ADD_ATI ; 
 unsigned int GL_ALPHA ; 
 unsigned int GL_BIAS_BIT_ATI ; 
 unsigned int GL_BLUE ; 
 unsigned int GL_COMP_BIT_ATI ; 
 size_t GL_CON_0_ATI ; 
 int /*<<< orphan*/  GL_DOT2_ADD_ATI ; 
 int /*<<< orphan*/  GL_DOT3_ATI ; 
 unsigned int GL_EXTCALL (int /*<<< orphan*/ ) ; 
 unsigned int GL_GREEN ; 
 unsigned int GL_GREEN_BIT_ATI ; 
 int /*<<< orphan*/  GL_LERP_ATI ; 
 int /*<<< orphan*/  GL_MAD_ATI ; 
 int /*<<< orphan*/  GL_MOV_ATI ; 
 int /*<<< orphan*/  GL_MUL_ATI ; 
 unsigned int GL_NONE ; 
 unsigned int GL_PRIMARY_COLOR ; 
 unsigned int GL_RED ; 
 unsigned int GL_RED_BIT_ATI ; 
 unsigned int GL_REG_0_ATI ; 
 unsigned int GL_SATURATE_BIT_ATI ; 
 int /*<<< orphan*/  GL_SUB_ATI ; 
 unsigned int GL_SWIZZLE_STQ_DQ_ATI ; 
 unsigned int GL_SWIZZLE_STR_ATI ; 
 unsigned int GL_SWIZZLE_STR_DR_ATI ; 
 unsigned int GL_TEXTURE0_ARB ; 
 unsigned int MAX_TEXTURES ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WINED3DTA_CURRENT ; 
 int /*<<< orphan*/  WINED3DTA_DIFFUSE ; 
 int /*<<< orphan*/  WINED3DTA_TEXTURE ; 
 int /*<<< orphan*/  WINED3DTA_TFACTOR ; 
 scalar_t__ WINED3D_PROJECTION_COUNT3 ; 
 scalar_t__ WINED3D_PROJECTION_COUNT4 ; 
 scalar_t__ WINED3D_PROJECTION_NONE ; 
#define  WINED3D_TOP_ADD 152 
#define  WINED3D_TOP_ADD_SIGNED 151 
#define  WINED3D_TOP_ADD_SIGNED_2X 150 
#define  WINED3D_TOP_ADD_SMOOTH 149 
#define  WINED3D_TOP_BLEND_CURRENT_ALPHA 148 
#define  WINED3D_TOP_BLEND_DIFFUSE_ALPHA 147 
#define  WINED3D_TOP_BLEND_FACTOR_ALPHA 146 
#define  WINED3D_TOP_BLEND_TEXTURE_ALPHA 145 
#define  WINED3D_TOP_BLEND_TEXTURE_ALPHA_PM 144 
#define  WINED3D_TOP_BUMPENVMAP 143 
#define  WINED3D_TOP_BUMPENVMAP_LUMINANCE 142 
#define  WINED3D_TOP_DISABLE 141 
#define  WINED3D_TOP_DOTPRODUCT3 140 
#define  WINED3D_TOP_LERP 139 
#define  WINED3D_TOP_MODULATE 138 
#define  WINED3D_TOP_MODULATE_2X 137 
#define  WINED3D_TOP_MODULATE_4X 136 
#define  WINED3D_TOP_MODULATE_ALPHA_ADD_COLOR 135 
#define  WINED3D_TOP_MODULATE_COLOR_ADD_ALPHA 134 
#define  WINED3D_TOP_MODULATE_INVALPHA_ADD_COLOR 133 
#define  WINED3D_TOP_MODULATE_INVCOLOR_ADD_ALPHA 132 
#define  WINED3D_TOP_MULTIPLY_ADD 131 
#define  WINED3D_TOP_SELECT_ARG1 130 
#define  WINED3D_TOP_SELECT_ARG2 129 
#define  WINED3D_TOP_SUBTRACT 128 
 int /*<<< orphan*/  atifs_color_fixup (struct wined3d_gl_info const*,struct color_fixup_desc,unsigned int) ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 int /*<<< orphan*/  debug_swizzle (unsigned int) ; 
 unsigned int find_tmpreg (struct texture_stage_op const*) ; 
 int /*<<< orphan*/  glBeginFragmentShaderATI () ; 
 int /*<<< orphan*/  glBindFragmentShaderATI (unsigned int) ; 
 int /*<<< orphan*/  glEndFragmentShaderATI () ; 
 int /*<<< orphan*/  glGenFragmentShadersATI (int) ; 
 int /*<<< orphan*/  glPassTexCoordATI (unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  glSampleMapATI (unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  is_identity_fixup (struct color_fixup_desc) ; 
 scalar_t__ op_reads_constant (struct texture_stage_op const*) ; 
 scalar_t__ op_reads_texture (struct texture_stage_op const*) ; 
 scalar_t__ op_reads_tfactor (struct texture_stage_op const*) ; 
 unsigned int register_for_arg (int /*<<< orphan*/ ,struct wined3d_gl_info const*,unsigned int,unsigned int*,unsigned int*,int) ; 
 int /*<<< orphan*/  wrap_op1 (struct wined3d_gl_info const*,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  wrap_op2 (struct wined3d_gl_info const*,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  wrap_op3 (struct wined3d_gl_info const*,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static GLuint gen_ati_shader(const struct texture_stage_op op[MAX_TEXTURES],
        const struct wined3d_gl_info *gl_info, enum atifs_constant_value *constants)
{
    GLuint ret = GL_EXTCALL(glGenFragmentShadersATI(1));
    unsigned int stage;
    GLuint arg0, arg1, arg2, extrarg;
    GLuint dstmod, argmod0, argmod1, argmod2, argmodextra;
    GLuint rep0, rep1, rep2;
    GLuint swizzle;
    GLuint tmparg = find_tmpreg(op);
    GLuint dstreg;
    BOOL tfactor_used = FALSE;

    if(!ret) {
        ERR("Failed to generate a GL_ATI_fragment_shader shader id\n");
        return 0;
    }
    GL_EXTCALL(glBindFragmentShaderATI(ret));
    checkGLcall("GL_EXTCALL(glBindFragmentShaderATI(ret))");

    TRACE("glBeginFragmentShaderATI()\n");
    GL_EXTCALL(glBeginFragmentShaderATI());
    checkGLcall("GL_EXTCALL(glBeginFragmentShaderATI())");

    /* Pass 1: Generate sampling instructions for perturbation maps */
    for (stage = 0; stage < gl_info->limits.textures; ++stage)
    {
        if (op[stage].cop == WINED3D_TOP_DISABLE)
            break;
        if (op[stage].cop != WINED3D_TOP_BUMPENVMAP
                && op[stage].cop != WINED3D_TOP_BUMPENVMAP_LUMINANCE)
            continue;

        constants[stage] = ATIFS_CONSTANT_BUMP;

        TRACE("glSampleMapATI(GL_REG_%d_ATI, GL_TEXTURE_%d_ARB, GL_SWIZZLE_STR_ATI)\n",
              stage, stage);
        GL_EXTCALL(glSampleMapATI(GL_REG_0_ATI + stage, GL_TEXTURE0_ARB + stage, GL_SWIZZLE_STR_ATI));
        if (op[stage + 1].projected == WINED3D_PROJECTION_NONE)
            swizzle = GL_SWIZZLE_STR_ATI;
        else if (op[stage + 1].projected == WINED3D_PROJECTION_COUNT4)
            swizzle = GL_SWIZZLE_STQ_DQ_ATI;
        else
            swizzle = GL_SWIZZLE_STR_DR_ATI;
        TRACE("glPassTexCoordATI(GL_REG_%d_ATI, GL_TEXTURE_%d_ARB, %s)\n",
              stage + 1, stage + 1, debug_swizzle(swizzle));
        GL_EXTCALL(glPassTexCoordATI(GL_REG_0_ATI + stage + 1,
                   GL_TEXTURE0_ARB + stage + 1,
                   swizzle));
    }

    /* Pass 2: Generate perturbation calculations */
    for (stage = 0; stage < gl_info->limits.textures; ++stage)
    {
        GLuint argmodextra_x, argmodextra_y;
        struct color_fixup_desc fixup;

        if (op[stage].cop == WINED3D_TOP_DISABLE)
            break;
        if (op[stage].cop != WINED3D_TOP_BUMPENVMAP
                && op[stage].cop != WINED3D_TOP_BUMPENVMAP_LUMINANCE)
            continue;

        fixup = op[stage].color_fixup;
        if (fixup.x_source != CHANNEL_SOURCE_X || fixup.y_source != CHANNEL_SOURCE_Y)
        {
            FIXME("Swizzles not implemented\n");
            argmodextra_x = GL_NONE;
            argmodextra_y = GL_NONE;
        }
        else
        {
            /* Nice thing, we get the color correction for free :-) */
            argmodextra_x = fixup.x_sign_fixup ? GL_2X_BIT_ATI | GL_BIAS_BIT_ATI : GL_NONE;
            argmodextra_y = fixup.y_sign_fixup ? GL_2X_BIT_ATI | GL_BIAS_BIT_ATI : GL_NONE;
        }

        wrap_op3(gl_info, GL_DOT2_ADD_ATI, GL_REG_0_ATI + stage + 1, GL_RED_BIT_ATI, GL_NONE,
                 GL_REG_0_ATI + stage, GL_NONE, argmodextra_x,
                 ATIFS_CONST_BUMPMAT(stage), GL_NONE, GL_2X_BIT_ATI | GL_BIAS_BIT_ATI,
                 GL_REG_0_ATI + stage + 1, GL_RED, GL_NONE);

        /* Don't use GL_DOT2_ADD_ATI here because we cannot configure it to read the blue and alpha
         * component of the bump matrix. Instead do this with two MADs:
         *
         * coord.a = tex.r * bump.b + coord.g
         * coord.g = tex.g * bump.a + coord.a
         *
         * The first instruction writes to alpha so it can be coissued with the above DOT2_ADD.
         * coord.a is unused. If the perturbed texture is projected, this was already handled
         * in the glPassTexCoordATI above.
         */
        wrap_op3(gl_info, GL_MAD_ATI, GL_REG_0_ATI + stage + 1, GL_ALPHA, GL_NONE,
                 GL_REG_0_ATI + stage, GL_RED, argmodextra_y,
                 ATIFS_CONST_BUMPMAT(stage), GL_BLUE, GL_2X_BIT_ATI | GL_BIAS_BIT_ATI,
                 GL_REG_0_ATI + stage + 1, GL_GREEN, GL_NONE);
        wrap_op3(gl_info, GL_MAD_ATI, GL_REG_0_ATI + stage + 1, GL_GREEN_BIT_ATI, GL_NONE,
                 GL_REG_0_ATI + stage, GL_GREEN, argmodextra_y,
                 ATIFS_CONST_BUMPMAT(stage), GL_ALPHA, GL_2X_BIT_ATI | GL_BIAS_BIT_ATI,
                 GL_REG_0_ATI + stage + 1, GL_ALPHA, GL_NONE);
    }

    /* Pass 3: Generate sampling instructions for regular textures */
    for (stage = 0; stage < gl_info->limits.textures; ++stage)
    {
        if (op[stage].cop == WINED3D_TOP_DISABLE)
            break;

        if (op[stage].projected == WINED3D_PROJECTION_NONE)
            swizzle = GL_SWIZZLE_STR_ATI;
        else if (op[stage].projected == WINED3D_PROJECTION_COUNT3)
            swizzle = GL_SWIZZLE_STR_DR_ATI;
        else
            swizzle = GL_SWIZZLE_STQ_DQ_ATI;

        if (op_reads_texture(&op[stage]))
        {
            if (stage > 0
                    && (op[stage - 1].cop == WINED3D_TOP_BUMPENVMAP
                    || op[stage - 1].cop == WINED3D_TOP_BUMPENVMAP_LUMINANCE))
            {
                TRACE("glSampleMapATI(GL_REG_%d_ATI, GL_REG_%d_ATI, GL_SWIZZLE_STR_ATI)\n",
                      stage, stage);
                GL_EXTCALL(glSampleMapATI(GL_REG_0_ATI + stage,
                           GL_REG_0_ATI + stage,
                           GL_SWIZZLE_STR_ATI));
            } else {
                TRACE("glSampleMapATI(GL_REG_%d_ATI, GL_TEXTURE_%d_ARB, %s)\n",
                    stage, stage, debug_swizzle(swizzle));
                GL_EXTCALL(glSampleMapATI(GL_REG_0_ATI + stage,
                                        GL_TEXTURE0_ARB + stage,
                                        swizzle));
            }
        }
    }

    /* Pass 4: Generate the arithmetic instructions */
    for (stage = 0; stage < MAX_TEXTURES; ++stage)
    {
        if (op[stage].cop == WINED3D_TOP_DISABLE)
        {
            if (!stage)
            {
                /* Handle complete texture disabling gracefully */
                wrap_op1(gl_info, GL_MOV_ATI, GL_REG_0_ATI, GL_NONE, GL_NONE,
                         GL_PRIMARY_COLOR, GL_NONE, GL_NONE);
                wrap_op1(gl_info, GL_MOV_ATI, GL_REG_0_ATI, GL_ALPHA, GL_NONE,
                         GL_PRIMARY_COLOR, GL_NONE, GL_NONE);
            }
            break;
        }

        if (op[stage].tmp_dst)
        {
            /* If we're writing to D3DTA_TEMP, but never reading from it we
             * don't have to write there in the first place. Skip the entire
             * stage, this saves some GPU time. */
            if (tmparg == GL_NONE)
                continue;

            dstreg = tmparg;
        }
        else
        {
            dstreg = GL_REG_0_ATI;
        }

        if (op[stage].cop == WINED3D_TOP_BUMPENVMAP || op[stage].cop == WINED3D_TOP_BUMPENVMAP_LUMINANCE)
        {
            /* Those are handled in the first pass of the shader (generation pass 1 and 2) already */
            continue;
        }

        arg0 = register_for_arg(op[stage].carg0, gl_info, stage, &argmod0, &rep0, tmparg);
        arg1 = register_for_arg(op[stage].carg1, gl_info, stage, &argmod1, &rep1, tmparg);
        arg2 = register_for_arg(op[stage].carg2, gl_info, stage, &argmod2, &rep2, tmparg);
        dstmod = GL_NONE;
        argmodextra = GL_NONE;
        extrarg = GL_NONE;

        if (op_reads_tfactor(&op[stage]))
            tfactor_used = TRUE;

        if (op_reads_constant(&op[stage]))
        {
            if (constants[stage] != ATIFS_CONSTANT_UNUSED)
                FIXME("Constant %u already used.\n", stage);
            constants[stage] = ATIFS_CONSTANT_STAGE;
        }

        if (op_reads_texture(&op[stage]) && !is_identity_fixup(op[stage].color_fixup))
            atifs_color_fixup(gl_info, op[stage].color_fixup, GL_REG_0_ATI + stage);

        switch (op[stage].cop)
        {
            case WINED3D_TOP_SELECT_ARG2:
                arg1 = arg2;
                argmod1 = argmod2;
                rep1 = rep2;
                /* fall through */
            case WINED3D_TOP_SELECT_ARG1:
                wrap_op1(gl_info, GL_MOV_ATI, dstreg, GL_NONE, GL_NONE,
                         arg1, rep1, argmod1);
                break;

            case WINED3D_TOP_MODULATE_4X:
                if(dstmod == GL_NONE) dstmod = GL_4X_BIT_ATI;
                /* fall through */
            case WINED3D_TOP_MODULATE_2X:
                if(dstmod == GL_NONE) dstmod = GL_2X_BIT_ATI;
                dstmod |= GL_SATURATE_BIT_ATI;
                /* fall through */
            case WINED3D_TOP_MODULATE:
                wrap_op2(gl_info, GL_MUL_ATI, dstreg, GL_NONE, dstmod,
                         arg1, rep1, argmod1,
                         arg2, rep2, argmod2);
                break;

            case WINED3D_TOP_ADD_SIGNED_2X:
                dstmod = GL_2X_BIT_ATI;
                /* fall through */
            case WINED3D_TOP_ADD_SIGNED:
                argmodextra = GL_BIAS_BIT_ATI;
                /* fall through */
            case WINED3D_TOP_ADD:
                dstmod |= GL_SATURATE_BIT_ATI;
                wrap_op2(gl_info, GL_ADD_ATI, GL_REG_0_ATI, GL_NONE, dstmod,
                         arg1, rep1, argmod1,
                         arg2, rep2, argmodextra | argmod2);
                break;

            case WINED3D_TOP_SUBTRACT:
                dstmod |= GL_SATURATE_BIT_ATI;
                wrap_op2(gl_info, GL_SUB_ATI, dstreg, GL_NONE, dstmod,
                         arg1, rep1, argmod1,
                         arg2, rep2, argmod2);
                break;

            case WINED3D_TOP_ADD_SMOOTH:
                argmodextra = argmod1 & GL_COMP_BIT_ATI ? argmod1 & ~GL_COMP_BIT_ATI : argmod1 | GL_COMP_BIT_ATI;
                /* Dst = arg1 + * arg2(1 -arg 1)
                 *     = arg2 * (1 - arg1) + arg1
                 */
                wrap_op3(gl_info, GL_MAD_ATI, dstreg, GL_NONE, GL_SATURATE_BIT_ATI,
                         arg2, rep2, argmod2,
                         arg1, rep1, argmodextra,
                         arg1, rep1, argmod1);
                break;

            case WINED3D_TOP_BLEND_CURRENT_ALPHA:
                if (extrarg == GL_NONE)
                    extrarg = register_for_arg(WINED3DTA_CURRENT, gl_info, stage, NULL, NULL, -1);
                /* fall through */
            case WINED3D_TOP_BLEND_FACTOR_ALPHA:
                if (extrarg == GL_NONE)
                    extrarg = register_for_arg(WINED3DTA_TFACTOR, gl_info, stage, NULL, NULL, -1);
                /* fall through */
            case WINED3D_TOP_BLEND_TEXTURE_ALPHA:
                if (extrarg == GL_NONE)
                    extrarg = register_for_arg(WINED3DTA_TEXTURE, gl_info, stage, NULL, NULL, -1);
                /* fall through */
            case WINED3D_TOP_BLEND_DIFFUSE_ALPHA:
                if (extrarg == GL_NONE)
                    extrarg = register_for_arg(WINED3DTA_DIFFUSE, gl_info, stage, NULL, NULL, -1);
                wrap_op3(gl_info, GL_LERP_ATI, dstreg, GL_NONE, GL_NONE,
                         extrarg, GL_ALPHA, GL_NONE,
                         arg1, rep1, argmod1,
                         arg2, rep2, argmod2);
                break;

            case WINED3D_TOP_BLEND_TEXTURE_ALPHA_PM:
                arg0 = register_for_arg(WINED3DTA_TEXTURE, gl_info, stage, NULL, NULL, -1);
                wrap_op3(gl_info, GL_MAD_ATI, dstreg, GL_NONE, GL_NONE,
                         arg2, rep2,  argmod2,
                         arg0, GL_ALPHA, GL_COMP_BIT_ATI,
                         arg1, rep1,  argmod1);
                break;

            /* D3DTOP_PREMODULATE ???? */

            case WINED3D_TOP_MODULATE_INVALPHA_ADD_COLOR:
                argmodextra = argmod1 & GL_COMP_BIT_ATI ? argmod1 & ~GL_COMP_BIT_ATI : argmod1 | GL_COMP_BIT_ATI;
                /* fall through */
            case WINED3D_TOP_MODULATE_ALPHA_ADD_COLOR:
                if (!argmodextra)
                    argmodextra = argmod1;
                wrap_op3(gl_info, GL_MAD_ATI, dstreg, GL_NONE, GL_SATURATE_BIT_ATI,
                         arg2, rep2,  argmod2,
                         arg1, GL_ALPHA, argmodextra,
                         arg1, rep1,  argmod1);
                break;

            case WINED3D_TOP_MODULATE_INVCOLOR_ADD_ALPHA:
                argmodextra = argmod1 & GL_COMP_BIT_ATI ? argmod1 & ~GL_COMP_BIT_ATI : argmod1 | GL_COMP_BIT_ATI;
                /* fall through */
            case WINED3D_TOP_MODULATE_COLOR_ADD_ALPHA:
                if (!argmodextra)
                    argmodextra = argmod1;
                wrap_op3(gl_info, GL_MAD_ATI, dstreg, GL_NONE, GL_SATURATE_BIT_ATI,
                         arg2, rep2,  argmod2,
                         arg1, rep1,  argmodextra,
                         arg1, GL_ALPHA, argmod1);
                break;

            case WINED3D_TOP_DOTPRODUCT3:
                wrap_op2(gl_info, GL_DOT3_ATI, dstreg, GL_NONE, GL_4X_BIT_ATI | GL_SATURATE_BIT_ATI,
                         arg1, rep1, argmod1 | GL_BIAS_BIT_ATI,
                         arg2, rep2, argmod2 | GL_BIAS_BIT_ATI);
                break;

            case WINED3D_TOP_MULTIPLY_ADD:
                wrap_op3(gl_info, GL_MAD_ATI, dstreg, GL_NONE, GL_SATURATE_BIT_ATI,
                         arg1, rep1, argmod1,
                         arg2, rep2, argmod2,
                         arg0, rep0, argmod0);
                break;

            case WINED3D_TOP_LERP:
                wrap_op3(gl_info, GL_LERP_ATI, dstreg, GL_NONE, GL_NONE,
                         arg0, rep0, argmod0,
                         arg1, rep1, argmod1,
                         arg2, rep2, argmod2);
                break;

            default: FIXME("Unhandled color operation %d on stage %d\n", op[stage].cop, stage);
        }

        arg0 = register_for_arg(op[stage].aarg0, gl_info, stage, &argmod0, NULL, tmparg);
        arg1 = register_for_arg(op[stage].aarg1, gl_info, stage, &argmod1, NULL, tmparg);
        arg2 = register_for_arg(op[stage].aarg2, gl_info, stage, &argmod2, NULL, tmparg);
        dstmod = GL_NONE;
        argmodextra = GL_NONE;
        extrarg = GL_NONE;

        switch (op[stage].aop)
        {
            case WINED3D_TOP_DISABLE:
                /* Get the primary color to the output if on stage 0, otherwise leave register 0 untouched */
                if (!stage)
                {
                    wrap_op1(gl_info, GL_MOV_ATI, GL_REG_0_ATI, GL_ALPHA, GL_NONE,
                             GL_PRIMARY_COLOR, GL_NONE, GL_NONE);
                }
                break;

            case WINED3D_TOP_SELECT_ARG2:
                arg1 = arg2;
                argmod1 = argmod2;
                /* fall through */
            case WINED3D_TOP_SELECT_ARG1:
                wrap_op1(gl_info, GL_MOV_ATI, dstreg, GL_ALPHA, GL_NONE,
                         arg1, GL_NONE, argmod1);
                break;

            case WINED3D_TOP_MODULATE_4X:
                if (dstmod == GL_NONE)
                    dstmod = GL_4X_BIT_ATI;
                /* fall through */
            case WINED3D_TOP_MODULATE_2X:
                if (dstmod == GL_NONE)
                    dstmod = GL_2X_BIT_ATI;
                dstmod |= GL_SATURATE_BIT_ATI;
                /* fall through */
            case WINED3D_TOP_MODULATE:
                wrap_op2(gl_info, GL_MUL_ATI, dstreg, GL_ALPHA, dstmod,
                         arg1, GL_NONE, argmod1,
                         arg2, GL_NONE, argmod2);
                break;

            case WINED3D_TOP_ADD_SIGNED_2X:
                dstmod = GL_2X_BIT_ATI;
                /* fall through */
            case WINED3D_TOP_ADD_SIGNED:
                argmodextra = GL_BIAS_BIT_ATI;
                /* fall through */
            case WINED3D_TOP_ADD:
                dstmod |= GL_SATURATE_BIT_ATI;
                wrap_op2(gl_info, GL_ADD_ATI, dstreg, GL_ALPHA, dstmod,
                         arg1, GL_NONE, argmod1,
                         arg2, GL_NONE, argmodextra | argmod2);
                break;

            case WINED3D_TOP_SUBTRACT:
                dstmod |= GL_SATURATE_BIT_ATI;
                wrap_op2(gl_info, GL_SUB_ATI, dstreg, GL_ALPHA, dstmod,
                         arg1, GL_NONE, argmod1,
                         arg2, GL_NONE, argmod2);
                break;

            case WINED3D_TOP_ADD_SMOOTH:
                argmodextra = argmod1 & GL_COMP_BIT_ATI ? argmod1 & ~GL_COMP_BIT_ATI : argmod1 | GL_COMP_BIT_ATI;
                /* Dst = arg1 + * arg2(1 -arg 1)
                 *     = arg2 * (1 - arg1) + arg1
                 */
                wrap_op3(gl_info, GL_MAD_ATI, dstreg, GL_ALPHA, GL_SATURATE_BIT_ATI,
                         arg2, GL_NONE, argmod2,
                         arg1, GL_NONE, argmodextra,
                         arg1, GL_NONE, argmod1);
                break;

            case WINED3D_TOP_BLEND_CURRENT_ALPHA:
                if (extrarg == GL_NONE)
                    extrarg = register_for_arg(WINED3DTA_CURRENT, gl_info, stage, NULL, NULL, -1);
                /* fall through */
            case WINED3D_TOP_BLEND_FACTOR_ALPHA:
                if (extrarg == GL_NONE)
                    extrarg = register_for_arg(WINED3DTA_TFACTOR, gl_info, stage, NULL, NULL, -1);
                /* fall through */
            case WINED3D_TOP_BLEND_TEXTURE_ALPHA:
                if (extrarg == GL_NONE)
                    extrarg = register_for_arg(WINED3DTA_TEXTURE, gl_info, stage, NULL, NULL, -1);
                /* fall through */
            case WINED3D_TOP_BLEND_DIFFUSE_ALPHA:
                if (extrarg == GL_NONE)
                    extrarg = register_for_arg(WINED3DTA_DIFFUSE, gl_info, stage, NULL, NULL, -1);
                wrap_op3(gl_info, GL_LERP_ATI, dstreg, GL_ALPHA, GL_NONE,
                         extrarg, GL_ALPHA, GL_NONE,
                         arg1, GL_NONE, argmod1,
                         arg2, GL_NONE, argmod2);
                break;

            case WINED3D_TOP_BLEND_TEXTURE_ALPHA_PM:
                arg0 = register_for_arg(WINED3DTA_TEXTURE, gl_info, stage, NULL, NULL, -1);
                wrap_op3(gl_info, GL_MAD_ATI, dstreg, GL_ALPHA, GL_NONE,
                         arg2, GL_NONE,  argmod2,
                         arg0, GL_ALPHA, GL_COMP_BIT_ATI,
                         arg1, GL_NONE,  argmod1);
                break;

            /* D3DTOP_PREMODULATE ???? */

            case WINED3D_TOP_DOTPRODUCT3:
                wrap_op2(gl_info, GL_DOT3_ATI, dstreg, GL_ALPHA, GL_4X_BIT_ATI | GL_SATURATE_BIT_ATI,
                         arg1, GL_NONE, argmod1 | GL_BIAS_BIT_ATI,
                         arg2, GL_NONE, argmod2 | GL_BIAS_BIT_ATI);
                break;

            case WINED3D_TOP_MULTIPLY_ADD:
                wrap_op3(gl_info, GL_MAD_ATI, dstreg, GL_ALPHA, GL_SATURATE_BIT_ATI,
                         arg1, GL_NONE, argmod1,
                         arg2, GL_NONE, argmod2,
                         arg0, GL_NONE, argmod0);
                break;

            case WINED3D_TOP_LERP:
                wrap_op3(gl_info, GL_LERP_ATI, dstreg, GL_ALPHA, GL_SATURATE_BIT_ATI,
                         arg1, GL_NONE, argmod1,
                         arg2, GL_NONE, argmod2,
                         arg0, GL_NONE, argmod0);
                break;

            case WINED3D_TOP_MODULATE_INVALPHA_ADD_COLOR:
            case WINED3D_TOP_MODULATE_ALPHA_ADD_COLOR:
            case WINED3D_TOP_MODULATE_COLOR_ADD_ALPHA:
            case WINED3D_TOP_MODULATE_INVCOLOR_ADD_ALPHA:
            case WINED3D_TOP_BUMPENVMAP:
            case WINED3D_TOP_BUMPENVMAP_LUMINANCE:
                ERR("Application uses an invalid alpha operation\n");
                break;

            default: FIXME("Unhandled alpha operation %d on stage %d\n", op[stage].aop, stage);
        }
    }

    if (tfactor_used && constants[ATIFS_CONST_TFACTOR - GL_CON_0_ATI] != ATIFS_CONSTANT_UNUSED)
        FIXME("Texture factor constant already used.\n");
    constants[ATIFS_CONST_TFACTOR - GL_CON_0_ATI] = ATIFS_CONSTANT_TFACTOR;

    /* Assign unused constants to avoid reloading due to unused <-> bump matrix switches. */
    for (stage = 0; stage < MAX_TEXTURES; ++stage)
    {
        if (constants[stage] == ATIFS_CONSTANT_UNUSED)
            constants[stage] = ATIFS_CONSTANT_BUMP;
    }

    TRACE("glEndFragmentShaderATI()\n");
    GL_EXTCALL(glEndFragmentShaderATI());
    checkGLcall("GL_EXTCALL(glEndFragmentShaderATI())");
    return ret;
}