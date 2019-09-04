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
typedef  enum wined3d_shader_type { ____Placeholder_wined3d_shader_type } wined3d_shader_type ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int) ; 
#define  WINED3D_SHADER_TYPE_COMPUTE 133 
#define  WINED3D_SHADER_TYPE_DOMAIN 132 
#define  WINED3D_SHADER_TYPE_GEOMETRY 131 
#define  WINED3D_SHADER_TYPE_HULL 130 
#define  WINED3D_SHADER_TYPE_PIXEL 129 
#define  WINED3D_SHADER_TYPE_VERTEX 128 

const char *debug_shader_type(enum wined3d_shader_type type)
{
    switch(type)
    {
#define WINED3D_TO_STR(type) case type: return #type
        WINED3D_TO_STR(WINED3D_SHADER_TYPE_PIXEL);
        WINED3D_TO_STR(WINED3D_SHADER_TYPE_VERTEX);
        WINED3D_TO_STR(WINED3D_SHADER_TYPE_GEOMETRY);
        WINED3D_TO_STR(WINED3D_SHADER_TYPE_HULL);
        WINED3D_TO_STR(WINED3D_SHADER_TYPE_DOMAIN);
        WINED3D_TO_STR(WINED3D_SHADER_TYPE_COMPUTE);
#undef WINED3D_TO_STR
        default:
            FIXME("Unrecognized shader type %#x.\n", type);
            return "unrecognized";
    }
}