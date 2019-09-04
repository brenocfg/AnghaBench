#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct attrib_info   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wined3d_string_buffer {int /*<<< orphan*/  buffer; } ;
struct TYPE_3__ {unsigned int user_clip_distances; int /*<<< orphan*/  glsl_varyings; } ;
struct wined3d_gl_info {int /*<<< orphan*/ * supported; TYPE_1__ limits; } ;
struct wined3d_ffp_vs_settings {unsigned int swizzle_map; int* texgen; unsigned int texcoords; unsigned int vertexblends; int fog_mode; scalar_t__ per_vertex_point_size; scalar_t__ point_size; scalar_t__ transformed; int /*<<< orphan*/  ortho_fog; scalar_t__ normalize; scalar_t__ vb_indices; int /*<<< orphan*/  sw_blending; scalar_t__ normal; scalar_t__ clipping; scalar_t__ flatshading; } ;
struct shader_glsl_priv {scalar_t__ legacy_lighting; struct wined3d_string_buffer shader_buffer; } ;
struct attrib_info {char const* type; char const* name; } ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 size_t ARB_CLIP_CONTROL ; 
 unsigned int ARRAY_SIZE (TYPE_2__ const*) ; 
 int /*<<< orphan*/  ERR (char*,int) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_VERTEX_SHADER ; 
 int /*<<< orphan*/  MAX_ACTIVE_LIGHTS ; 
 unsigned int MAX_TEXTURES ; 
 int /*<<< orphan*/  MAX_VERTEX_INDEX_BLENDS ; 
#define  WINED3DTSS_TCI_CAMERASPACENORMAL 136 
#define  WINED3DTSS_TCI_CAMERASPACEPOSITION 135 
#define  WINED3DTSS_TCI_CAMERASPACEREFLECTIONVECTOR 134 
#define  WINED3DTSS_TCI_PASSTHRU 133 
#define  WINED3DTSS_TCI_SPHEREMAP 132 
 unsigned int WINED3D_FFP_ATTRIBS_COUNT ; 
 scalar_t__ WINED3D_FFP_TEXCOORD0 ; 
