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
typedef  int /*<<< orphan*/  IDirect3DVertexShader9 ;
typedef  int /*<<< orphan*/  IDirect3DSurface9 ;
typedef  int /*<<< orphan*/  IDirect3DPixelShader9 ;
typedef  int /*<<< orphan*/  IDirect3DDevice9 ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  D3DFORMAT ;

/* Variables and functions */
 int /*<<< orphan*/  D3DMULTISAMPLE_NONE ; 
 int /*<<< orphan*/  D3DPOOL_SYSTEMMEM ; 
 scalar_t__ D3D_OK ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IDirect3DDevice9_CreateOffscreenPlainSurface (int /*<<< orphan*/ *,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ IDirect3DDevice9_CreateRenderTarget (int /*<<< orphan*/ *,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ IDirect3DDevice9_SetPixelShader (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IDirect3DDevice9_SetRenderTarget (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ IDirect3DDevice9_SetVertexShader (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void setup_device9(IDirect3DDevice9 *device, IDirect3DSurface9 **render_target,
        IDirect3DSurface9 **readback, D3DFORMAT format, unsigned int width, unsigned int height,
        IDirect3DVertexShader9 *vshader, IDirect3DPixelShader9 *pshader)
{
    HRESULT hr;
    hr = IDirect3DDevice9_CreateRenderTarget(device, width, height, format,
            D3DMULTISAMPLE_NONE, 0, FALSE, render_target, NULL);
    ok(hr == D3D_OK, "IDirect3DDevice9_CreateRenderTarget returned: %08x\n", hr);

    /* The Direct3D 9 docs state that we cannot lock a render target surface,
       instead we must copy the render target onto this surface to lock it */
    hr = IDirect3DDevice9_CreateOffscreenPlainSurface(device, width, height, format,
            D3DPOOL_SYSTEMMEM, readback, NULL);
    ok(hr == D3D_OK, "IDirect3DDevice9_CreateOffscreenPlainSurface returned: %08x\n", hr);

    hr = IDirect3DDevice9_SetRenderTarget(device, 0, *render_target);
    ok(hr == D3D_OK, "IDirect3DDevice9_SetRenderTarget returned: %08x\n", hr);

    hr = IDirect3DDevice9_SetVertexShader(device, vshader);
    ok(hr == D3D_OK, "IDirect3DDevice9_SetVertexShader returned: %08x\n", hr);
    hr = IDirect3DDevice9_SetPixelShader(device, pshader);
    ok(hr == D3D_OK, "IDirect3DDevice9_SetPixelShader returned: %08x\n", hr);
}