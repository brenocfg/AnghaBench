#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct wined3d_gl_info {int dummy; } ;
typedef  char GLuint ;
typedef  size_t GLint ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,...) ; 
 int /*<<< orphan*/  FIXME (char*,...) ; 
 int /*<<< orphan*/  GL_ATTACHED_SHADERS ; 
 int /*<<< orphan*/  GL_COMPILE_STATUS ; 
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_SHADER_SOURCE_LENGTH ; 
 int /*<<< orphan*/  GL_SHADER_TYPE ; 
 int /*<<< orphan*/  debug_gl_shader_type (size_t) ; 
 char* get_info_log_line (char const**) ; 
 int /*<<< orphan*/  glGetAttachedShaders (char,size_t,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  glGetProgramiv (char,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  glGetShaderSource (char,size_t,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  glGetShaderiv (char,int /*<<< orphan*/ ,size_t*) ; 
 char* heap_alloc_zero (size_t) ; 
 char* heap_calloc (size_t,int) ; 
 int /*<<< orphan*/  heap_free (char*) ; 

__attribute__((used)) static void shader_glsl_dump_program_source(const struct wined3d_gl_info *gl_info, GLuint program)
{
    GLint i, shader_count, source_size = -1;
    GLuint *shaders;
    char *source = NULL;

    GL_EXTCALL(glGetProgramiv(program, GL_ATTACHED_SHADERS, &shader_count));
    if (!(shaders = heap_calloc(shader_count, sizeof(*shaders))))
    {
        ERR("Failed to allocate shader array memory.\n");
        return;
    }

    GL_EXTCALL(glGetAttachedShaders(program, shader_count, NULL, shaders));
    for (i = 0; i < shader_count; ++i)
    {
        const char *ptr, *line;
        GLint tmp;

        GL_EXTCALL(glGetShaderiv(shaders[i], GL_SHADER_SOURCE_LENGTH, &tmp));

        if (source_size < tmp)
        {
            heap_free(source);

            if (!(source = heap_alloc_zero(tmp)))
            {
                ERR("Failed to allocate %d bytes for shader source.\n", tmp);
                heap_free(shaders);
                return;
            }
            source_size = tmp;
        }

        FIXME("Shader %u:\n", shaders[i]);
        GL_EXTCALL(glGetShaderiv(shaders[i], GL_SHADER_TYPE, &tmp));
        FIXME("    GL_SHADER_TYPE: %s.\n", debug_gl_shader_type(tmp));
        GL_EXTCALL(glGetShaderiv(shaders[i], GL_COMPILE_STATUS, &tmp));
        FIXME("    GL_COMPILE_STATUS: %d.\n", tmp);
        FIXME("\n");

        ptr = source;
        GL_EXTCALL(glGetShaderSource(shaders[i], source_size, NULL, source));
        while ((line = get_info_log_line(&ptr))) FIXME("    %.*s", (int)(ptr - line), line);
        FIXME("\n");
    }

    heap_free(source);
    heap_free(shaders);
}