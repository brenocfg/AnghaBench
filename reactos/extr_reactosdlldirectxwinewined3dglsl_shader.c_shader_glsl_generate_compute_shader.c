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
struct wined3d_string_buffer_list {int dummy; } ;
struct wined3d_string_buffer {int /*<<< orphan*/  buffer; } ;
struct wined3d_shader_thread_group_size {int /*<<< orphan*/  z; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct wined3d_shader_reg_maps {unsigned int tgsm_count; TYPE_3__* tgsm; } ;
struct TYPE_4__ {struct wined3d_shader_thread_group_size thread_group_size; } ;
struct TYPE_5__ {TYPE_1__ cs; } ;
struct wined3d_shader {struct wined3d_shader_reg_maps reg_maps; TYPE_2__ u; } ;
struct wined3d_gl_info {int dummy; } ;
struct wined3d_context {struct wined3d_gl_info* gl_info; } ;
struct shader_glsl_ctx_priv {struct wined3d_string_buffer_list* string_buffers; } ;
typedef  int /*<<< orphan*/  priv_ctx ;
struct TYPE_6__ {scalar_t__ size; } ;
typedef  int /*<<< orphan*/  GLuint ;

/* Variables and functions */
 int /*<<< orphan*/  GL_COMPUTE_SHADER ; 
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glCreateShader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct shader_glsl_ctx_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,...) ; 
 int /*<<< orphan*/  shader_generate_code (struct wined3d_shader const*,struct wined3d_string_buffer*,struct wined3d_shader_reg_maps const*,struct shader_glsl_ctx_priv*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shader_generate_glsl_declarations (struct wined3d_context const*,struct wined3d_string_buffer*,struct wined3d_shader const*,struct wined3d_shader_reg_maps const*,struct shader_glsl_ctx_priv*) ; 
 int /*<<< orphan*/  shader_glsl_add_version_declaration (struct wined3d_string_buffer*,struct wined3d_gl_info const*) ; 
 int /*<<< orphan*/  shader_glsl_compile (struct wined3d_gl_info const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_glsl_enable_extensions (struct wined3d_string_buffer*,struct wined3d_gl_info const*) ; 

__attribute__((used)) static GLuint shader_glsl_generate_compute_shader(const struct wined3d_context *context,
        struct wined3d_string_buffer *buffer, struct wined3d_string_buffer_list *string_buffers,
        const struct wined3d_shader *shader)
{
    const struct wined3d_shader_thread_group_size *thread_group_size = &shader->u.cs.thread_group_size;
    const struct wined3d_shader_reg_maps *reg_maps = &shader->reg_maps;
    const struct wined3d_gl_info *gl_info = context->gl_info;
    struct shader_glsl_ctx_priv priv_ctx;
    GLuint shader_id;
    unsigned int i;

    memset(&priv_ctx, 0, sizeof(priv_ctx));
    priv_ctx.string_buffers = string_buffers;

    shader_glsl_add_version_declaration(buffer, gl_info);

    shader_glsl_enable_extensions(buffer, gl_info);
    shader_addline(buffer, "#extension GL_ARB_compute_shader : enable\n");

    shader_generate_glsl_declarations(context, buffer, shader, reg_maps, &priv_ctx);

    for (i = 0; i < reg_maps->tgsm_count; ++i)
    {
        if (reg_maps->tgsm[i].size)
            shader_addline(buffer, "shared uint cs_g%u[%u];\n", i, reg_maps->tgsm[i].size);
    }

    shader_addline(buffer, "layout(local_size_x = %u, local_size_y = %u, local_size_z = %u) in;\n",
            thread_group_size->x, thread_group_size->y, thread_group_size->z);

    shader_addline(buffer, "void main()\n{\n");
    shader_generate_code(shader, buffer, reg_maps, &priv_ctx, NULL, NULL);
    shader_addline(buffer, "}\n");

    shader_id = GL_EXTCALL(glCreateShader(GL_COMPUTE_SHADER));
    TRACE("Compiling shader object %u.\n", shader_id);
    shader_glsl_compile(gl_info, shader_id, buffer->buffer);

    return shader_id;
}