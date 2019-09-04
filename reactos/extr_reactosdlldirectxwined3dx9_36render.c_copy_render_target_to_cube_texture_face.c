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
typedef  int /*<<< orphan*/  IDirect3DSurface9 ;
typedef  int /*<<< orphan*/  IDirect3DCubeTexture9 ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  D3DCUBEMAP_FACES ;

/* Variables and functions */
 int /*<<< orphan*/  D3DXLoadSurfaceFromSurface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirect3DCubeTexture9_GetCubeMapSurface (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IDirect3DSurface9_Release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void copy_render_target_to_cube_texture_face(IDirect3DCubeTexture9 *cube_texture,
        D3DCUBEMAP_FACES face, IDirect3DSurface9 *render_target, DWORD filter)
{
    HRESULT hr;
    IDirect3DSurface9 *cube_surface;

    IDirect3DCubeTexture9_GetCubeMapSurface(cube_texture, face, 0, &cube_surface);

    hr = D3DXLoadSurfaceFromSurface(cube_surface, NULL, NULL, render_target, NULL, NULL, filter, 0);
    if (FAILED(hr)) ERR("Copying render target data to surface failed %#x\n", hr);

    IDirect3DSurface9_Release(cube_surface);
}