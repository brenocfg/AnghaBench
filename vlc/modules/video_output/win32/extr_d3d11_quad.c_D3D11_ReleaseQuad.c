#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  picSys; int /*<<< orphan*/ ** d3dsampState; int /*<<< orphan*/ * pVertexShaderConstants; int /*<<< orphan*/ * pIndexBuffer; int /*<<< orphan*/ * pVertexBuffer; int /*<<< orphan*/ ** pPixelShaderConstants; } ;
typedef  TYPE_1__ d3d_quad_t ;

/* Variables and functions */
 int /*<<< orphan*/  D3D11_ReleasePixelShader (TYPE_1__*) ; 
 int /*<<< orphan*/  ID3D11Buffer_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ID3D11SamplerState_Release (int /*<<< orphan*/ *) ; 
 size_t PS_CONST_COLORSPACE ; 
 size_t PS_CONST_LUMI_BOUNDS ; 
 int /*<<< orphan*/  ReleaseD3D11PictureSys (int /*<<< orphan*/ *) ; 

void D3D11_ReleaseQuad(d3d_quad_t *quad)
{
    if (quad->pPixelShaderConstants[PS_CONST_LUMI_BOUNDS])
    {
        ID3D11Buffer_Release(quad->pPixelShaderConstants[PS_CONST_LUMI_BOUNDS]);
        quad->pPixelShaderConstants[PS_CONST_LUMI_BOUNDS] = NULL;
    }
    if (quad->pPixelShaderConstants[PS_CONST_COLORSPACE])
    {
        ID3D11Buffer_Release(quad->pPixelShaderConstants[PS_CONST_COLORSPACE]);
        quad->pPixelShaderConstants[PS_CONST_COLORSPACE] = NULL;
    }
    if (quad->pVertexBuffer)
    {
        ID3D11Buffer_Release(quad->pVertexBuffer);
        quad->pVertexBuffer = NULL;
    }
    if (quad->pIndexBuffer)
    {
        ID3D11Buffer_Release(quad->pIndexBuffer);
        quad->pIndexBuffer = NULL;
    }
    if (quad->pVertexShaderConstants)
    {
        ID3D11Buffer_Release(quad->pVertexShaderConstants);
        quad->pVertexShaderConstants = NULL;
    }
    D3D11_ReleasePixelShader(quad);
    for (size_t i=0; i<2; i++)
    {
        if (quad->d3dsampState[i])
        {
            ID3D11SamplerState_Release(quad->d3dsampState[i]);
            quad->d3dsampState[i] = NULL;
        }
    }
    ReleaseD3D11PictureSys(&quad->picSys);
}