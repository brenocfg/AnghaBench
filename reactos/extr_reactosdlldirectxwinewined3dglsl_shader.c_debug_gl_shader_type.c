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
typedef  int GLenum ;

/* Variables and functions */
#define  GL_COMPUTE_SHADER 133 
#define  GL_FRAGMENT_SHADER 132 
#define  GL_GEOMETRY_SHADER 131 
#define  GL_TESS_CONTROL_SHADER 130 
#define  GL_TESS_EVALUATION_SHADER 129 
#define  GL_VERTEX_SHADER 128 
 char const* wine_dbg_sprintf (char*,int) ; 

__attribute__((used)) static const char *debug_gl_shader_type(GLenum type)
{
    switch (type)
    {
#define WINED3D_TO_STR(u) case u: return #u
        WINED3D_TO_STR(GL_VERTEX_SHADER);
        WINED3D_TO_STR(GL_TESS_CONTROL_SHADER);
        WINED3D_TO_STR(GL_TESS_EVALUATION_SHADER);
        WINED3D_TO_STR(GL_GEOMETRY_SHADER);
        WINED3D_TO_STR(GL_FRAGMENT_SHADER);
        WINED3D_TO_STR(GL_COMPUTE_SHADER);
#undef WINED3D_TO_STR
        default:
            return wine_dbg_sprintf("UNKNOWN(%#x)", type);
    }
}