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
typedef  enum wined3d_ffp_ps_fog_mode { ____Placeholder_wined3d_ffp_ps_fog_mode } wined3d_ffp_ps_fog_mode ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int) ; 
#define  WINED3D_FFP_PS_FOG_EXP 131 
#define  WINED3D_FFP_PS_FOG_EXP2 130 
#define  WINED3D_FFP_PS_FOG_LINEAR 129 
#define  WINED3D_FFP_PS_FOG_OFF 128 
 scalar_t__ needs_legacy_glsl_syntax (struct wined3d_gl_info const*) ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,...) ; 

__attribute__((used)) static void shader_glsl_generate_fog_code(struct wined3d_string_buffer *buffer,
        const struct wined3d_gl_info *gl_info, enum wined3d_ffp_ps_fog_mode mode)
{
    const char *output = needs_legacy_glsl_syntax(gl_info) ? "gl_FragData[0]" : "ps_out0";

    switch (mode)
    {
        case WINED3D_FFP_PS_FOG_OFF:
            return;

        case WINED3D_FFP_PS_FOG_LINEAR:
            shader_addline(buffer, "float fog = (ffp_fog.end - ffp_varying_fogcoord) * ffp_fog.scale;\n");
            break;

        case WINED3D_FFP_PS_FOG_EXP:
            shader_addline(buffer, "float fog = exp(-ffp_fog.density * ffp_varying_fogcoord);\n");
            break;

        case WINED3D_FFP_PS_FOG_EXP2:
            shader_addline(buffer, "float fog = exp(-ffp_fog.density * ffp_fog.density"
                    " * ffp_varying_fogcoord * ffp_varying_fogcoord);\n");
            break;

        default:
            ERR("Invalid fog mode %#x.\n", mode);
            return;
    }

    shader_addline(buffer, "%s.xyz = mix(ffp_fog.color.xyz, %s.xyz, clamp(fog, 0.0, 1.0));\n",
            output, output);
}