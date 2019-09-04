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

__attribute__((used)) static void gen_nv12_read(struct wined3d_string_buffer *buffer,
        const struct wined3d_gl_info *gl_info, const char *tex_type)
{
    char component = gl_info->supported[WINED3D_GL_LEGACY_CONTEXT] ? 'w' : 'x';
    const char *tex = needs_legacy_glsl_syntax(gl_info) ? tex_type : "";

    /* NV12 surfaces contain a WxH sized luminance plane, followed by a
     * (W/2)x(H/2) sized plane where each component is an UV pair. So the
     * effective bitdepth is 12 bits per pixel. If the whole texture is
     * interpreted as luminance data it looks approximately like this:
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
     *        +----------------------------------+----
     *        |UVUVUVUVUVUVUVUVUVUVUVUVUVUVUVUVUV|
     *        |UVUVUVUVUVUVUVUVUVUVUVUVUVUVUVUVUV|
     *        |                                  |   1
     *        |                                  |   -
     *        |                                  |   3
     *        |                                  |
     *        |                                  |
     *        +----------------------------------+---- */

    /* First sample the chroma values. */
    shader_addline(buffer, "    texcoord.xy = out_texcoord.xy;\n");
    /* We only have half the number of chroma pixels. */
    shader_addline(buffer, "    texcoord.x *= 0.5;\n");
    shader_addline(buffer, "    texcoord.y = (texcoord.y + 2.0) / 3.0;\n");

    /* We must not allow filtering horizontally, this would mix U and V.
     * Vertical filtering is ok. However, bear in mind that the pixel center
     * is at 0.5, so add 0.5. */

    /* Convert to non-normalised coordinates so we can find the individual
     * pixel. */
    shader_addline(buffer, "    texcoord.x = floor(texcoord.x * size.x);\n");
    /* Multiply by 2 since chroma components are stored in UV pixel pairs, add
     * 0.5 to hit the center of the pixel. Then convert back to normalised
     * coordinates. */
    shader_addline(buffer, "    texcoord.x = (texcoord.x * 2.0 + 0.5) / size.x;\n");
    /* Clamp, keep the half pixel origin in mind. */
    shader_addline(buffer, "    texcoord.y = max(texcoord.y, 2.0 / 3.0 + 0.5 / size.y);\n");

    shader_addline(buffer, "    chroma.y = texture%s(sampler, texcoord.xy).%c;\n", tex, component);
    /* Add 1.0 / size.x to sample the adjacent texel. */
    shader_addline(buffer, "    texcoord.x += 1.0 / size.x;\n");
    shader_addline(buffer, "    chroma.x = texture%s(sampler, texcoord.xy).%c;\n", tex, component);

    /* Sample the luminance value. It is in the top 2/3rd of the texture, so
     * scale the y coordinate. Clamp the y coordinate to prevent the chroma
     * values from bleeding into the sampled luminance values due to
     * filtering. */
    shader_addline(buffer, "    texcoord.xy = out_texcoord.xy;\n");
    /* Multiply the y coordinate by 2/3 and clamp it. */
    shader_addline(buffer, "    texcoord.y = min(texcoord.y * 2.0 / 3.0, 2.0 / 3.0 - 0.5 / size.y);\n");
    shader_addline(buffer, "    luminance = texture%s(sampler, texcoord.xy).%c;\n", tex, component);
}