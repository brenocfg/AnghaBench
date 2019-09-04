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
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
struct wined3d_shader_reg_maps {int /*<<< orphan*/ * cb_sizes; TYPE_1__ shader_version; } ;
struct wined3d_gl_info {int /*<<< orphan*/  limits; } ;
struct shader_glsl_priv {int /*<<< orphan*/  string_buffers; } ;
typedef  int /*<<< orphan*/  GLuint ;

/* Variables and functions */
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 int /*<<< orphan*/  glGetUniformBlockIndex (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glUniformBlockBinding (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 char* shader_glsl_get_prefix (int /*<<< orphan*/ ) ; 
 scalar_t__ shader_glsl_use_layout_binding_qualifier (struct wined3d_gl_info const*) ; 
 struct wined3d_string_buffer* string_buffer_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  string_buffer_release (int /*<<< orphan*/ *,struct wined3d_string_buffer*) ; 
 int /*<<< orphan*/  string_buffer_sprintf (struct wined3d_string_buffer*,char*,char const*,unsigned int) ; 
 int /*<<< orphan*/  wined3d_gl_limits_get_uniform_block_range (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int*,unsigned int*) ; 

__attribute__((used)) static void shader_glsl_init_uniform_block_bindings(const struct wined3d_gl_info *gl_info,
        struct shader_glsl_priv *priv, GLuint program_id,
        const struct wined3d_shader_reg_maps *reg_maps)
{
    const char *prefix = shader_glsl_get_prefix(reg_maps->shader_version.type);
    struct wined3d_string_buffer *name;
    unsigned int i, base, count;
    GLuint block_idx;

    if (shader_glsl_use_layout_binding_qualifier(gl_info))
        return;

    name = string_buffer_get(&priv->string_buffers);
    wined3d_gl_limits_get_uniform_block_range(&gl_info->limits, reg_maps->shader_version.type, &base, &count);
    for (i = 0; i < count; ++i)
    {
        if (!reg_maps->cb_sizes[i])
            continue;

        string_buffer_sprintf(name, "block_%s_cb%u", prefix, i);
        block_idx = GL_EXTCALL(glGetUniformBlockIndex(program_id, name->buffer));
        GL_EXTCALL(glUniformBlockBinding(program_id, block_idx, base + i));
    }
    checkGLcall("glUniformBlockBinding");
    string_buffer_release(&priv->string_buffers, name);
}