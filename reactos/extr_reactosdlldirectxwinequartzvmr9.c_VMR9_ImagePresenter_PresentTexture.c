#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct VERTEX {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  d3d9_dev; int /*<<< orphan*/  d3d9_vertex; } ;
typedef  TYPE_1__ VMR9DefaultAllocatorPresenterImpl ;
typedef  int /*<<< orphan*/  IDirect3DTexture9 ;
typedef  int /*<<< orphan*/  IDirect3DSurface9 ;
typedef  int /*<<< orphan*/  IDirect3DBaseTexture9 ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  D3DPT_TRIANGLESTRIP ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*,...) ; 
 int /*<<< orphan*/  IDirect3DDevice9_DrawPrimitive (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IDirect3DDevice9_SetFVF (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirect3DDevice9_SetStreamSource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IDirect3DDevice9_SetTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirect3DSurface9_GetContainer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IDirect3DTexture9_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IDirect3DTexture9 ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  USED_FVF ; 

__attribute__((used)) static HRESULT VMR9_ImagePresenter_PresentTexture(VMR9DefaultAllocatorPresenterImpl *This, IDirect3DSurface9 *surface)
{
    IDirect3DTexture9 *texture = NULL;
    HRESULT hr;

    hr = IDirect3DDevice9_SetFVF(This->d3d9_dev, USED_FVF);
    if (FAILED(hr))
    {
        FIXME("SetFVF: %08x\n", hr);
        return hr;
    }

    hr = IDirect3DDevice9_SetStreamSource(This->d3d9_dev, 0, This->d3d9_vertex, 0, sizeof(struct VERTEX));
    if (FAILED(hr))
    {
        FIXME("SetStreamSource: %08x\n", hr);
        return hr;
    }

    hr = IDirect3DSurface9_GetContainer(surface, &IID_IDirect3DTexture9, (void **) &texture);
    if (FAILED(hr))
    {
        FIXME("IDirect3DSurface9_GetContainer failed\n");
        return hr;
    }
    hr = IDirect3DDevice9_SetTexture(This->d3d9_dev, 0, (IDirect3DBaseTexture9 *)texture);
    IDirect3DTexture9_Release(texture);
    if (FAILED(hr))
    {
        FIXME("SetTexture: %08x\n", hr);
        return hr;
    }

    hr = IDirect3DDevice9_DrawPrimitive(This->d3d9_dev, D3DPT_TRIANGLESTRIP, 0, 2);
    if (FAILED(hr))
    {
        FIXME("DrawPrimitive: %08x\n", hr);
        return hr;
    }

    return S_OK;
}