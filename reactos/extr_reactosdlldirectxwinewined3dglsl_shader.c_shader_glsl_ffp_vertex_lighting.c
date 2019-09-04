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
struct wined3d_ffp_vs_settings {unsigned int point_light_count; unsigned int spot_light_count; unsigned int directional_light_count; unsigned int parallel_point_light_count; int /*<<< orphan*/  normal; int /*<<< orphan*/  emissive_source; int /*<<< orphan*/  specular_source; int /*<<< orphan*/  diffuse_source; int /*<<< orphan*/  ambient_source; int /*<<< orphan*/  lighting; } ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,...) ; 
 char* shader_glsl_ffp_mcs (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  shader_glsl_ffp_vertex_lighting_footer (struct wined3d_string_buffer*,struct wined3d_ffp_vs_settings const*,unsigned int) ; 

__attribute__((used)) static void shader_glsl_ffp_vertex_lighting(struct wined3d_string_buffer *buffer,
        const struct wined3d_ffp_vs_settings *settings, BOOL legacy_lighting)
{
    const char *diffuse, *specular, *emissive, *ambient;
    unsigned int i, idx;

    if (!settings->lighting)
    {
        shader_addline(buffer, "ffp_varying_diffuse = ffp_attrib_diffuse;\n");
        shader_addline(buffer, "ffp_varying_specular = ffp_attrib_specular;\n");
        return;
    }

    shader_addline(buffer, "vec3 ambient = ffp_light_ambient;\n");
    shader_addline(buffer, "vec3 diffuse = vec3(0.0);\n");
    shader_addline(buffer, "vec4 specular = vec4(0.0);\n");
    shader_addline(buffer, "vec3 dir, dst;\n");
    shader_addline(buffer, "float att, t;\n");

    ambient = shader_glsl_ffp_mcs(settings->ambient_source, "ffp_material.ambient");
    diffuse = shader_glsl_ffp_mcs(settings->diffuse_source, "ffp_material.diffuse");
    specular = shader_glsl_ffp_mcs(settings->specular_source, "ffp_material.specular");
    emissive = shader_glsl_ffp_mcs(settings->emissive_source, "ffp_material.emissive");

    idx = 0;
    for (i = 0; i < settings->point_light_count; ++i, ++idx)
    {
        shader_addline(buffer, "dir = ffp_light[%u].position.xyz - ec_pos.xyz;\n", idx);
        shader_addline(buffer, "dst.z = dot(dir, dir);\n");
        shader_addline(buffer, "dst.y = sqrt(dst.z);\n");
        shader_addline(buffer, "dst.x = 1.0;\n");
        if (legacy_lighting)
        {
            shader_addline(buffer, "dst.y = (ffp_light[%u].range - dst.y) / ffp_light[%u].range;\n", idx, idx);
            shader_addline(buffer, "dst.z = dst.y * dst.y;\n");
            shader_addline(buffer, "if (dst.y > 0.0)\n{\n");
        }
        else
        {
            shader_addline(buffer, "if (dst.y <= ffp_light[%u].range)\n{\n", idx);
        }
        shader_addline(buffer, "att = dot(dst.xyz, vec3(ffp_light[%u].c_att,"
                " ffp_light[%u].l_att, ffp_light[%u].q_att));\n", idx, idx, idx);
        if (!legacy_lighting)
            shader_addline(buffer, "att = 1.0 / att;\n");
        shader_addline(buffer, "ambient += ffp_light[%u].ambient.xyz * att;\n", idx);
        if (!settings->normal)
        {
            shader_addline(buffer, "}\n");
            continue;
        }
        shader_addline(buffer, "dir = normalize(dir);\n");
        shader_glsl_ffp_vertex_lighting_footer(buffer, settings, idx);
        shader_addline(buffer, "}\n");
    }

    for (i = 0; i < settings->spot_light_count; ++i, ++idx)
    {
        shader_addline(buffer, "dir = ffp_light[%u].position.xyz - ec_pos.xyz;\n", idx);
        shader_addline(buffer, "dst.z = dot(dir, dir);\n");
        shader_addline(buffer, "dst.y = sqrt(dst.z);\n");
        shader_addline(buffer, "dst.x = 1.0;\n");
        if (legacy_lighting)
        {
            shader_addline(buffer, "dst.y = (ffp_light[%u].range - dst.y) / ffp_light[%u].range;\n", idx, idx);
            shader_addline(buffer, "dst.z = dst.y * dst.y;\n");
            shader_addline(buffer, "if (dst.y > 0.0)\n{\n");
        }
        else
        {
            shader_addline(buffer, "if (dst.y <= ffp_light[%u].range)\n{\n", idx);
        }
        shader_addline(buffer, "dir = normalize(dir);\n");
        shader_addline(buffer, "t = dot(-dir, normalize(ffp_light[%u].direction));\n", idx);
        shader_addline(buffer, "if (t > ffp_light[%u].cos_htheta) att = 1.0;\n", idx);
        shader_addline(buffer, "else if (t <= ffp_light[%u].cos_hphi) att = 0.0;\n", idx);
        shader_addline(buffer, "else att = pow((t - ffp_light[%u].cos_hphi)"
                " / (ffp_light[%u].cos_htheta - ffp_light[%u].cos_hphi), ffp_light[%u].falloff);\n",
                idx, idx, idx, idx);
        if (legacy_lighting)
            shader_addline(buffer, "att *= dot(dst.xyz, vec3(ffp_light[%u].c_att,"
                    " ffp_light[%u].l_att, ffp_light[%u].q_att));\n",
                    idx, idx, idx);
        else
            shader_addline(buffer, "att /= dot(dst.xyz, vec3(ffp_light[%u].c_att,"
                    " ffp_light[%u].l_att, ffp_light[%u].q_att));\n",
                    idx, idx, idx);
        shader_addline(buffer, "ambient += ffp_light[%u].ambient.xyz * att;\n", idx);
        if (!settings->normal)
        {
            shader_addline(buffer, "}\n");
            continue;
        }
        shader_glsl_ffp_vertex_lighting_footer(buffer, settings, idx);
        shader_addline(buffer, "}\n");
    }

    for (i = 0; i < settings->directional_light_count; ++i, ++idx)
    {
        shader_addline(buffer, "ambient += ffp_light[%u].ambient.xyz;\n", idx);
        if (!settings->normal)
            continue;
        shader_addline(buffer, "att = 1.0;\n");
        shader_addline(buffer, "dir = normalize(ffp_light[%u].direction.xyz);\n", idx);
        shader_glsl_ffp_vertex_lighting_footer(buffer, settings, idx);
    }

    for (i = 0; i < settings->parallel_point_light_count; ++i, ++idx)
    {
        shader_addline(buffer, "ambient += ffp_light[%u].ambient.xyz;\n", idx);
        if (!settings->normal)
            continue;
        shader_addline(buffer, "att = 1.0;\n");
        shader_addline(buffer, "dir = normalize(ffp_light[%u].position.xyz);\n", idx);
        shader_glsl_ffp_vertex_lighting_footer(buffer, settings, idx);
    }

    shader_addline(buffer, "ffp_varying_diffuse.xyz = %s.xyz * ambient + %s.xyz * diffuse + %s.xyz;\n",
            ambient, diffuse, emissive);
    shader_addline(buffer, "ffp_varying_diffuse.w = %s.w;\n", diffuse);
    shader_addline(buffer, "ffp_varying_specular = %s * specular;\n", specular);
}