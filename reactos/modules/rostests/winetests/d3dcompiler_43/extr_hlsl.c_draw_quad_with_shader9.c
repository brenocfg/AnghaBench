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
struct vertex {int dummy; } ;
typedef  int /*<<< orphan*/  IDirect3DVertexBuffer9 ;
typedef  int /*<<< orphan*/  IDirect3DDevice9 ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  D3DXMATRIX ;

/* Variables and functions */
 int /*<<< orphan*/  D3DCLEAR_TARGET ; 
 int /*<<< orphan*/  D3DCOLOR_XRGB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  D3DPT_TRIANGLESTRIP ; 
 int /*<<< orphan*/  D3DTS_PROJECTION ; 
 int /*<<< orphan*/  D3DXMatrixOrthoLH (int /*<<< orphan*/ *,float,float,float,float) ; 
 scalar_t__ D3D_OK ; 
 scalar_t__ IDirect3DDevice9_BeginScene (int /*<<< orphan*/ *) ; 
 scalar_t__ IDirect3DDevice9_Clear (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float,int /*<<< orphan*/ ) ; 
 scalar_t__ IDirect3DDevice9_DrawPrimitive (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ IDirect3DDevice9_EndScene (int /*<<< orphan*/ *) ; 
 scalar_t__ IDirect3DDevice9_SetStreamSource (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IDirect3DDevice9_SetTransform (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void draw_quad_with_shader9(IDirect3DDevice9 *device, IDirect3DVertexBuffer9 *quad_geometry)
{
    HRESULT hr;
    D3DXMATRIX projection_matrix;

    D3DXMatrixOrthoLH(&projection_matrix, 2.0f, 2.0f, 0.0f, 1.0f);
    IDirect3DDevice9_SetTransform(device, D3DTS_PROJECTION, &projection_matrix);

    hr = IDirect3DDevice9_Clear(device, 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
    ok(hr == D3D_OK, "IDirect3DDevice9_Clear returned: %08x\n", hr);

    hr = IDirect3DDevice9_BeginScene(device);
    ok(hr == D3D_OK, "IDirect3DDevice9_BeginScene returned: %08x\n", hr);

    hr = IDirect3DDevice9_SetStreamSource(device, 0, quad_geometry, 0, sizeof(struct vertex));
    ok(hr == D3D_OK, "IDirect3DDevice9_SetStreamSource returned: %08x\n", hr);
    hr = IDirect3DDevice9_DrawPrimitive(device, D3DPT_TRIANGLESTRIP, 0, 2);
    ok(hr == D3D_OK, "IDirect3DDevice9_DrawPrimitive returned: %08x\n", hr);

    hr = IDirect3DDevice9_EndScene(device);
    ok(hr == D3D_OK, "IDirect3DDevice9_EndScene returned: %08x\n", hr);
}