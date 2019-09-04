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
typedef  enum wined3d_texture_filter_type { ____Placeholder_wined3d_texture_filter_type } wined3d_texture_filter_type ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int) ; 
#define  WINED3D_TEXF_ANISOTROPIC 135 
#define  WINED3D_TEXF_FLAT_CUBIC 134 
#define  WINED3D_TEXF_GAUSSIAN_CUBIC 133 
#define  WINED3D_TEXF_GAUSSIAN_QUAD 132 
#define  WINED3D_TEXF_LINEAR 131 
#define  WINED3D_TEXF_NONE 130 
#define  WINED3D_TEXF_POINT 129 
#define  WINED3D_TEXF_PYRAMIDAL_QUAD 128 

const char *debug_d3dtexturefiltertype(enum wined3d_texture_filter_type filter_type)
{
    switch (filter_type)
    {
#define D3DTEXTUREFILTERTYPE_TO_STR(u) case u: return #u
        D3DTEXTUREFILTERTYPE_TO_STR(WINED3D_TEXF_NONE);
        D3DTEXTUREFILTERTYPE_TO_STR(WINED3D_TEXF_POINT);
        D3DTEXTUREFILTERTYPE_TO_STR(WINED3D_TEXF_LINEAR);
        D3DTEXTUREFILTERTYPE_TO_STR(WINED3D_TEXF_ANISOTROPIC);
        D3DTEXTUREFILTERTYPE_TO_STR(WINED3D_TEXF_FLAT_CUBIC);
        D3DTEXTUREFILTERTYPE_TO_STR(WINED3D_TEXF_GAUSSIAN_CUBIC);
        D3DTEXTUREFILTERTYPE_TO_STR(WINED3D_TEXF_PYRAMIDAL_QUAD);
        D3DTEXTUREFILTERTYPE_TO_STR(WINED3D_TEXF_GAUSSIAN_QUAD);
#undef D3DTEXTUREFILTERTYPE_TO_STR
        default:
            FIXME("Unrecognized texture filter type 0x%08x.\n", filter_type);
            return "unrecognized";
    }
}