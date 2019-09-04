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
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int) ; 
#define  WINED3D_LOCATION_BUFFER 136 
#define  WINED3D_LOCATION_DISCARDED 135 
#define  WINED3D_LOCATION_DRAWABLE 134 
#define  WINED3D_LOCATION_RB_MULTISAMPLE 133 
#define  WINED3D_LOCATION_RB_RESOLVED 132 
#define  WINED3D_LOCATION_SYSMEM 131 
#define  WINED3D_LOCATION_TEXTURE_RGB 130 
#define  WINED3D_LOCATION_TEXTURE_SRGB 129 
#define  WINED3D_LOCATION_USER_MEMORY 128 
 int WINED3D_RESOURCE_ACCESS_CPU ; 
 int WINED3D_RESOURCE_ACCESS_GPU ; 

__attribute__((used)) static DWORD wined3d_resource_access_from_location(DWORD location)
{
    switch (location)
    {
        case WINED3D_LOCATION_DISCARDED:
            return 0;

        case WINED3D_LOCATION_SYSMEM:
        case WINED3D_LOCATION_USER_MEMORY:
            return WINED3D_RESOURCE_ACCESS_CPU;

        case WINED3D_LOCATION_BUFFER:
        case WINED3D_LOCATION_DRAWABLE:
        case WINED3D_LOCATION_TEXTURE_RGB:
        case WINED3D_LOCATION_TEXTURE_SRGB:
        case WINED3D_LOCATION_RB_MULTISAMPLE:
        case WINED3D_LOCATION_RB_RESOLVED:
            return WINED3D_RESOURCE_ACCESS_GPU;

        default:
            FIXME("Unhandled location %#x.\n", location);
            return 0;
    }
}