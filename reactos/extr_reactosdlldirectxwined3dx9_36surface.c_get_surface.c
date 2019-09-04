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
struct IDirect3DSurface9 {int dummy; } ;
struct IDirect3DBaseTexture9 {int dummy; } ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  IDirect3DTexture9 ;
typedef  int /*<<< orphan*/  IDirect3DCubeTexture9 ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int D3DRESOURCETYPE ;

/* Variables and functions */
#define  D3DRTYPE_CUBETEXTURE 129 
#define  D3DRTYPE_TEXTURE 128 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  E_NOTIMPL ; 
 int /*<<< orphan*/  IDirect3DCubeTexture9_GetCubeMapSurface (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct IDirect3DSurface9**) ; 
 int /*<<< orphan*/  IDirect3DTexture9_GetSurfaceLevel (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct IDirect3DSurface9**) ; 

__attribute__((used)) static HRESULT get_surface(D3DRESOURCETYPE type, struct IDirect3DBaseTexture9 *tex,
        int face, UINT level, struct IDirect3DSurface9 **surf)
{
    switch (type)
    {
        case D3DRTYPE_TEXTURE:
            return IDirect3DTexture9_GetSurfaceLevel((IDirect3DTexture9*) tex, level, surf);
        case D3DRTYPE_CUBETEXTURE:
            return IDirect3DCubeTexture9_GetCubeMapSurface((IDirect3DCubeTexture9*) tex, face, level, surf);
        default:
            ERR("Unexpected texture type\n");
            return E_NOTIMPL;
    }
}