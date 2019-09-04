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
typedef  int UINT ;
typedef  int /*<<< orphan*/  PALETTEENTRY ;
typedef  int /*<<< orphan*/  IDirect3DSurface9 ;
typedef  int /*<<< orphan*/  IDirect3DBaseTexture9 ;
typedef  int /*<<< orphan*/  ID3DXBuffer ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ D3DRESOURCETYPE ;

/* Variables and functions */
 int /*<<< orphan*/  D3DCUBEMAP_FACE_POSITIVE_X ; 
 int /*<<< orphan*/  D3DERR_INVALIDCALL ; 
 scalar_t__ D3DRTYPE_CUBETEXTURE ; 
 scalar_t__ D3DRTYPE_TEXTURE ; 
 scalar_t__ D3DRTYPE_VOLUMETEXTURE ; 
 int /*<<< orphan*/  E_NOTIMPL ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 scalar_t__ IDirect3DBaseTexture9_GetType (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirect3DSurface9_Release (int /*<<< orphan*/ *) ; 
 int IDirect3DTexture9_GetLevelCount (int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_surface (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  save_dds_surface_to_memory (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

HRESULT save_dds_texture_to_memory(ID3DXBuffer **dst_buffer, IDirect3DBaseTexture9 *src_texture, const PALETTEENTRY *src_palette)
{
    HRESULT hr;
    D3DRESOURCETYPE type;
    UINT mip_levels;
    IDirect3DSurface9 *surface;

    type = IDirect3DBaseTexture9_GetType(src_texture);

    if ((type !=  D3DRTYPE_TEXTURE) && (type != D3DRTYPE_CUBETEXTURE) && (type != D3DRTYPE_VOLUMETEXTURE))
        return D3DERR_INVALIDCALL;

    if (type == D3DRTYPE_CUBETEXTURE)
    {
        FIXME("Cube texture not supported yet\n");
        return E_NOTIMPL;
    }
    else if (type == D3DRTYPE_VOLUMETEXTURE)
    {
        FIXME("Volume texture not supported yet\n");
        return E_NOTIMPL;
    }

    mip_levels = IDirect3DTexture9_GetLevelCount(src_texture);

    if (mip_levels > 1)
    {
        FIXME("Mipmap not supported yet\n");
        return E_NOTIMPL;
    }

    if (src_palette)
    {
        FIXME("Saving surfaces with palettized pixel formats not implemented yet\n");
        return E_NOTIMPL;
    }

    hr = get_surface(type, src_texture, D3DCUBEMAP_FACE_POSITIVE_X, 0, &surface);

    if (SUCCEEDED(hr))
    {
        hr = save_dds_surface_to_memory(dst_buffer, surface, NULL);
        IDirect3DSurface9_Release(surface);
    }

    return hr;
}