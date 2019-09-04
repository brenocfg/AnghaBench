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
 int /*<<< orphan*/  FIXME (char*,int) ; 
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

const char *debug_d3dprimitivetype(enum wined3d_primitive_type primitive_type)
{
    switch (primitive_type)
    {
#define PRIM_TO_STR(prim) case prim: return #prim
        PRIM_TO_STR(WINED3D_PT_UNDEFINED);
        PRIM_TO_STR(WINED3D_PT_POINTLIST);
        PRIM_TO_STR(WINED3D_PT_LINELIST);
        PRIM_TO_STR(WINED3D_PT_LINESTRIP);
        PRIM_TO_STR(WINED3D_PT_TRIANGLELIST);
        PRIM_TO_STR(WINED3D_PT_TRIANGLESTRIP);
        PRIM_TO_STR(WINED3D_PT_TRIANGLEFAN);
        PRIM_TO_STR(WINED3D_PT_LINELIST_ADJ);
        PRIM_TO_STR(WINED3D_PT_LINESTRIP_ADJ);
        PRIM_TO_STR(WINED3D_PT_TRIANGLELIST_ADJ);
        PRIM_TO_STR(WINED3D_PT_TRIANGLESTRIP_ADJ);
        PRIM_TO_STR(WINED3D_PT_PATCH);
#undef  PRIM_TO_STR
        default:
            FIXME("Unrecognized primitive type %#x.\n", primitive_type);
            return "unrecognized";
    }
}