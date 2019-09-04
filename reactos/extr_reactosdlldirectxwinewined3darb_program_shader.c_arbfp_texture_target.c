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
typedef  enum wined3d_gl_resource_type { ____Placeholder_wined3d_gl_resource_type } wined3d_gl_resource_type ;

/* Variables and functions */
#define  WINED3D_GL_RES_TYPE_TEX_1D 132 
#define  WINED3D_GL_RES_TYPE_TEX_2D 131 
#define  WINED3D_GL_RES_TYPE_TEX_3D 130 
#define  WINED3D_GL_RES_TYPE_TEX_CUBE 129 
#define  WINED3D_GL_RES_TYPE_TEX_RECT 128 

__attribute__((used)) static const char *arbfp_texture_target(enum wined3d_gl_resource_type type)
{
    switch(type)
    {
        case WINED3D_GL_RES_TYPE_TEX_1D:
            return "1D";
        case WINED3D_GL_RES_TYPE_TEX_2D:
            return "2D";
        case WINED3D_GL_RES_TYPE_TEX_3D:
            return "3D";
        case WINED3D_GL_RES_TYPE_TEX_CUBE:
            return "CUBE";
        case WINED3D_GL_RES_TYPE_TEX_RECT:
            return "RECT";
        default:
            return "unexpected_resource_type";
    }
}