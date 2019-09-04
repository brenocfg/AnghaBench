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
typedef  enum wined3d_primitive_type { ____Placeholder_wined3d_primitive_type } wined3d_primitive_type ;
typedef  unsigned int GLenum ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 unsigned int GL_LINES ; 
 unsigned int GL_LINES_ADJACENCY_ARB ; 
 unsigned int GL_LINE_STRIP ; 
 unsigned int GL_LINE_STRIP_ADJACENCY_ARB ; 
 unsigned int GL_PATCHES ; 
 unsigned int GL_POINTS ; 
 unsigned int GL_TRIANGLES ; 
 unsigned int GL_TRIANGLES_ADJACENCY_ARB ; 
 unsigned int GL_TRIANGLE_FAN ; 
 unsigned int GL_TRIANGLE_STRIP ; 
 unsigned int GL_TRIANGLE_STRIP_ADJACENCY_ARB ; 
#define  WINED3D_PT_LINELIST 139 
#define  WINED3D_PT_LINELIST_ADJ 138 
#define  WINED3D_PT_LINESTRIP 137 
#define  WINED3D_PT_LINESTRIP_ADJ 136 
#define  WINED3D_PT_PATCH 135 
#define  WINED3D_PT_POINTLIST 134 
#define  WINED3D_PT_TRIANGLEFAN 133 
#define  WINED3D_PT_TRIANGLELIST 132 
#define  WINED3D_PT_TRIANGLELIST_ADJ 131 
#define  WINED3D_PT_TRIANGLESTRIP 130 
#define  WINED3D_PT_TRIANGLESTRIP_ADJ 129 
#define  WINED3D_PT_UNDEFINED 128 
 int /*<<< orphan*/  debug_d3dprimitivetype (int) ; 

GLenum gl_primitive_type_from_d3d(enum wined3d_primitive_type primitive_type)
{
    switch (primitive_type)
    {
        case WINED3D_PT_POINTLIST:
            return GL_POINTS;

        case WINED3D_PT_LINELIST:
            return GL_LINES;

        case WINED3D_PT_LINESTRIP:
            return GL_LINE_STRIP;

        case WINED3D_PT_TRIANGLELIST:
            return GL_TRIANGLES;

        case WINED3D_PT_TRIANGLESTRIP:
            return GL_TRIANGLE_STRIP;

        case WINED3D_PT_TRIANGLEFAN:
            return GL_TRIANGLE_FAN;

        case WINED3D_PT_LINELIST_ADJ:
            return GL_LINES_ADJACENCY_ARB;

        case WINED3D_PT_LINESTRIP_ADJ:
            return GL_LINE_STRIP_ADJACENCY_ARB;

        case WINED3D_PT_TRIANGLELIST_ADJ:
            return GL_TRIANGLES_ADJACENCY_ARB;

        case WINED3D_PT_TRIANGLESTRIP_ADJ:
            return GL_TRIANGLE_STRIP_ADJACENCY_ARB;

        case WINED3D_PT_PATCH:
            return GL_PATCHES;

        default:
            FIXME("Unhandled primitive type %s.\n", debug_d3dprimitivetype(primitive_type));
        case WINED3D_PT_UNDEFINED:
            return ~0u;
    }
}