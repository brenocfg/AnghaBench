#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct wined3d_string_buffer_list {int dummy; } ;
struct wined3d_string_buffer {int /*<<< orphan*/  buffer; } ;
struct wined3d_shader_signature_element {int /*<<< orphan*/  register_idx; } ;
struct wined3d_shader_reg_maps {scalar_t__ viewport_array; } ;
struct TYPE_8__ {unsigned int element_count; struct wined3d_shader_signature_element* elements; } ;
struct TYPE_6__ {int input_type; int instance_count; int output_type; unsigned int vertices_out; int /*<<< orphan*/  so_desc; } ;
struct TYPE_7__ {TYPE_2__ gs; } ;
struct wined3d_shader {TYPE_4__ output_signature; scalar_t__ function; TYPE_3__ u; TYPE_1__* limits; struct wined3d_shader_reg_maps reg_maps; } ;
struct wined3d_gl_info {int /*<<< orphan*/ * supported; } ;
struct wined3d_context {struct wined3d_gl_info* gl_info; } ;
struct shader_glsl_priv {struct wined3d_string_buffer shader_buffer; struct wined3d_string_buffer_list string_buffers; } ;
struct shader_glsl_ctx_priv {struct wined3d_string_buffer_list* string_buffers; } ;
struct gs_compile_args {int primitive_type; int /*<<< orphan*/  interpolation_mode; int /*<<< orphan*/  output_count; } ;
typedef  int /*<<< orphan*/  priv_ctx ;
typedef  enum wined3d_primitive_type { ____Placeholder_wined3d_primitive_type } wined3d_primitive_type ;
struct TYPE_5__ {int /*<<< orphan*/  packed_input; } ;
typedef  int /*<<< orphan*/  GLuint ;

/* Variables and functions */
 size_t ARB_CLIP_CONTROL ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_GEOMETRY_SHADER ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WINED3D_MAX_VIEWPORTS ; 
