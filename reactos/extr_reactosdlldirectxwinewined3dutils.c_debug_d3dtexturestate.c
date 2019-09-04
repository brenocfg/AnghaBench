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
typedef  enum wined3d_texture_stage_state { ____Placeholder_wined3d_texture_stage_state } wined3d_texture_stage_state ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int) ; 
#define  WINED3D_TSS_ALPHA_ARG0 145 
#define  WINED3D_TSS_ALPHA_ARG1 144 
#define  WINED3D_TSS_ALPHA_ARG2 143 
#define  WINED3D_TSS_ALPHA_OP 142 
#define  WINED3D_TSS_BUMPENV_LOFFSET 141 
#define  WINED3D_TSS_BUMPENV_LSCALE 140 
#define  WINED3D_TSS_BUMPENV_MAT00 139 
#define  WINED3D_TSS_BUMPENV_MAT01 138 
#define  WINED3D_TSS_BUMPENV_MAT10 137 
#define  WINED3D_TSS_BUMPENV_MAT11 136 
#define  WINED3D_TSS_COLOR_ARG0 135 
#define  WINED3D_TSS_COLOR_ARG1 134 
#define  WINED3D_TSS_COLOR_ARG2 133 
#define  WINED3D_TSS_COLOR_OP 132 
#define  WINED3D_TSS_CONSTANT 131 
#define  WINED3D_TSS_RESULT_ARG 130 
#define  WINED3D_TSS_TEXCOORD_INDEX 129 
#define  WINED3D_TSS_TEXTURE_TRANSFORM_FLAGS 128 

const char *debug_d3dtexturestate(enum wined3d_texture_stage_state state)
{
    switch (state)
    {
#define D3DSTATE_TO_STR(u) case u: return #u
        D3DSTATE_TO_STR(WINED3D_TSS_COLOR_OP);
        D3DSTATE_TO_STR(WINED3D_TSS_COLOR_ARG1);
        D3DSTATE_TO_STR(WINED3D_TSS_COLOR_ARG2);
        D3DSTATE_TO_STR(WINED3D_TSS_ALPHA_OP);
        D3DSTATE_TO_STR(WINED3D_TSS_ALPHA_ARG1);
        D3DSTATE_TO_STR(WINED3D_TSS_ALPHA_ARG2);
        D3DSTATE_TO_STR(WINED3D_TSS_BUMPENV_MAT00);
        D3DSTATE_TO_STR(WINED3D_TSS_BUMPENV_MAT01);
        D3DSTATE_TO_STR(WINED3D_TSS_BUMPENV_MAT10);
        D3DSTATE_TO_STR(WINED3D_TSS_BUMPENV_MAT11);
        D3DSTATE_TO_STR(WINED3D_TSS_TEXCOORD_INDEX);
        D3DSTATE_TO_STR(WINED3D_TSS_BUMPENV_LSCALE);
        D3DSTATE_TO_STR(WINED3D_TSS_BUMPENV_LOFFSET);
        D3DSTATE_TO_STR(WINED3D_TSS_TEXTURE_TRANSFORM_FLAGS);
        D3DSTATE_TO_STR(WINED3D_TSS_COLOR_ARG0);
        D3DSTATE_TO_STR(WINED3D_TSS_ALPHA_ARG0);
        D3DSTATE_TO_STR(WINED3D_TSS_RESULT_ARG);
        D3DSTATE_TO_STR(WINED3D_TSS_CONSTANT);
#undef D3DSTATE_TO_STR
        default:
            FIXME("Unrecognized %u texture state!\n", state);
            return "unrecognized";
    }
}