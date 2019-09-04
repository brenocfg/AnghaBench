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
typedef  enum wined3d_format_id { ____Placeholder_wined3d_format_id } wined3d_format_id ;
typedef  int DWORD ;

/* Variables and functions */
 int WINED3DFMT_B5G5R5X1_UNORM ; 
 int WINED3DFMT_B5G6R5_UNORM ; 
 int WINED3DFMT_B8G8R8X8_UNORM ; 
 int WINED3DFMT_P8_UINT ; 
 int WINED3DFMT_UNKNOWN ; 

enum wined3d_format_id pixelformat_for_depth(DWORD depth)
{
    switch (depth)
    {
        case 8:  return WINED3DFMT_P8_UINT;
        case 15: return WINED3DFMT_B5G5R5X1_UNORM;
        case 16: return WINED3DFMT_B5G6R5_UNORM;
        case 24: return WINED3DFMT_B8G8R8X8_UNORM; /* Robots needs 24bit to be WINED3DFMT_B8G8R8X8_UNORM */
        case 32: return WINED3DFMT_B8G8R8X8_UNORM; /* EVE online and the Fur demo need 32bit AdapterDisplayMode to return WINED3DFMT_B8G8R8X8_UNORM */
        default: return WINED3DFMT_UNKNOWN;
    }
}