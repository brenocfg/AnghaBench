#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  i_chroma; } ;
struct TYPE_7__ {TYPE_2__* vt; TYPE_1__ fmt; int /*<<< orphan*/  gl; scalar_t__ b_dump_shaders; int /*<<< orphan*/  glsl_version; } ;
typedef  TYPE_3__ opengl_tex_converter_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* CompileShader ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* ShaderSource ) (int /*<<< orphan*/ ,int,char const**,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* CreateShader ) (int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  GLuint ;

/* Variables and functions */
 int /*<<< orphan*/  GL_VERTEX_SHADER ; 
 scalar_t__ asprintf (char**,char const*,int /*<<< orphan*/ ,char const*,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ ,char*,char const*,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int,char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static GLuint BuildVertexShader(const opengl_tex_converter_t *tc,
                                unsigned plane_count)
{
    /* Basic vertex shader */
    static const char *template =
        "#version %u\n"
        "varying vec2 TexCoord0;\n"
        "attribute vec4 MultiTexCoord0;\n"
        "%s%s"
        "attribute vec3 VertexPosition;\n"
        "uniform mat4 OrientationMatrix;\n"
        "uniform mat4 ProjectionMatrix;\n"
        "uniform mat4 ZoomMatrix;\n"
        "uniform mat4 ViewMatrix;\n"
        "void main() {\n"
        " TexCoord0 = vec4(OrientationMatrix * MultiTexCoord0).st;\n"
        "%s%s"
        " gl_Position = ProjectionMatrix * ZoomMatrix * ViewMatrix\n"
        "               * vec4(VertexPosition, 1.0);\n"
        "}";

    const char *coord1_header = plane_count > 1 ?
        "varying vec2 TexCoord1;\nattribute vec4 MultiTexCoord1;\n" : "";
    const char *coord1_code = plane_count > 1 ?
        " TexCoord1 = vec4(OrientationMatrix * MultiTexCoord1).st;\n" : "";
    const char *coord2_header = plane_count > 2 ?
        "varying vec2 TexCoord2;\nattribute vec4 MultiTexCoord2;\n" : "";
    const char *coord2_code = plane_count > 2 ?
        " TexCoord2 = vec4(OrientationMatrix * MultiTexCoord2).st;\n" : "";

    char *code;
    if (asprintf(&code, template, tc->glsl_version, coord1_header, coord2_header,
                 coord1_code, coord2_code) < 0)
        return 0;

    GLuint shader = tc->vt->CreateShader(GL_VERTEX_SHADER);
    tc->vt->ShaderSource(shader, 1, (const char **) &code, NULL);
    if (tc->b_dump_shaders)
        msg_Dbg(tc->gl, "\n=== Vertex shader for fourcc: %4.4s ===\n%s\n",
                (const char *)&tc->fmt.i_chroma, code);
    tc->vt->CompileShader(shader);
    free(code);
    return shader;
}