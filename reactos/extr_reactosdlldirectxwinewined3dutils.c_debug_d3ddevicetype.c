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
typedef  enum wined3d_device_type { ____Placeholder_wined3d_device_type } wined3d_device_type ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int) ; 
#define  WINED3D_DEVICE_TYPE_HAL 130 
#define  WINED3D_DEVICE_TYPE_REF 129 
#define  WINED3D_DEVICE_TYPE_SW 128 

const char *debug_d3ddevicetype(enum wined3d_device_type device_type)
{
    switch (device_type)
    {
#define DEVTYPE_TO_STR(dev) case dev: return #dev
        DEVTYPE_TO_STR(WINED3D_DEVICE_TYPE_HAL);
        DEVTYPE_TO_STR(WINED3D_DEVICE_TYPE_REF);
        DEVTYPE_TO_STR(WINED3D_DEVICE_TYPE_SW);
#undef DEVTYPE_TO_STR
        default:
            FIXME("Unrecognized device type %#x.\n", device_type);
            return "unrecognized";
    }
}