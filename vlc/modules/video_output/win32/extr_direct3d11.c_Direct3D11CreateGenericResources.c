#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_16__ ;
typedef  struct TYPE_19__   TYPE_13__ ;

/* Type definitions */
struct TYPE_22__ {TYPE_3__* sys; } ;
typedef  TYPE_2__ vout_display_t ;
struct TYPE_19__ {int /*<<< orphan*/  d3dcontext; int /*<<< orphan*/  d3ddevice; } ;
struct TYPE_20__ {int /*<<< orphan*/ * textureFormat; } ;
struct TYPE_23__ {int /*<<< orphan*/  projectionVShader; TYPE_13__ d3d_dev; int /*<<< orphan*/  hd3d; int /*<<< orphan*/  flatVShader; int /*<<< orphan*/  picQuad; TYPE_16__ regionQuad; int /*<<< orphan*/  display; int /*<<< orphan*/  legacy_shader; int /*<<< orphan*/  prepareWait; } ;
typedef  TYPE_3__ vout_display_sys_t ;
typedef  int /*<<< orphan*/  stencilDesc ;
struct TYPE_25__ {TYPE_1__* RenderTarget; int /*<<< orphan*/  member_0; } ;
struct TYPE_24__ {int /*<<< orphan*/  Query; int /*<<< orphan*/  member_0; } ;
struct TYPE_21__ {int /*<<< orphan*/  DestBlendAlpha; int /*<<< orphan*/  SrcBlendAlpha; void* BlendOpAlpha; int /*<<< orphan*/  DestBlend; int /*<<< orphan*/  SrcBlend; void* BlendOp; int /*<<< orphan*/  RenderTargetWriteMask; int /*<<< orphan*/  BlendEnable; } ;
typedef  int /*<<< orphan*/  ID3D11DepthStencilState ;
typedef  int /*<<< orphan*/  ID3D11BlendState ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_4__ D3D11_QUERY_DESC ;
typedef  int /*<<< orphan*/  D3D11_DEPTH_STENCIL_DESC ;
typedef  TYPE_5__ D3D11_BLEND_DESC ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_PRIMARIES_SRGB ; 
 int /*<<< orphan*/  D3D11_BLEND_INV_SRC_ALPHA ; 
 int /*<<< orphan*/  D3D11_BLEND_ONE ; 
 void* D3D11_BLEND_OP_ADD ; 
 int /*<<< orphan*/  D3D11_BLEND_SRC_ALPHA ; 
 int /*<<< orphan*/  D3D11_BLEND_ZERO ; 
 int /*<<< orphan*/  D3D11_COLOR_WRITE_ENABLE_ALL ; 
 int /*<<< orphan*/  D3D11_CompileFlatVertexShader (TYPE_2__*,int /*<<< orphan*/ *,TYPE_13__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  D3D11_CompilePixelShader (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_13__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_16__*) ; 
 int /*<<< orphan*/  D3D11_CompileProjectionVertexShader (TYPE_2__*,int /*<<< orphan*/ *,TYPE_13__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  D3D11_QUERY_EVENT ; 
 int /*<<< orphan*/  D3D11_ReleasePixelShader (int /*<<< orphan*/ *) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ID3D11BlendState_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ID3D11DepthStencilState_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ID3D11DeviceContext_OMSetBlendState (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ID3D11DeviceContext_OMSetDepthStencilState (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ID3D11Device_CreateBlendState (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ID3D11Device_CreateDepthStencilState (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ID3D11Device_CreateQuery (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRANSFER_FUNC_SRGB ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UpdatePicQuadPosition (TYPE_2__*) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  ZeroMemory (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int Direct3D11CreateGenericResources(vout_display_t *vd)
{
    vout_display_sys_t *sys = vd->sys;
    HRESULT hr;

    D3D11_QUERY_DESC query = { 0 };
    query.Query = D3D11_QUERY_EVENT;
    hr = ID3D11Device_CreateQuery(sys->d3d_dev.d3ddevice, &query, &sys->prepareWait);

    ID3D11BlendState *pSpuBlendState;
    D3D11_BLEND_DESC spuBlendDesc = { 0 };
    spuBlendDesc.RenderTarget[0].BlendEnable = TRUE;
    spuBlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    /* output colors */
    spuBlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
    spuBlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA; /* keep source intact */
    spuBlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA; /* RGB colors + inverse alpha (255 is full opaque) */
    /* output alpha  */
    spuBlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
    spuBlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE; /* keep source intact */
    spuBlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO; /* discard */

    hr = ID3D11Device_CreateBlendState(sys->d3d_dev.d3ddevice, &spuBlendDesc, &pSpuBlendState);
    if (FAILED(hr)) {
       msg_Err(vd, "Could not create SPU blend state. (hr=0x%lX)", hr);
       return VLC_EGENERIC;
    }
    ID3D11DeviceContext_OMSetBlendState(sys->d3d_dev.d3dcontext, pSpuBlendState, NULL, 0xFFFFFFFF);
    ID3D11BlendState_Release(pSpuBlendState);

    /* disable depth testing as we're only doing 2D
     * see https://msdn.microsoft.com/en-us/library/windows/desktop/bb205074%28v=vs.85%29.aspx
     * see http://rastertek.com/dx11tut11.html
    */
    D3D11_DEPTH_STENCIL_DESC stencilDesc;
    ZeroMemory(&stencilDesc, sizeof(stencilDesc));

    ID3D11DepthStencilState *pDepthStencilState;
    hr = ID3D11Device_CreateDepthStencilState(sys->d3d_dev.d3ddevice, &stencilDesc, &pDepthStencilState );
    if (SUCCEEDED(hr)) {
        ID3D11DeviceContext_OMSetDepthStencilState(sys->d3d_dev.d3dcontext, pDepthStencilState, 0);
        ID3D11DepthStencilState_Release(pDepthStencilState);
    }

    if (sys->regionQuad.textureFormat != NULL)
    {
        hr = D3D11_CompilePixelShader(vd, &sys->hd3d, sys->legacy_shader, &sys->d3d_dev,
                                      &sys->display, TRANSFER_FUNC_SRGB, COLOR_PRIMARIES_SRGB, true,
                                      &sys->regionQuad);
        if (FAILED(hr))
        {
            D3D11_ReleasePixelShader(&sys->picQuad);
            msg_Err(vd, "Failed to create the SPU pixel shader. (hr=0x%lX)", hr);
            return VLC_EGENERIC;
        }
    }

    hr = D3D11_CompileFlatVertexShader(vd, &sys->hd3d, &sys->d3d_dev, &sys->flatVShader);
    if(FAILED(hr)) {
      msg_Err(vd, "Failed to create the vertex input layout. (hr=0x%lX)", hr);
      return VLC_EGENERIC;
    }

    hr = D3D11_CompileProjectionVertexShader(vd, &sys->hd3d, &sys->d3d_dev, &sys->projectionVShader);
    if(FAILED(hr)) {
      msg_Err(vd, "Failed to create the projection vertex shader. (hr=0x%lX)", hr);
      return VLC_EGENERIC;
    }

    UpdatePicQuadPosition(vd);

    msg_Dbg(vd, "Direct3D11 resources created");
    return VLC_SUCCESS;
}