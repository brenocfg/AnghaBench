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
typedef  enum wined3d_sampler_state { ____Placeholder_wined3d_sampler_state } wined3d_sampler_state ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int) ; 
#define  WINED3D_SAMP_ADDRESS_U 140 
#define  WINED3D_SAMP_ADDRESS_V 139 
#define  WINED3D_SAMP_ADDRESS_W 138 
#define  WINED3D_SAMP_BORDER_COLOR 137 
#define  WINED3D_SAMP_DMAP_OFFSET 136 
#define  WINED3D_SAMP_ELEMENT_INDEX 135 
#define  WINED3D_SAMP_MAG_FILTER 134 
#define  WINED3D_SAMP_MAX_ANISOTROPY 133 
#define  WINED3D_SAMP_MAX_MIP_LEVEL 132 
#define  WINED3D_SAMP_MIN_FILTER 131 
#define  WINED3D_SAMP_MIPMAP_LOD_BIAS 130 
#define  WINED3D_SAMP_MIP_FILTER 129 
#define  WINED3D_SAMP_SRGB_TEXTURE 128 

const char *debug_d3dsamplerstate(enum wined3d_sampler_state state)
{
    switch (state)
    {
#define D3DSTATE_TO_STR(u) case u: return #u
        D3DSTATE_TO_STR(WINED3D_SAMP_BORDER_COLOR);
        D3DSTATE_TO_STR(WINED3D_SAMP_ADDRESS_U);
        D3DSTATE_TO_STR(WINED3D_SAMP_ADDRESS_V);
        D3DSTATE_TO_STR(WINED3D_SAMP_ADDRESS_W);
        D3DSTATE_TO_STR(WINED3D_SAMP_MAG_FILTER);
        D3DSTATE_TO_STR(WINED3D_SAMP_MIN_FILTER);
        D3DSTATE_TO_STR(WINED3D_SAMP_MIP_FILTER);
        D3DSTATE_TO_STR(WINED3D_SAMP_MIPMAP_LOD_BIAS);
        D3DSTATE_TO_STR(WINED3D_SAMP_MAX_MIP_LEVEL);
        D3DSTATE_TO_STR(WINED3D_SAMP_MAX_ANISOTROPY);
        D3DSTATE_TO_STR(WINED3D_SAMP_SRGB_TEXTURE);
        D3DSTATE_TO_STR(WINED3D_SAMP_ELEMENT_INDEX);
        D3DSTATE_TO_STR(WINED3D_SAMP_DMAP_OFFSET);
#undef D3DSTATE_TO_STR
        default:
            FIXME("Unrecognized %u sampler state!\n", state);
            return "unrecognized";
    }
}