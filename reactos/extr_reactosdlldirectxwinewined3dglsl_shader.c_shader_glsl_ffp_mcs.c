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
typedef  enum wined3d_material_color_source { ____Placeholder_wined3d_material_color_source } wined3d_material_color_source ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int) ; 
#define  WINED3D_MCS_COLOR1 130 
#define  WINED3D_MCS_COLOR2 129 
#define  WINED3D_MCS_MATERIAL 128 

__attribute__((used)) static const char *shader_glsl_ffp_mcs(enum wined3d_material_color_source mcs, const char *material)
{
    switch (mcs)
    {
        case WINED3D_MCS_MATERIAL:
            return material;
        case WINED3D_MCS_COLOR1:
            return "ffp_attrib_diffuse";
        case WINED3D_MCS_COLOR2:
            return "ffp_attrib_specular";
        default:
            ERR("Invalid material color source %#x.\n", mcs);
            return "<invalid>";
    }
}