#define  WINED3D_PT_LINELIST 130 
#define  WINED3D_PT_POINTLIST 129 
#define  WINED3D_PT_TRIANGLELIST 128 
 int /*<<< orphan*/  debug_d3dprimitivetype (int) ; 
 int /*<<< orphan*/  glCreateShader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glsl_primitive_type_from_d3d (int) ; 
 scalar_t__ is_rasterization_disabled (struct wined3d_shader const*) ; 
 int /*<<< orphan*/  memset (struct shader_glsl_ctx_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,...) ; 
 int /*<<< orphan*/  shader_generate_code (struct wined3d_shader const*,struct wined3d_string_buffer*,struct wined3d_shader_reg_maps const*,struct shader_glsl_ctx_priv*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shader_generate_glsl_declarations (struct wined3d_context const*,struct wined3d_string_buffer*,struct wined3d_shader const*,struct wined3d_shader_reg_maps const*,struct shader_glsl_ctx_priv*) ; 
 int /*<<< orphan*/  shader_glsl_add_version_declaration (struct wined3d_string_buffer*,struct wined3d_gl_info const*) ; 
 int /*<<< orphan*/  shader_glsl_compile (struct wined3d_gl_info const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_glsl_enable_extensions (struct wined3d_string_buffer*,struct wined3d_gl_info const*) ; 
 int /*<<< orphan*/  shader_glsl_fixup_position (struct wined3d_string_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_glsl_generate_sm4_output_setup (struct shader_glsl_priv*,struct wined3d_shader const*,int /*<<< orphan*/ ,struct wined3d_gl_info const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_glsl_generate_stream_output_setup (struct shader_glsl_priv*,struct wined3d_shader const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static GLuint shader_glsl_generate_geometry_shader(const struct wined3d_context *context,
        struct shader_glsl_priv *priv, const struct wined3d_shader *shader, const struct gs_compile_args *args)
{
    struct wined3d_string_buffer_list *string_buffers = &priv->string_buffers;
    const struct wined3d_shader_reg_maps *reg_maps = &shader->reg_maps;
    struct wined3d_string_buffer *buffer = &priv->shader_buffer;
    const struct wined3d_gl_info *gl_info = context->gl_info;
    const struct wined3d_shader_signature_element *output;
    enum wined3d_primitive_type primitive_type;
    struct shader_glsl_ctx_priv priv_ctx;
    unsigned int max_vertices;
    unsigned int i, j;
    GLuint shader_id;

    memset(&priv_ctx, 0, sizeof(priv_ctx));
    priv_ctx.string_buffers = string_buffers;

    shader_glsl_add_version_declaration(buffer, gl_info);

    shader_glsl_enable_extensions(buffer, gl_info);

    shader_generate_glsl_declarations(context, buffer, shader, reg_maps, &priv_ctx);

    primitive_type = shader->u.gs.input_type ? shader->u.gs.input_type : args->primitive_type;
    shader_addline(buffer, "layout(%s", glsl_primitive_type_from_d3d(primitive_type));
    if (shader->u.gs.instance_count > 1)
        shader_addline(buffer, ", invocations = %u", shader->u.gs.instance_count);
    shader_addline(buffer, ") in;\n");

    primitive_type = shader->u.gs.output_type ? shader->u.gs.output_type : args->primitive_type;
    if (!(max_vertices = shader->u.gs.vertices_out))
    {
        switch (args->primitive_type)
        {
            case WINED3D_PT_POINTLIST:
                max_vertices = 1;
                break;
            case WINED3D_PT_LINELIST:
                max_vertices = 2;
                break;
            case WINED3D_PT_TRIANGLELIST:
                max_vertices = 3;
                break;
            default:
                FIXME("Unhandled primitive type %s.\n", debug_d3dprimitivetype(args->primitive_type));
                break;
        }
    }
    shader_addline(buffer, "layout(%s, max_vertices = %u) out;\n",
            glsl_primitive_type_from_d3d(primitive_type), max_vertices);
    shader_addline(buffer, "in shader_in_out { vec4 reg[%u]; } shader_in[];\n", shader->limits->packed_input);

    if (!gl_info->supported[ARB_CLIP_CONTROL])
    {
        shader_addline(buffer, "uniform vec4 pos_fixup");
        if (reg_maps->viewport_array)
            shader_addline(buffer, "[%u]", WINED3D_MAX_VIEWPORTS);
        shader_addline(buffer, ";\n");
    }

    if (is_rasterization_disabled(shader))
    {
        shader_glsl_generate_stream_output_setup(priv, shader, &shader->u.gs.so_desc);
    }
    else
    {
        shader_glsl_generate_sm4_output_setup(priv, shader, args->output_count,
                gl_info, TRUE, args->interpolation_mode);
    }

    shader_addline(buffer, "void main()\n{\n");
    if (shader->function)
    {
        if (FAILED(shader_generate_code(shader, buffer, reg_maps, &priv_ctx, NULL, NULL)))
            return 0;
    }
    else
    {
        for (i = 0; i < max_vertices; ++i)
        {
            for (j = 0; j < shader->output_signature.element_count; ++j)
            {
                output = &shader->output_signature.elements[j];
                shader_addline(buffer, "gs_out[%u] = shader_in[%u].reg[%u];\n",
                        output->register_idx, i, output->register_idx);
            }
            shader_addline(buffer, "setup_gs_output(gs_out);\n");
            if (!gl_info->supported[ARB_CLIP_CONTROL])
                shader_glsl_fixup_position(buffer, FALSE);
            shader_addline(buffer, "EmitVertex();\n");
        }
    }
    shader_addline(buffer, "}\n");

    shader_id = GL_EXTCALL(glCreateShader(GL_GEOMETRY_SHADER));
    TRACE("Compiling shader object %u.\n", shader_id);
    shader_glsl_compile(gl_info, shader_id, buffer->buffer);

    return shader_id;
}