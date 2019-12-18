#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_11__ {scalar_t__* resourceFormat; } ;
typedef  TYPE_3__ d3d_format_t ;
typedef  int UINT ;
struct TYPE_10__ {int MipLevels; int ArraySize; int FirstArraySlice; } ;
struct TYPE_9__ {int MipLevels; } ;
struct TYPE_13__ {scalar_t__ Format; TYPE_2__ Texture2DArray; int /*<<< orphan*/  ViewDimension; TYPE_1__ Texture2D; int /*<<< orphan*/  member_0; } ;
struct TYPE_12__ {int BindFlags; int ArraySize; } ;
typedef  int /*<<< orphan*/  ID3D11Texture2D ;
typedef  int /*<<< orphan*/  ID3D11ShaderResourceView ;
typedef  int /*<<< orphan*/  ID3D11Resource ;
typedef  int /*<<< orphan*/  ID3D11Device ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_4__ D3D11_TEXTURE2D_DESC ;
typedef  TYPE_5__ D3D11_SHADER_RESOURCE_VIEW_DESC ;

/* Variables and functions */
 int D3D11_BIND_SHADER_RESOURCE ; 
 int D3D11_MAX_SHADER_VIEW ; 
 int /*<<< orphan*/  D3D11_SRV_DIMENSION_TEXTURE2D ; 
 int /*<<< orphan*/  D3D11_SRV_DIMENSION_TEXTURE2DARRAY ; 
 scalar_t__ DXGI_FORMAT_UNKNOWN ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ID3D11Device_CreateShaderResourceView (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ID3D11ShaderResourceView_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ID3D11Texture2D_GetDesc (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,int,int,int /*<<< orphan*/ ) ; 

int D3D11_AllocateResourceView(vlc_object_t *obj, ID3D11Device *d3ddevice,
                              const d3d_format_t *format,
                              ID3D11Texture2D *p_texture[D3D11_MAX_SHADER_VIEW], UINT slice_index,
                              ID3D11ShaderResourceView *renderSrc[D3D11_MAX_SHADER_VIEW])
{
    HRESULT hr;
    int i;
    D3D11_SHADER_RESOURCE_VIEW_DESC resviewDesc = { 0 };
    D3D11_TEXTURE2D_DESC texDesc;
    ID3D11Texture2D_GetDesc(p_texture[0], &texDesc);
    assert(texDesc.BindFlags & D3D11_BIND_SHADER_RESOURCE);

    if (texDesc.ArraySize == 1)
    {
        resviewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        resviewDesc.Texture2D.MipLevels = 1;
    }
    else
    {
        resviewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
        resviewDesc.Texture2DArray.MipLevels = -1;
        resviewDesc.Texture2DArray.ArraySize = 1;
        resviewDesc.Texture2DArray.FirstArraySlice = slice_index;
        assert(slice_index < texDesc.ArraySize);
    }
    for (i=0; i<D3D11_MAX_SHADER_VIEW; i++)
    {
        resviewDesc.Format = format->resourceFormat[i];
        if (resviewDesc.Format == DXGI_FORMAT_UNKNOWN)
            renderSrc[i] = NULL;
        else
        {
            hr = ID3D11Device_CreateShaderResourceView(d3ddevice, (ID3D11Resource*)p_texture[i], &resviewDesc, &renderSrc[i]);
            if (FAILED(hr)) {
                msg_Err(obj, "Could not Create the Texture ResourceView %d slice %d. (hr=0x%lX)", i, slice_index, hr);
                break;
            }
        }
    }

    if (i != D3D11_MAX_SHADER_VIEW)
    {
        while (--i >= 0)
        {
            ID3D11ShaderResourceView_Release(renderSrc[i]);
            renderSrc[i] = NULL;
        }
        return VLC_EGENERIC;
    }

    return VLC_SUCCESS;
}