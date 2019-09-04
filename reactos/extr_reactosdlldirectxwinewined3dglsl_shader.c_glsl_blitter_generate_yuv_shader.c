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
struct wined3d_string_buffer {int dummy; } ;
struct wined3d_gl_info {int dummy; } ;
struct glsl_blitter_args {int /*<<< orphan*/  fixup; } ;
typedef  enum complex_fixup { ____Placeholder_complex_fixup } complex_fixup ;

/* Variables and functions */
#define  COMPLEX_FIXUP_NV12 131 
#define  COMPLEX_FIXUP_UYVY 130 
#define  COMPLEX_FIXUP_YUY2 129 
#define  COMPLEX_FIXUP_YV12 128 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  gen_nv12_read (struct wined3d_string_buffer*,struct wined3d_gl_info const*,char const*) ; 
 int /*<<< orphan*/  gen_packed_yuv_read (struct wined3d_string_buffer*,struct wined3d_gl_info const*,struct glsl_blitter_args const*,char const*) ; 
 int /*<<< orphan*/  gen_yv12_read (struct wined3d_string_buffer*,struct wined3d_gl_info const*,char const*) ; 
 int get_complex_fixup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,...) ; 
 int /*<<< orphan*/  string_buffer_free (struct wined3d_string_buffer*) ; 

__attribute__((used)) static void glsl_blitter_generate_yuv_shader(struct wined3d_string_buffer *buffer,
        const struct wined3d_gl_info *gl_info, const struct glsl_blitter_args *args,
        const char *output, const char *tex_type, const char *swizzle)
{
    enum complex_fixup complex_fixup = get_complex_fixup(args->fixup);

    shader_addline(buffer, "const vec4 yuv_coef = vec4(1.403, -0.344, -0.714, 1.770);\n");
    shader_addline(buffer, "float luminance;\n");
    shader_addline(buffer, "vec2 texcoord;\n");
    shader_addline(buffer, "vec2 chroma;\n");
    shader_addline(buffer, "uniform vec2 size;\n");

    shader_addline(buffer, "\nvoid main()\n{\n");

    switch (complex_fixup)
    {
        case COMPLEX_FIXUP_UYVY:
        case COMPLEX_FIXUP_YUY2:
            gen_packed_yuv_read(buffer, gl_info, args, tex_type);
            break;

        case COMPLEX_FIXUP_YV12:
            gen_yv12_read(buffer, gl_info, tex_type);
            break;

        case COMPLEX_FIXUP_NV12:
            gen_nv12_read(buffer, gl_info, tex_type);
            break;

        default:
            FIXME("Unsupported fixup %#x.\n", complex_fixup);
            string_buffer_free(buffer);
            return;
    }

    /* Calculate the final result. Formula is taken from
     * http://www.fourcc.org/fccyvrgb.php. Note that the chroma
     * ranges from -0.5 to 0.5. */
    shader_addline(buffer, "\n    chroma.xy -= 0.5;\n");

    shader_addline(buffer, "    %s.x = luminance + chroma.x * yuv_coef.x;\n", output);
    shader_addline(buffer, "    %s.y = luminance + chroma.y * yuv_coef.y + chroma.x * yuv_coef.z;\n", output);
    shader_addline(buffer, "    %s.z = luminance + chroma.y * yuv_coef.w;\n", output);

    shader_addline(buffer, "}\n");
}