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
struct wined3d_shader {struct glsl_shader_private* backend_data; } ;
struct wined3d_context {int dummy; } ;
struct shader_glsl_priv {int /*<<< orphan*/  shader_buffer; } ;
struct TYPE_2__ {struct glsl_hs_compiled_shader* hs; } ;
struct glsl_shader_private {int num_gl_shaders; unsigned int shader_array_size; TYPE_1__ gl_shaders; } ;
struct glsl_hs_compiled_shader {int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  GLuint ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  TRACE (char*,struct wined3d_shader*) ; 
 int /*<<< orphan*/  assert (int) ; 
 struct glsl_hs_compiled_shader* heap_alloc (int) ; 
 struct glsl_shader_private* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  shader_glsl_generate_hull_shader (struct wined3d_context const*,struct shader_glsl_priv*,struct wined3d_shader*) ; 
 int /*<<< orphan*/  string_buffer_clear (int /*<<< orphan*/ *) ; 

__attribute__((used)) static GLuint find_glsl_hull_shader(const struct wined3d_context *context,
        struct shader_glsl_priv *priv, struct wined3d_shader *shader)
{
    struct glsl_hs_compiled_shader *gl_shaders, *new_array;
    struct glsl_shader_private *shader_data;
    unsigned int new_size;
    GLuint ret;

    if (!shader->backend_data)
    {
        if (!(shader->backend_data = heap_alloc_zero(sizeof(*shader_data))))
        {
            ERR("Failed to allocate backend data.\n");
            return 0;
        }
    }
    shader_data = shader->backend_data;
    gl_shaders = shader_data->gl_shaders.hs;

    if (shader_data->num_gl_shaders > 0)
    {
        assert(shader_data->num_gl_shaders == 1);
        return gl_shaders[0].id;
    }

    TRACE("No matching GL shader found for shader %p, compiling a new shader.\n", shader);

    assert(!shader_data->gl_shaders.hs);
    new_size = 1;
    if (!(new_array = heap_alloc(sizeof(*new_array))))
    {
        ERR("Failed to allocate GL shaders array.\n");
        return 0;
    }
    shader_data->gl_shaders.hs = new_array;
    shader_data->shader_array_size = new_size;
    gl_shaders = new_array;

    string_buffer_clear(&priv->shader_buffer);
    ret = shader_glsl_generate_hull_shader(context, priv, shader);
    gl_shaders[shader_data->num_gl_shaders++].id = ret;

    return ret;
}