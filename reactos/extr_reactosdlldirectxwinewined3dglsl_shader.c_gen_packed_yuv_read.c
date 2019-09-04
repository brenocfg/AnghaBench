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
struct wined3d_gl_info {scalar_t__* supported; } ;
struct glsl_blitter_args {int /*<<< orphan*/  fixup; } ;
typedef  enum complex_fixup { ____Placeholder_complex_fixup } complex_fixup ;

/* Variables and functions */
 int COMPLEX_FIXUP_UYVY ; 
 size_t WINED3D_GL_LEGACY_CONTEXT ; 
 int get_complex_fixup (int /*<<< orphan*/ ) ; 
 scalar_t__ needs_legacy_glsl_syntax (struct wined3d_gl_info const*) ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,...) ; 

__attribute__((used)) static void gen_packed_yuv_read(struct wined3d_string_buffer *buffer,
        const struct wined3d_gl_info *gl_info, const struct glsl_blitter_args *args,
        const char *tex_type)
{
    enum complex_fixup complex_fixup = get_complex_fixup(args->fixup);
    char chroma, luminance;
    const char *tex;

    /* The YUY2 and UYVY formats contain two pixels packed into a 32 bit
     * macropixel, giving effectively 16 bits per pixel. The color consists of
     * a luminance(Y) and two chroma(U and V) values. Each macropixel has two
     * luminance values, one for each single pixel it contains, and one U and
     * one V value shared between both pixels.
     *
     * The data is loaded into an A8L8 texture. With YUY2, the luminance
     * component contains the luminance and alpha the chroma. With UYVY it is
     * vice versa. Thus take the format into account when generating the read
     * swizzles
     *
     * Reading the Y value is straightforward - just sample the texture. The
     * hardware takes care of filtering in the horizontal and vertical
     * direction.
     *
     * Reading the U and V values is harder. We have to avoid filtering
     * horizontally, because that would mix the U and V values of one pixel or
     * two adjacent pixels.  Thus floor the texture coordinate and add 0.5 to
     * get an unfiltered read, regardless of the filtering setting. Vertical
     * filtering works automatically though - the U and V values of two rows
     * are mixed nicely.
     *
     * Apart of avoiding filtering issues, the code has to know which value it
     * just read, and where it can find the other one. To determine this, it
     * checks if it sampled an even or odd pixel, and shifts the 2nd read
     * accordingly.
     *
     * Handling horizontal filtering of U and V values requires reading a 2nd
     * pair of pixels, extracting U and V and mixing them. This is not
     * implemented yet.
     *
     * An alternative implementation idea is to load the texture as A8R8G8B8
     * texture, with width / 2. This way one read gives all 3 values, finding
     * U and V is easy in an unfiltered situation. Finding the luminance on
     * the other hand requires finding out if it is an odd or even pixel. The
     * real drawback of this approach is filtering. This would have to be
     * emulated completely in the shader, reading up two 2 packed pixels in up
     * to 2 rows and interpolating both horizontally and vertically. Beyond
     * that it would require adjustments to the texture handling code to deal
     * with the width scaling. */

    if (complex_fixup == COMPLEX_FIXUP_UYVY)
    {
        chroma = 'x';
        luminance = gl_info->supported[WINED3D_GL_LEGACY_CONTEXT] ? 'w' : 'y';
    }
    else
    {
        chroma = gl_info->supported[WINED3D_GL_LEGACY_CONTEXT] ? 'w' : 'y';
        luminance = 'x';
    }

    tex = needs_legacy_glsl_syntax(gl_info) ? tex_type : "";

    /* First we have to read the chroma values. This means we need at least
     * two pixels (no filtering), or 4 pixels (with filtering). To get the
     * unmodified chroma, we have to rid ourselves of the filtering when we
     * sample the texture. */
    shader_addline(buffer, "    texcoord.xy = out_texcoord.xy;\n");
    /* We must not allow filtering between pixel x and x+1, this would mix U
     * and V. Vertical filtering is ok. However, bear in mind that the pixel
     * center is at 0.5, so add 0.5. */
    shader_addline(buffer, "    texcoord.x = (floor(texcoord.x * size.x) + 0.5) / size.x;\n");
    shader_addline(buffer, "    luminance = texture%s(sampler, texcoord.xy).%c;\n", tex, chroma);

    /* Multiply the x coordinate by 0.5 and get the fraction. This gives 0.25
     * and 0.75 for the even and odd pixels respectively. */
    /* Put the value into either of the chroma values. */
    shader_addline(buffer, "    bool even = fract(texcoord.x * size.x * 0.5) < 0.5;\n");
    shader_addline(buffer, "    if (even)\n");
    shader_addline(buffer, "        chroma.y = luminance;\n");
    shader_addline(buffer, "    else\n");
    shader_addline(buffer, "        chroma.x = luminance;\n");

    /* Sample pixel 2. If we read an even pixel, sample the pixel right to the
     * current one. Otherwise, sample the left pixel. */
    shader_addline(buffer, "    texcoord.x += even ? 1.0 / size.x : -1.0 / size.x;\n");
    shader_addline(buffer, "    luminance = texture%s(sampler, texcoord.xy).%c;\n", tex, chroma);

    /* Put the value into the other chroma. */
    shader_addline(buffer, "    if (even)\n");
    shader_addline(buffer, "        chroma.x = luminance;\n");
    shader_addline(buffer, "    else\n");
    shader_addline(buffer, "        chroma.y = luminance;\n");

    /* TODO: If filtering is enabled, sample a 2nd pair of pixels left or right of
     * the current one and lerp the two U and V values. */

    /* This gives the correctly filtered luminance value. */
    shader_addline(buffer, "    luminance = texture%s(sampler, out_texcoord.xy).%c;\n", tex, luminance);
}