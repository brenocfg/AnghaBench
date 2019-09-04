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
struct wined3d_string_buffer {int /*<<< orphan*/  buffer; } ;
struct TYPE_4__ {int type; } ;
struct wined3d_shader_src_param {int /*<<< orphan*/  modifiers; TYPE_2__ reg; } ;
struct wined3d_shader_instruction {TYPE_1__* ctx; } ;
struct shader_glsl_ctx_priv {int /*<<< orphan*/  string_buffers; } ;
struct glsl_src_param {char* reg_name; char* param_str; } ;
typedef  enum wined3d_data_type { ____Placeholder_wined3d_data_type } wined3d_data_type ;
struct TYPE_3__ {struct shader_glsl_ctx_priv* backend_data; } ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
#define  WINED3DSPR_FORKINSTID 137 
#define  WINED3DSPR_GSINSTID 136 
#define  WINED3DSPR_IMMCONST 135 
#define  WINED3DSPR_JOININSTID 134 
#define  WINED3DSPR_LOCALTHREADID 133 
#define  WINED3DSPR_LOCALTHREADINDEX 132 
#define  WINED3DSPR_OUTPOINTID 131 
#define  WINED3DSPR_PRIMID 130 
#define  WINED3DSPR_THREADGROUPID 129 
#define  WINED3DSPR_THREADID 128 
 int WINED3D_DATA_FLOAT ; 
 int WINED3D_DATA_INT ; 
 int /*<<< orphan*/  shader_glsl_gen_modifier (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  shader_glsl_get_register_name (TYPE_2__*,int,char*,int /*<<< orphan*/ *,struct wined3d_shader_instruction const*) ; 
 int /*<<< orphan*/  shader_glsl_get_swizzle (struct wined3d_shader_src_param const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  shader_glsl_sprintf_cast (struct wined3d_string_buffer*,char*,int,int) ; 
 struct wined3d_string_buffer* string_buffer_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_buffer_release (int /*<<< orphan*/ ,struct wined3d_string_buffer*) ; 

__attribute__((used)) static void shader_glsl_add_src_param_ext(const struct wined3d_shader_instruction *ins,
        const struct wined3d_shader_src_param *wined3d_src, DWORD mask, struct glsl_src_param *glsl_src,
        enum wined3d_data_type data_type)
{
    struct shader_glsl_ctx_priv *priv = ins->ctx->backend_data;
    struct wined3d_string_buffer *reg_name = string_buffer_get(priv->string_buffers);
    enum wined3d_data_type param_data_type;
    BOOL is_color = FALSE;
    char swizzle_str[6];

    glsl_src->reg_name[0] = '\0';
    glsl_src->param_str[0] = '\0';
    swizzle_str[0] = '\0';

    shader_glsl_get_register_name(&wined3d_src->reg, data_type, glsl_src->reg_name, &is_color, ins);
    shader_glsl_get_swizzle(wined3d_src, is_color, mask, swizzle_str);

    switch (wined3d_src->reg.type)
    {
        case WINED3DSPR_IMMCONST:
            param_data_type = data_type;
            break;
        case WINED3DSPR_FORKINSTID:
        case WINED3DSPR_GSINSTID:
        case WINED3DSPR_JOININSTID:
        case WINED3DSPR_LOCALTHREADID:
        case WINED3DSPR_LOCALTHREADINDEX:
        case WINED3DSPR_OUTPOINTID:
        case WINED3DSPR_PRIMID:
        case WINED3DSPR_THREADGROUPID:
        case WINED3DSPR_THREADID:
            param_data_type = WINED3D_DATA_INT;
            break;
        default:
            param_data_type = WINED3D_DATA_FLOAT;
            break;
    }

    shader_glsl_sprintf_cast(reg_name, glsl_src->reg_name, data_type, param_data_type);
    shader_glsl_gen_modifier(wined3d_src->modifiers, reg_name->buffer, swizzle_str, glsl_src->param_str);

    string_buffer_release(priv->string_buffers, reg_name);
}