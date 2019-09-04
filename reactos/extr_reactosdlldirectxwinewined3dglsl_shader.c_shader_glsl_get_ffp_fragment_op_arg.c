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
typedef  int DWORD ;

/* Variables and functions */
 int ARG_UNUSED ; 
 int WINED3DTA_ALPHAREPLICATE ; 
 int WINED3DTA_COMPLEMENT ; 
#define  WINED3DTA_CONSTANT 134 
#define  WINED3DTA_CURRENT 133 
#define  WINED3DTA_DIFFUSE 132 
 int WINED3DTA_SELECTMASK ; 
#define  WINED3DTA_SPECULAR 131 
#define  WINED3DTA_TEMP 130 
#define  WINED3DTA_TEXTURE 129 
#define  WINED3DTA_TFACTOR 128 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,int,char const*) ; 

__attribute__((used)) static const char *shader_glsl_get_ffp_fragment_op_arg(struct wined3d_string_buffer *buffer,
        DWORD argnum, unsigned int stage, DWORD arg)
{
    const char *ret;

    if (arg == ARG_UNUSED)
        return "<unused arg>";

    switch (arg & WINED3DTA_SELECTMASK)
    {
        case WINED3DTA_DIFFUSE:
            ret = "ffp_varying_diffuse";
            break;

        case WINED3DTA_CURRENT:
            ret = "ret";
            break;

        case WINED3DTA_TEXTURE:
            switch (stage)
            {
                case 0: ret = "tex0"; break;
                case 1: ret = "tex1"; break;
                case 2: ret = "tex2"; break;
                case 3: ret = "tex3"; break;
                case 4: ret = "tex4"; break;
                case 5: ret = "tex5"; break;
                case 6: ret = "tex6"; break;
                case 7: ret = "tex7"; break;
                default:
                    ret = "<invalid texture>";
                    break;
            }
            break;

        case WINED3DTA_TFACTOR:
            ret = "tex_factor";
            break;

        case WINED3DTA_SPECULAR:
            ret = "ffp_varying_specular";
            break;

        case WINED3DTA_TEMP:
            ret = "temp_reg";
            break;

        case WINED3DTA_CONSTANT:
            switch (stage)
            {
                case 0: ret = "tss_const0"; break;
                case 1: ret = "tss_const1"; break;
                case 2: ret = "tss_const2"; break;
                case 3: ret = "tss_const3"; break;
                case 4: ret = "tss_const4"; break;
                case 5: ret = "tss_const5"; break;
                case 6: ret = "tss_const6"; break;
                case 7: ret = "tss_const7"; break;
                default:
                    ret = "<invalid constant>";
                    break;
            }
            break;

        default:
            return "<unhandled arg>";
    }

    if (arg & WINED3DTA_COMPLEMENT)
    {
        shader_addline(buffer, "arg%u = vec4(1.0) - %s;\n", argnum, ret);
        if (argnum == 0)
            ret = "arg0";
        else if (argnum == 1)
            ret = "arg1";
        else if (argnum == 2)
            ret = "arg2";
    }

    if (arg & WINED3DTA_ALPHAREPLICATE)
    {
        shader_addline(buffer, "arg%u = vec4(%s.w);\n", argnum, ret);
        if (argnum == 0)
            ret = "arg0";
        else if (argnum == 1)
            ret = "arg1";
        else if (argnum == 2)
            ret = "arg2";
    }

    return ret;
}