#define  WINED3D_FFP_VS_FOG_DEPTH 131 
#define  WINED3D_FFP_VS_FOG_FOGCOORD 130 
#define  WINED3D_FFP_VS_FOG_OFF 129 
#define  WINED3D_FFP_VS_FOG_RANGE 128 
 int /*<<< orphan*/  declare_out_varying (struct wined3d_gl_info const*,struct wined3d_string_buffer*,scalar_t__,char*,...) ; 
 int /*<<< orphan*/  get_attribute_keyword (struct wined3d_gl_info const*) ; 
 int /*<<< orphan*/  glCreateShader (int /*<<< orphan*/ ) ; 
 scalar_t__ needs_legacy_glsl_syntax (struct wined3d_gl_info const*) ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,...) ; 
 int /*<<< orphan*/  shader_glsl_add_version_declaration (struct wined3d_string_buffer*,struct wined3d_gl_info const*) ; 
 int /*<<< orphan*/  shader_glsl_compile (struct wined3d_gl_info const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_glsl_ffp_vertex_lighting (struct wined3d_string_buffer*,struct wined3d_ffp_vs_settings const*,scalar_t__) ; 
 scalar_t__ shader_glsl_use_explicit_attrib_location (struct wined3d_gl_info const*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 
 int /*<<< orphan*/  string_buffer_clear (struct wined3d_string_buffer*) ; 
 int /*<<< orphan*/  wined3d_max_compat_varyings (struct wined3d_gl_info const*) ; 

__attribute__((used)) static GLuint shader_glsl_generate_ffp_vertex_shader(struct shader_glsl_priv *priv,
        const struct wined3d_ffp_vs_settings *settings, const struct wined3d_gl_info *gl_info)
{
    static const struct attrib_info
    {
        const char type[6];
        const char name[24];
    }
    attrib_info[] =
    {
        {"vec4", "ffp_attrib_position"},        /* WINED3D_FFP_POSITION */
        {"vec4", "ffp_attrib_blendweight"},     /* WINED3D_FFP_BLENDWEIGHT */
        {"vec4", "ffp_attrib_blendindices"},    /* WINED3D_FFP_BLENDINDICES */
        {"vec3", "ffp_attrib_normal"},          /* WINED3D_FFP_NORMAL */
        {"float", "ffp_attrib_psize"},          /* WINED3D_FFP_PSIZE */
        {"vec4", "ffp_attrib_diffuse"},         /* WINED3D_FFP_DIFFUSE */
        {"vec4", "ffp_attrib_specular"},        /* WINED3D_FFP_SPECULAR */
    };
    const BOOL legacy_syntax = needs_legacy_glsl_syntax(gl_info);
    struct wined3d_string_buffer *buffer = &priv->shader_buffer;
    BOOL output_legacy_fogcoord = legacy_syntax;
    BOOL legacy_lighting = priv->legacy_lighting;
    GLuint shader_obj;
    unsigned int i;
    char var[64];

    string_buffer_clear(buffer);

    shader_glsl_add_version_declaration(buffer, gl_info);

    if (shader_glsl_use_explicit_attrib_location(gl_info))
        shader_addline(buffer, "#extension GL_ARB_explicit_attrib_location : enable\n");

    for (i = 0; i < WINED3D_FFP_ATTRIBS_COUNT; ++i)
    {
        const char *type = i < ARRAY_SIZE(attrib_info) ? attrib_info[i].type : "vec4";

        if (shader_glsl_use_explicit_attrib_location(gl_info))
            shader_addline(buffer, "layout(location = %u) ", i);
        shader_addline(buffer, "%s %s vs_in%u;\n", get_attribute_keyword(gl_info), type, i);
    }
    shader_addline(buffer, "\n");

    shader_addline(buffer, "uniform mat4 ffp_modelview_matrix[%u];\n", MAX_VERTEX_INDEX_BLENDS);
    shader_addline(buffer, "uniform mat3 ffp_normal_matrix[%u];\n", MAX_VERTEX_INDEX_BLENDS);
    shader_addline(buffer, "uniform mat4 ffp_projection_matrix;\n");
    shader_addline(buffer, "uniform mat4 ffp_texture_matrix[%u];\n", MAX_TEXTURES);

    shader_addline(buffer, "uniform struct\n{\n");
    shader_addline(buffer, "    vec4 emissive;\n");
    shader_addline(buffer, "    vec4 ambient;\n");
    shader_addline(buffer, "    vec4 diffuse;\n");
    shader_addline(buffer, "    vec4 specular;\n");
    shader_addline(buffer, "    float shininess;\n");
    shader_addline(buffer, "} ffp_material;\n");

    shader_addline(buffer, "uniform vec3 ffp_light_ambient;\n");
    shader_addline(buffer, "uniform struct\n{\n");
    shader_addline(buffer, "    vec4 diffuse;\n");
    shader_addline(buffer, "    vec4 specular;\n");
    shader_addline(buffer, "    vec4 ambient;\n");
    shader_addline(buffer, "    vec4 position;\n");
    shader_addline(buffer, "    vec3 direction;\n");
    shader_addline(buffer, "    float range;\n");
    shader_addline(buffer, "    float falloff;\n");
    shader_addline(buffer, "    float c_att;\n");
    shader_addline(buffer, "    float l_att;\n");
    shader_addline(buffer, "    float q_att;\n");
    shader_addline(buffer, "    float cos_htheta;\n");
    shader_addline(buffer, "    float cos_hphi;\n");
    shader_addline(buffer, "} ffp_light[%u];\n", MAX_ACTIVE_LIGHTS);

    if (settings->point_size)
    {
        shader_addline(buffer, "uniform struct\n{\n");
        shader_addline(buffer, "    float size;\n");
        shader_addline(buffer, "    float size_min;\n");
        shader_addline(buffer, "    float size_max;\n");
        shader_addline(buffer, "    float c_att;\n");
        shader_addline(buffer, "    float l_att;\n");
        shader_addline(buffer, "    float q_att;\n");
        shader_addline(buffer, "} ffp_point;\n");
    }

    if (legacy_syntax)
    {
        shader_addline(buffer, "vec4 ffp_varying_diffuse;\n");
        shader_addline(buffer, "vec4 ffp_varying_specular;\n");
        shader_addline(buffer, "vec4 ffp_varying_texcoord[%u];\n", MAX_TEXTURES);
        shader_addline(buffer, "float ffp_varying_fogcoord;\n");
    }
    else
    {
        if (settings->clipping)
            shader_addline(buffer, "uniform vec4 clip_planes[%u];\n", gl_info->limits.user_clip_distances);

        declare_out_varying(gl_info, buffer, settings->flatshading, "vec4 ffp_varying_diffuse;\n");
        declare_out_varying(gl_info, buffer, settings->flatshading, "vec4 ffp_varying_specular;\n");
        declare_out_varying(gl_info, buffer, FALSE, "vec4 ffp_varying_texcoord[%u];\n", MAX_TEXTURES);
        declare_out_varying(gl_info, buffer, FALSE, "float ffp_varying_fogcoord;\n");
    }

    shader_addline(buffer, "\nvoid main()\n{\n");
    shader_addline(buffer, "float m;\n");
    shader_addline(buffer, "vec3 r;\n");

    for (i = 0; i < ARRAY_SIZE(attrib_info); ++i)
    {
        if (attrib_info[i].name[0])
            shader_addline(buffer, "%s %s = vs_in%u%s;\n", attrib_info[i].type, attrib_info[i].name,
                    i, settings->swizzle_map & (1u << i) ? ".zyxw" : "");
    }
    for (i = 0; i < MAX_TEXTURES; ++i)
    {
        unsigned int coord_idx = settings->texgen[i] & 0x0000ffff;
        if ((settings->texgen[i] & 0xffff0000) == WINED3DTSS_TCI_PASSTHRU
                && settings->texcoords & (1u << i))
            shader_addline(buffer, "vec4 ffp_attrib_texcoord%u = vs_in%u;\n", i, coord_idx + WINED3D_FFP_TEXCOORD0);
    }

    shader_addline(buffer, "ffp_attrib_blendweight[%u] = 1.0;\n", settings->vertexblends);

    if (settings->transformed)
    {
        shader_addline(buffer, "vec4 ec_pos = vec4(ffp_attrib_position.xyz, 1.0);\n");
        shader_addline(buffer, "gl_Position = ffp_projection_matrix * ec_pos;\n");
        shader_addline(buffer, "if (ffp_attrib_position.w != 0.0) gl_Position /= ffp_attrib_position.w;\n");
    }
    else
    {
        if (!settings->sw_blending)
        {
            for (i = 0; i < settings->vertexblends; ++i)
                shader_addline(buffer, "ffp_attrib_blendweight[%u] -= ffp_attrib_blendweight[%u];\n", settings->vertexblends, i);

            shader_addline(buffer, "vec4 ec_pos = vec4(0.0);\n");
            for (i = 0; i < settings->vertexblends + 1; ++i)
            {
                sprintf(var, settings->vb_indices ? "int(ffp_attrib_blendindices[%u] + 0.1)" : "%u", i);
                shader_addline(buffer, "ec_pos += ffp_attrib_blendweight[%u] * (ffp_modelview_matrix[%s] * ffp_attrib_position);\n", i, var);
            }
        }
        else
        {
            shader_addline(buffer, "vec4 ec_pos = ffp_attrib_position;\n");
        }

        shader_addline(buffer, "gl_Position = ffp_projection_matrix * ec_pos;\n");
        if (settings->clipping)
        {
            if (legacy_syntax)
                shader_addline(buffer, "gl_ClipVertex = ec_pos;\n");
            else
                for (i = 0; i < gl_info->limits.user_clip_distances; ++i)
                    shader_addline(buffer, "gl_ClipDistance[%u] = dot(ec_pos, clip_planes[%u]);\n", i, i);
        }
        shader_addline(buffer, "ec_pos /= ec_pos.w;\n");
    }

    shader_addline(buffer, "vec3 normal = vec3(0.0);\n");
    if (settings->normal)
    {
        if (!settings->sw_blending)
        {
            for (i = 0; i < settings->vertexblends + 1; ++i)
            {
                sprintf(var, settings->vb_indices ? "int(ffp_attrib_blendindices[%u] + 0.1)" : "%u", i);
                shader_addline(buffer, "normal += ffp_attrib_blendweight[%u] * (ffp_normal_matrix[%s] * ffp_attrib_normal);\n", i, var);
            }
        }
        else
        {
            shader_addline(buffer, "normal = ffp_attrib_normal;\n");
        }

        if (settings->normalize)
            shader_addline(buffer, "normal = normalize(normal);\n");
    }

    shader_glsl_ffp_vertex_lighting(buffer, settings, legacy_lighting);
    if (legacy_syntax)
    {
        shader_addline(buffer, "gl_FrontColor = ffp_varying_diffuse;\n");
        shader_addline(buffer, "gl_FrontSecondaryColor = ffp_varying_specular;\n");
    }
    else
    {
        shader_addline(buffer, "ffp_varying_diffuse = clamp(ffp_varying_diffuse, 0.0, 1.0);\n");
        shader_addline(buffer, "ffp_varying_specular = clamp(ffp_varying_specular, 0.0, 1.0);\n");
    }

    for (i = 0; i < MAX_TEXTURES; ++i)
    {
        BOOL output_legacy_texcoord = legacy_syntax;

        switch (settings->texgen[i] & 0xffff0000)
        {
            case WINED3DTSS_TCI_PASSTHRU:
                if (settings->texcoords & (1u << i))
                    shader_addline(buffer, "ffp_varying_texcoord[%u] = ffp_texture_matrix[%u] * ffp_attrib_texcoord%u;\n",
                            i, i, i);
                else if (gl_info->limits.glsl_varyings >= wined3d_max_compat_varyings(gl_info))
                    shader_addline(buffer, "ffp_varying_texcoord[%u] = vec4(0.0);\n", i);
                else
                    output_legacy_texcoord = FALSE;
                break;

            case WINED3DTSS_TCI_CAMERASPACENORMAL:
                shader_addline(buffer, "ffp_varying_texcoord[%u] = ffp_texture_matrix[%u] * vec4(normal, 1.0);\n", i, i);
                break;

            case WINED3DTSS_TCI_CAMERASPACEPOSITION:
                shader_addline(buffer, "ffp_varying_texcoord[%u] = ffp_texture_matrix[%u] * ec_pos;\n", i, i);
                break;

            case WINED3DTSS_TCI_CAMERASPACEREFLECTIONVECTOR:
                shader_addline(buffer, "ffp_varying_texcoord[%u] = ffp_texture_matrix[%u]"
                        " * vec4(reflect(normalize(ec_pos.xyz), normal), 1.0);\n", i, i);
                break;

            case WINED3DTSS_TCI_SPHEREMAP:
                shader_addline(buffer, "r = reflect(normalize(ec_pos.xyz), normal);\n");
                shader_addline(buffer, "m = 2.0 * length(vec3(r.x, r.y, r.z + 1.0));\n");
                shader_addline(buffer, "ffp_varying_texcoord[%u] = ffp_texture_matrix[%u]"
                        " * vec4(r.x / m + 0.5, r.y / m + 0.5, 0.0, 1.0);\n", i, i);
                break;

            default:
                ERR("Unhandled texgen %#x.\n", settings->texgen[i]);
                break;
        }
        if (output_legacy_texcoord)
            shader_addline(buffer, "gl_TexCoord[%u] = ffp_varying_texcoord[%u];\n", i, i);
    }

    switch (settings->fog_mode)
    {
        case WINED3D_FFP_VS_FOG_OFF:
            output_legacy_fogcoord = FALSE;
            break;

        case WINED3D_FFP_VS_FOG_FOGCOORD:
            shader_addline(buffer, "ffp_varying_fogcoord = ffp_attrib_specular.w * 255.0;\n");
            break;

        case WINED3D_FFP_VS_FOG_RANGE:
            shader_addline(buffer, "ffp_varying_fogcoord = length(ec_pos.xyz);\n");
            break;

        case WINED3D_FFP_VS_FOG_DEPTH:
            if (settings->ortho_fog)
            {
                if (gl_info->supported[ARB_CLIP_CONTROL])
                    shader_addline(buffer, "ffp_varying_fogcoord = gl_Position.z;\n");
                else
                    /* Need to undo the [0.0 - 1.0] -> [-1.0 - 1.0] transformation from D3D to GL coordinates. */
                    shader_addline(buffer, "ffp_varying_fogcoord = gl_Position.z * 0.5 + 0.5;\n");
            }
            else if (settings->transformed)
            {
                shader_addline(buffer, "ffp_varying_fogcoord = ec_pos.z;\n");
            }
            else
            {
                shader_addline(buffer, "ffp_varying_fogcoord = abs(ec_pos.z);\n");
            }
            break;

        default:
            ERR("Unhandled fog mode %#x.\n", settings->fog_mode);
            break;
    }
    if (output_legacy_fogcoord)
        shader_addline(buffer, "gl_FogFragCoord = ffp_varying_fogcoord;\n");

    if (settings->point_size)
    {
        shader_addline(buffer, "gl_PointSize = %s / sqrt(ffp_point.c_att"
                " + ffp_point.l_att * length(ec_pos.xyz)"
                " + ffp_point.q_att * dot(ec_pos.xyz, ec_pos.xyz));\n",
                settings->per_vertex_point_size ? "ffp_attrib_psize" : "ffp_point.size");
        shader_addline(buffer, "gl_PointSize = clamp(gl_PointSize, ffp_point.size_min, ffp_point.size_max);\n");
    }

    shader_addline(buffer, "}\n");

    shader_obj = GL_EXTCALL(glCreateShader(GL_VERTEX_SHADER));
    shader_glsl_compile(gl_info, shader_obj, buffer->buffer);

    return shader_obj;
}