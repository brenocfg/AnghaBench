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

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
#define  WINED3D_PT_LINELIST 134 
#define  WINED3D_PT_LINELIST_ADJ 133 
#define  WINED3D_PT_LINESTRIP 132 
#define  WINED3D_PT_POINTLIST 131 
#define  WINED3D_PT_TRIANGLELIST 130 
#define  WINED3D_PT_TRIANGLELIST_ADJ 129 
#define  WINED3D_PT_TRIANGLESTRIP 128 
 int /*<<< orphan*/  debug_d3dprimitivetype (int) ; 

__attribute__((used)) static const char *glsl_primitive_type_from_d3d(enum wined3d_primitive_type primitive_type)
{
    switch (primitive_type)
    {
        case WINED3D_PT_POINTLIST:
            return "points";

        case WINED3D_PT_LINELIST:
            return "lines";

        case WINED3D_PT_LINESTRIP:
            return "line_strip";

        case WINED3D_PT_TRIANGLELIST:
            return "triangles";

        case WINED3D_PT_TRIANGLESTRIP:
            return "triangle_strip";

        case WINED3D_PT_LINELIST_ADJ:
            return "lines_adjacency";

        case WINED3D_PT_TRIANGLELIST_ADJ:
            return "triangles_adjacency";

        default:
            FIXME("Unhandled primitive type %s.\n", debug_d3dprimitivetype(primitive_type));
            return "";
    }
}