#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_3__* sys; } ;
typedef  TYPE_2__ vout_display_t ;
struct TYPE_12__ {int TextureFilterCaps; int AlphaCmpCaps; } ;
struct TYPE_16__ {TYPE_1__ caps; int /*<<< orphan*/  BufferFormat; int /*<<< orphan*/ * dev; } ;
struct TYPE_14__ {int clear_scene; TYPE_5__ d3d_dev; int /*<<< orphan*/ * d3dregion; scalar_t__ d3dregion_count; int /*<<< orphan*/ * sceneTexture; int /*<<< orphan*/  sceneVertexBuffer; } ;
typedef  TYPE_3__ vout_display_sys_t ;
struct TYPE_15__ {int i_visible_width; int i_visible_height; int /*<<< orphan*/  i_height; int /*<<< orphan*/  i_width; } ;
typedef  TYPE_4__ video_format_t ;
typedef  TYPE_5__ d3d9_device_t ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  IDirect3DDevice9 ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  CUSTOMVERTEX ;

/* Variables and functions */
 int D3DBLEND_INVSRCALPHA ; 
 int D3DBLEND_SRCALPHA ; 
 int D3DCMP_GREATER ; 
 int D3DCOLOR_XRGB (int,int,int) ; 
 int D3DCULL_NONE ; 
 int /*<<< orphan*/  D3DFVF_CUSTOMVERTEX ; 
 int D3DPCMPCAPS_GREATER ; 
 int /*<<< orphan*/  D3DPOOL_DEFAULT ; 
 int D3DPTFILTERCAPS_MAGFLINEAR ; 
 int D3DPTFILTERCAPS_MINFLINEAR ; 
 int /*<<< orphan*/  D3DRS_ALPHABLENDENABLE ; 
 int /*<<< orphan*/  D3DRS_ALPHAFUNC ; 
 int /*<<< orphan*/  D3DRS_ALPHAREF ; 
 int /*<<< orphan*/  D3DRS_ALPHATESTENABLE ; 
 int /*<<< orphan*/  D3DRS_AMBIENT ; 
 int /*<<< orphan*/  D3DRS_CULLMODE ; 
 int /*<<< orphan*/  D3DRS_DESTBLEND ; 
 int /*<<< orphan*/  D3DRS_DITHERENABLE ; 
 int /*<<< orphan*/  D3DRS_LIGHTING ; 
 int /*<<< orphan*/  D3DRS_SRCBLEND ; 
 int /*<<< orphan*/  D3DRS_STENCILENABLE ; 
 int /*<<< orphan*/  D3DRS_ZENABLE ; 
 int /*<<< orphan*/  D3DSAMP_ADDRESSU ; 
 int /*<<< orphan*/  D3DSAMP_ADDRESSV ; 
 int /*<<< orphan*/  D3DSAMP_MAGFILTER ; 
 int /*<<< orphan*/  D3DSAMP_MINFILTER ; 
 int /*<<< orphan*/  D3DTADDRESS_CLAMP ; 
 int /*<<< orphan*/  D3DTA_DIFFUSE ; 
 int /*<<< orphan*/  D3DTA_TEXTURE ; 
 int /*<<< orphan*/  D3DTEXF_LINEAR ; 
 int /*<<< orphan*/  D3DTEXF_POINT ; 
 int /*<<< orphan*/  D3DTOP_MODULATE ; 
 int /*<<< orphan*/  D3DTOP_SELECTARG1 ; 
 int /*<<< orphan*/  D3DTSS_ALPHAARG1 ; 
 int /*<<< orphan*/  D3DTSS_ALPHAARG2 ; 
 int /*<<< orphan*/  D3DTSS_ALPHAOP ; 
 int /*<<< orphan*/  D3DTSS_COLORARG1 ; 
 int /*<<< orphan*/  D3DTSS_COLOROP ; 
 int D3DUSAGE_DYNAMIC ; 
 int /*<<< orphan*/  D3DUSAGE_RENDERTARGET ; 
 int D3DUSAGE_WRITEONLY ; 
 int D3DZB_FALSE ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int FALSE ; 
 int /*<<< orphan*/  IDirect3DDevice9_CreateTexture (int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirect3DDevice9_CreateVertexBuffer (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirect3DDevice9_SetFVF (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirect3DDevice9_SetRenderState (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IDirect3DDevice9_SetSamplerState (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirect3DDevice9_SetTextureStageState (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirect3DTexture9_Release (int /*<<< orphan*/ *) ; 
 int TRUE ; 
 scalar_t__ UpdateOutput (TYPE_2__*,TYPE_4__ const*) ; 
 int VLC_EGENERIC ; 
 scalar_t__ VLC_SUCCESS ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  msg_Err (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int Direct3D9CreateScene(vout_display_t *vd, const video_format_t *fmt)
{
    vout_display_sys_t *sys = vd->sys;
    const d3d9_device_t *p_d3d9_dev = &sys->d3d_dev;
    IDirect3DDevice9        *d3ddev = p_d3d9_dev->dev;
    HRESULT hr;

    if (UpdateOutput(vd, fmt) != VLC_SUCCESS)
        return VLC_EGENERIC;

    UINT width  = fmt->i_visible_width;
    UINT height = fmt->i_visible_height;
    // On nVidia & AMD, StretchRect will fail if the visible size isn't even.
    // When copying the entire buffer, the margin end up being blended in the actual picture
    // on nVidia (regardless of even/odd dimensions)
    if (height & 1) height++;
    if (width  & 1) width++;

    /*
     * Create a texture for use when rendering a scene
     * for performance reason, texture format is identical to backbuffer
     * which would usually be a RGB format
     */
    hr = IDirect3DDevice9_CreateTexture(d3ddev,
                                        width,
                                        height,
                                        1,
                                        D3DUSAGE_RENDERTARGET,
                                        p_d3d9_dev->BufferFormat,
                                        D3DPOOL_DEFAULT,
                                        &sys->sceneTexture,
                                        NULL);
    if (FAILED(hr)) {
        msg_Err(vd, "Failed to create texture. (hr=0x%lX)", hr);
        return VLC_EGENERIC;
    }

#ifndef NDEBUG
    msg_Dbg(vd, "Direct3D created texture: %ix%i",
                fmt->i_width, fmt->i_height);
#endif

    /*
    ** Create a vertex buffer for use when rendering scene
    */
    hr = IDirect3DDevice9_CreateVertexBuffer(d3ddev,
                                             sizeof(CUSTOMVERTEX)*4,
                                             D3DUSAGE_DYNAMIC|D3DUSAGE_WRITEONLY,
                                             D3DFVF_CUSTOMVERTEX,
                                             D3DPOOL_DEFAULT,
                                             &sys->sceneVertexBuffer,
                                             NULL);
    if (FAILED(hr)) {
        msg_Err(vd, "Failed to create vertex buffer. (hr=0x%lX)", hr);
        IDirect3DTexture9_Release(sys->sceneTexture);
        sys->sceneTexture = NULL;
        return VLC_EGENERIC;
    }

    // we use FVF instead of vertex shader
    hr = IDirect3DDevice9_SetFVF(d3ddev, D3DFVF_CUSTOMVERTEX);
    if (FAILED(hr)) {
        msg_Dbg(vd, "Failed SetFVF: 0x%lX", hr);
        return -1;
    }

    /* */
    sys->d3dregion_count = 0;
    sys->d3dregion       = NULL;

    sys->clear_scene = true;

    // Texture coordinates outside the range [0.0, 1.0] are set
    // to the texture color at 0.0 or 1.0, respectively.
    IDirect3DDevice9_SetSamplerState(d3ddev, 0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
    IDirect3DDevice9_SetSamplerState(d3ddev, 0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);

    // Set linear filtering quality
    if (sys->d3d_dev.caps.TextureFilterCaps & D3DPTFILTERCAPS_MINFLINEAR) {
        //msg_Dbg(vd, "Using D3DTEXF_LINEAR for minification");
        IDirect3DDevice9_SetSamplerState(d3ddev, 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
    } else {
        //msg_Dbg(vd, "Using D3DTEXF_POINT for minification");
        IDirect3DDevice9_SetSamplerState(d3ddev, 0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
    }
    if (sys->d3d_dev.caps.TextureFilterCaps & D3DPTFILTERCAPS_MAGFLINEAR) {
        //msg_Dbg(vd, "Using D3DTEXF_LINEAR for magnification");
        IDirect3DDevice9_SetSamplerState(d3ddev, 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
    } else {
        //msg_Dbg(vd, "Using D3DTEXF_POINT for magnification");
        IDirect3DDevice9_SetSamplerState(d3ddev, 0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
    }

    // set maximum ambient light
    IDirect3DDevice9_SetRenderState(d3ddev, D3DRS_AMBIENT, D3DCOLOR_XRGB(255,255,255));

    // Turn off culling
    IDirect3DDevice9_SetRenderState(d3ddev, D3DRS_CULLMODE, D3DCULL_NONE);

    // Turn off the zbuffer
    IDirect3DDevice9_SetRenderState(d3ddev, D3DRS_ZENABLE, D3DZB_FALSE);

    // Turn off lights
    IDirect3DDevice9_SetRenderState(d3ddev, D3DRS_LIGHTING, FALSE);

    // Enable dithering
    IDirect3DDevice9_SetRenderState(d3ddev, D3DRS_DITHERENABLE, TRUE);

    // disable stencil
    IDirect3DDevice9_SetRenderState(d3ddev, D3DRS_STENCILENABLE, FALSE);

    // manage blending
    IDirect3DDevice9_SetRenderState(d3ddev, D3DRS_ALPHABLENDENABLE, FALSE);
    IDirect3DDevice9_SetRenderState(d3ddev, D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
    IDirect3DDevice9_SetRenderState(d3ddev, D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);

    if (sys->d3d_dev.caps.AlphaCmpCaps & D3DPCMPCAPS_GREATER) {
        IDirect3DDevice9_SetRenderState(d3ddev, D3DRS_ALPHATESTENABLE,TRUE);
        IDirect3DDevice9_SetRenderState(d3ddev, D3DRS_ALPHAREF, 0x00);
        IDirect3DDevice9_SetRenderState(d3ddev, D3DRS_ALPHAFUNC,D3DCMP_GREATER);
    }

    // Set texture states
    IDirect3DDevice9_SetTextureStageState(d3ddev, 0, D3DTSS_COLOROP,D3DTOP_SELECTARG1);
    IDirect3DDevice9_SetTextureStageState(d3ddev, 0, D3DTSS_COLORARG1,D3DTA_TEXTURE);

    IDirect3DDevice9_SetTextureStageState(d3ddev, 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
    IDirect3DDevice9_SetTextureStageState(d3ddev, 0, D3DTSS_ALPHAARG1,D3DTA_TEXTURE);
    IDirect3DDevice9_SetTextureStageState(d3ddev, 0, D3DTSS_ALPHAARG2,D3DTA_DIFFUSE);

    msg_Dbg(vd, "Direct3D9 scene created successfully");

    return VLC_SUCCESS;
}