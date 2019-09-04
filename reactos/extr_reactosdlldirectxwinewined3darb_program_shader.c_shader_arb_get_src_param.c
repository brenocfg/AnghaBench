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
struct wined3d_string_buffer {int dummy; } ;
struct wined3d_shader_src_param {int modifiers; int /*<<< orphan*/  reg; } ;
struct wined3d_shader_instruction {TYPE_3__* ctx; } ;
struct shader_arb_ctx_priv {int /*<<< orphan*/  target_version; } ;
struct TYPE_6__ {TYPE_2__* reg_maps; struct shader_arb_ctx_priv* backend_data; struct wined3d_string_buffer* buffer; } ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
struct TYPE_5__ {TYPE_1__ shader_version; } ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ARB_ONE ; 
 int /*<<< orphan*/  ARB_TWO ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  NV2 ; 
 scalar_t__ TRUE ; 
#define  WINED3DSPSM_ABS 140 
#define  WINED3DSPSM_ABSNEG 139 
#define  WINED3DSPSM_BIAS 138 
#define  WINED3DSPSM_BIASNEG 137 
#define  WINED3DSPSM_COMP 136 
#define  WINED3DSPSM_DW 135 
#define  WINED3DSPSM_DZ 134 
#define  WINED3DSPSM_NEG 133 
#define  WINED3DSPSM_NONE 132 
#define  WINED3DSPSM_SIGN 131 
#define  WINED3DSPSM_SIGNNEG 130 
#define  WINED3DSPSM_X2 129 
#define  WINED3DSPSM_X2NEG 128 
 char* arb_get_helper_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,char,char const*,...) ; 
 int /*<<< orphan*/  shader_arb_get_register_name (struct wined3d_shader_instruction const*,int /*<<< orphan*/ *,char*,scalar_t__*) ; 
 int /*<<< orphan*/  shader_arb_get_swizzle (struct wined3d_shader_src_param const*,scalar_t__,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

__attribute__((used)) static void shader_arb_get_src_param(const struct wined3d_shader_instruction *ins,
        const struct wined3d_shader_src_param *src, unsigned int tmpreg, char *outregstr)
{
    /* Generate a line that does the input modifier computation and return the input register to use */
    BOOL is_color = FALSE, insert_line;
    char regstr[256];
    char swzstr[20];
    struct wined3d_string_buffer *buffer = ins->ctx->buffer;
    struct shader_arb_ctx_priv *ctx = ins->ctx->backend_data;
    const char *one = arb_get_helper_value(ins->ctx->reg_maps->shader_version.type, ARB_ONE);
    const char *two = arb_get_helper_value(ins->ctx->reg_maps->shader_version.type, ARB_TWO);

    /* Assume a new line will be added */
    insert_line = TRUE;

    /* Get register name */
    shader_arb_get_register_name(ins, &src->reg, regstr, &is_color);
    shader_arb_get_swizzle(src, is_color, swzstr);

    switch (src->modifiers)
    {
    case WINED3DSPSM_NONE:
        sprintf(outregstr, "%s%s", regstr, swzstr);
        insert_line = FALSE;
        break;
    case WINED3DSPSM_NEG:
        sprintf(outregstr, "-%s%s", regstr, swzstr);
        insert_line = FALSE;
        break;
    case WINED3DSPSM_BIAS:
        shader_addline(buffer, "ADD T%c, %s, -coefdiv.x;\n", 'A' + tmpreg, regstr);
        break;
    case WINED3DSPSM_BIASNEG:
        shader_addline(buffer, "ADD T%c, -%s, coefdiv.x;\n", 'A' + tmpreg, regstr);
        break;
    case WINED3DSPSM_SIGN:
        shader_addline(buffer, "MAD T%c, %s, %s, -%s;\n", 'A' + tmpreg, regstr, two, one);
        break;
    case WINED3DSPSM_SIGNNEG:
        shader_addline(buffer, "MAD T%c, %s, -%s, %s;\n", 'A' + tmpreg, regstr, two, one);
        break;
    case WINED3DSPSM_COMP:
        shader_addline(buffer, "SUB T%c, %s, %s;\n", 'A' + tmpreg, one, regstr);
        break;
    case WINED3DSPSM_X2:
        shader_addline(buffer, "ADD T%c, %s, %s;\n", 'A' + tmpreg, regstr, regstr);
        break;
    case WINED3DSPSM_X2NEG:
        shader_addline(buffer, "ADD T%c, -%s, -%s;\n", 'A' + tmpreg, regstr, regstr);
        break;
    case WINED3DSPSM_DZ:
        shader_addline(buffer, "RCP T%c, %s.z;\n", 'A' + tmpreg, regstr);
        shader_addline(buffer, "MUL T%c, %s, T%c;\n", 'A' + tmpreg, regstr, 'A' + tmpreg);
        break;
    case WINED3DSPSM_DW:
        shader_addline(buffer, "RCP T%c, %s.w;\n", 'A' + tmpreg, regstr);
        shader_addline(buffer, "MUL T%c, %s, T%c;\n", 'A' + tmpreg, regstr, 'A' + tmpreg);
        break;
    case WINED3DSPSM_ABS:
        if(ctx->target_version >= NV2) {
            sprintf(outregstr, "|%s%s|", regstr, swzstr);
            insert_line = FALSE;
        } else {
            shader_addline(buffer, "ABS T%c, %s;\n", 'A' + tmpreg, regstr);
        }
        break;
    case WINED3DSPSM_ABSNEG:
        if(ctx->target_version >= NV2) {
            sprintf(outregstr, "-|%s%s|", regstr, swzstr);
        } else {
            shader_addline(buffer, "ABS T%c, %s;\n", 'A' + tmpreg, regstr);
            sprintf(outregstr, "-T%c%s", 'A' + tmpreg, swzstr);
        }
        insert_line = FALSE;
        break;
    default:
        sprintf(outregstr, "%s%s", regstr, swzstr);
        insert_line = FALSE;
    }

    /* Return modified or original register, with swizzle */
    if (insert_line)
        sprintf(outregstr, "T%c%s", 'A' + tmpreg, swzstr);
}