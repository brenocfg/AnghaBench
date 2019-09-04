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
typedef  int /*<<< orphan*/  GLenum ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int) ; 
 int /*<<< orphan*/  GL_RENDERBUFFER ; 
 int /*<<< orphan*/  GL_TEXTURE_1D ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  GL_TEXTURE_3D ; 
 int /*<<< orphan*/  GL_TEXTURE_CUBE_MAP_ARB ; 
 int /*<<< orphan*/  GL_TEXTURE_RECTANGLE_ARB ; 
#define  WINED3D_GL_RES_TYPE_BUFFER 135 
#define  WINED3D_GL_RES_TYPE_COUNT 134 
#define  WINED3D_GL_RES_TYPE_RB 133 
#define  WINED3D_GL_RES_TYPE_TEX_1D 132 
#define  WINED3D_GL_RES_TYPE_TEX_2D 131 
#define  WINED3D_GL_RES_TYPE_TEX_3D 130 
#define  WINED3D_GL_RES_TYPE_TEX_CUBE 129 
#define  WINED3D_GL_RES_TYPE_TEX_RECT 128 

__attribute__((used)) static GLenum wined3d_gl_type_to_enum(enum wined3d_gl_resource_type type)
{
    switch (type)
    {
        case WINED3D_GL_RES_TYPE_TEX_1D:
            return GL_TEXTURE_1D;
        case WINED3D_GL_RES_TYPE_TEX_2D:
            return GL_TEXTURE_2D;
        case WINED3D_GL_RES_TYPE_TEX_3D:
            return GL_TEXTURE_3D;
        case WINED3D_GL_RES_TYPE_TEX_CUBE:
            return GL_TEXTURE_CUBE_MAP_ARB;
        case WINED3D_GL_RES_TYPE_TEX_RECT:
            return GL_TEXTURE_RECTANGLE_ARB;
        case WINED3D_GL_RES_TYPE_BUFFER:
            return GL_TEXTURE_2D; /* TODO: GL_TEXTURE_BUFFER. */
        case WINED3D_GL_RES_TYPE_RB:
            return GL_RENDERBUFFER;
        case WINED3D_GL_RES_TYPE_COUNT:
            break;
    }
    ERR("Unexpected GL resource type %u.\n", type);
    return 0;
}