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
typedef  int D3DXPARAMETER_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  D3DXPT_BOOL ; 
 int /*<<< orphan*/  D3DXPT_FLOAT ; 
 int /*<<< orphan*/  D3DXPT_INT ; 
 int /*<<< orphan*/  D3DXPT_PIXELFRAGMENT ; 
 int /*<<< orphan*/  D3DXPT_PIXELSHADER ; 
 int /*<<< orphan*/  D3DXPT_SAMPLER ; 
 int /*<<< orphan*/  D3DXPT_SAMPLER1D ; 
 int /*<<< orphan*/  D3DXPT_SAMPLER2D ; 
 int /*<<< orphan*/  D3DXPT_SAMPLER3D ; 
 int /*<<< orphan*/  D3DXPT_SAMPLERCUBE ; 
 int /*<<< orphan*/  D3DXPT_STRING ; 
 int /*<<< orphan*/  D3DXPT_TEXTURE ; 
 int /*<<< orphan*/  D3DXPT_TEXTURE1D ; 
 int /*<<< orphan*/  D3DXPT_TEXTURE2D ; 
 int /*<<< orphan*/  D3DXPT_TEXTURE3D ; 
 int /*<<< orphan*/  D3DXPT_TEXTURECUBE ; 
 int /*<<< orphan*/  D3DXPT_UNSUPPORTED ; 
 int /*<<< orphan*/  D3DXPT_VERTEXFRAGMENT ; 
 int /*<<< orphan*/  D3DXPT_VERTEXSHADER ; 
 int /*<<< orphan*/  D3DXPT_VOID ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  WINE_D3DX_TO_STR (int /*<<< orphan*/ ) ; 

const char *debug_d3dxparameter_type(D3DXPARAMETER_TYPE t)
{
    switch (t)
    {
        WINE_D3DX_TO_STR(D3DXPT_VOID);
        WINE_D3DX_TO_STR(D3DXPT_BOOL);
        WINE_D3DX_TO_STR(D3DXPT_INT);
        WINE_D3DX_TO_STR(D3DXPT_FLOAT);
        WINE_D3DX_TO_STR(D3DXPT_STRING);
        WINE_D3DX_TO_STR(D3DXPT_TEXTURE);
        WINE_D3DX_TO_STR(D3DXPT_TEXTURE1D);
        WINE_D3DX_TO_STR(D3DXPT_TEXTURE2D);
        WINE_D3DX_TO_STR(D3DXPT_TEXTURE3D);
        WINE_D3DX_TO_STR(D3DXPT_TEXTURECUBE);
        WINE_D3DX_TO_STR(D3DXPT_SAMPLER);
        WINE_D3DX_TO_STR(D3DXPT_SAMPLER1D);
        WINE_D3DX_TO_STR(D3DXPT_SAMPLER2D);
        WINE_D3DX_TO_STR(D3DXPT_SAMPLER3D);
        WINE_D3DX_TO_STR(D3DXPT_SAMPLERCUBE);
        WINE_D3DX_TO_STR(D3DXPT_PIXELSHADER);
        WINE_D3DX_TO_STR(D3DXPT_VERTEXSHADER);
        WINE_D3DX_TO_STR(D3DXPT_PIXELFRAGMENT);
        WINE_D3DX_TO_STR(D3DXPT_VERTEXFRAGMENT);
        WINE_D3DX_TO_STR(D3DXPT_UNSUPPORTED);
        default:
            FIXME("Unrecognized D3DXPARAMETER_TYP %#x.\n", t);
            return "unrecognized";
    }
}