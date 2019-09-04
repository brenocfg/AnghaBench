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
typedef  enum wined3d_resource_type { ____Placeholder_wined3d_resource_type } wined3d_resource_type ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int) ; 
#define  WINED3D_RTYPE_BUFFER 132 
#define  WINED3D_RTYPE_NONE 131 
#define  WINED3D_RTYPE_TEXTURE_1D 130 
#define  WINED3D_RTYPE_TEXTURE_2D 129 
#define  WINED3D_RTYPE_TEXTURE_3D 128 

const char *debug_d3dresourcetype(enum wined3d_resource_type resource_type)
{
    switch (resource_type)
    {
#define WINED3D_TO_STR(x) case x: return #x
        WINED3D_TO_STR(WINED3D_RTYPE_NONE);
        WINED3D_TO_STR(WINED3D_RTYPE_BUFFER);
        WINED3D_TO_STR(WINED3D_RTYPE_TEXTURE_1D);
        WINED3D_TO_STR(WINED3D_RTYPE_TEXTURE_2D);
        WINED3D_TO_STR(WINED3D_RTYPE_TEXTURE_3D);
#undef WINED3D_TO_STR
        default:
            FIXME("Unrecognized resource type %#x.\n", resource_type);
            return "unrecognized";
    }
}