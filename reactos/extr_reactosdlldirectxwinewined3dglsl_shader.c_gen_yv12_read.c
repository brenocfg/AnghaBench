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

/* Variables and functions */
 size_t WINED3D_GL_LEGACY_CONTEXT ; 
 scalar_t__ needs_legacy_glsl_syntax (struct wined3d_gl_info const*) ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,...) ; 

__attribute__((used)) static void gen_yv12_read(struct wined3d_string_buffer *buffer,
        const struct wined3d_gl_info *gl_info, const char *tex_type)
{
    char component = gl_info->supported[WINED3D_GL_LEGACY_CONTEXT] ? 'w' : 'x';
    const char *tex = needs_legacy_glsl_syntax(gl_info) ? tex_type : "";

    /* YV12 surfaces contain a WxH sized luminance plane, followed by a
     * (W/2)x(H/2) V and a (W/2)x(H/2) U plane, each with 8 bit per pixel. So
     * the effective bitdepth is 12 bits per pixel. Since the U and V planes
     * have only half the pitch of the luminance plane, the packing into the
     * gl texture is a bit unfortunate. If the whole texture is interpreted as
     * luminance data it looks approximately like this:
     *
     *        +----------------------------------+----
     *        |                                  |
     *        |                                  |
     *        |                                  |
     *        |                                  |
     *        |                                  |   2
     *        |            LUMINANCE             |   -
     *        |                                  |   3
     *        |                                  |
     *        |                                  |
     *        |                                  |
     *        |                                  |
     *        +----------------+-----------------+----
     *        |                |                 |
     *        |  V even rows   |  V odd rows     |
     *        |                |                 |   1
     *        +----------------+------------------   -
     *        |                |                 |   3
     *        |  U even rows   |  U odd rows     |
     *        |                |                 |
     *        +----------------+-----------------+----
     *        |                |                 |
     *        |     0.5        |       0.5       |
     *
     * So it appears as if there are 4 chroma images, but in fact the odd rows
     * in the chroma images are in the same row as the even ones. So it is
     * kinda tricky to read. */

    /* First sample the chroma values. */
    shader_addline(buffer, "    texcoord.xy = out_texcoord.xy;\n");
    /* The chroma planes have only half the width. */
    shader_addline(buffer, "    texcoord.x *= 0.5;\n");

    /* The first value is between 2/3 and 5/6 of the texture's height, so
     * scale+bias the coordinate. Also read the right side of the image when
     * reading odd lines.
     *
     * Don't forget to clamp the y values in into the range, otherwise we'll
     * get filtering bleeding. */

    /* Read odd lines from the right side (add 0.5 to the x coordinate). */
    shader_addline(buffer, "    if (fract(floor(texcoord.y * size.y) * 0.5 + 1.0 / 6.0) >= 0.5)\n");
    shader_addline(buffer, "        texcoord.x += 0.5;\n");

    /* Clamp, keep the half pixel origin in mind. */
    shader_addline(buffer, "    texcoord.y = clamp(2.0 / 3.0 + texcoord.y / 6.0, "
            "2.0 / 3.0 + 0.5 / size.y, 5.0 / 6.0 - 0.5 / size.y);\n");

    shader_addline(buffer, "    chroma.x = texture%s(sampler, texcoord.xy).%c;\n", tex, component);

    /* The other chroma value is 1/6th of the texture lower, from 5/6th to
     * 6/6th No need to clamp because we're just reusing the already clamped
     * value from above. */
    shader_addline(buffer, "    texcoord.y += 1.0 / 6.0;\n");
    shader_addline(buffer, "    chroma.y = texture%s(sampler, texcoord.xy).%c;\n", tex, component);

    /* Sample the luminance value. It is in the top 2/3rd of the texture, so
     * scale the y coordinate.  Clamp the y coordinate to prevent the chroma
     * values from bleeding into the sampled luminance values due to
     * filtering. */
    shader_addline(buffer, "    texcoord.xy = out_texcoord.xy;\n");
    /* Multiply the y coordinate by 2/3 and clamp it. */
    shader_addline(buffer, "    texcoord.y = min(texcoord.y * 2.0 / 3.0, 2.0 / 3.0 - 0.5 / size.y);\n");
    shader_addline(buffer, "    luminance = texture%s(sampler, texcoord.xy).%c;\n", tex, component);
}