#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_40__   TYPE_9__ ;
typedef  struct TYPE_39__   TYPE_8__ ;
typedef  struct TYPE_38__   TYPE_7__ ;
typedef  struct TYPE_37__   TYPE_6__ ;
typedef  struct TYPE_36__   TYPE_5__ ;
typedef  struct TYPE_35__   TYPE_4__ ;
typedef  struct TYPE_34__   TYPE_3__ ;
typedef  struct TYPE_33__   TYPE_2__ ;
typedef  struct TYPE_32__   TYPE_25__ ;
typedef  struct TYPE_31__   TYPE_1__ ;
typedef  struct TYPE_30__   TYPE_10__ ;

/* Type definitions */
struct TYPE_33__ {int /*<<< orphan*/  i_chroma; } ;
struct TYPE_31__ {int /*<<< orphan*/ * subpicture_chromas; } ;
struct TYPE_34__ {scalar_t__ max_luminance; } ;
struct TYPE_36__ {scalar_t__ projection_mode; scalar_t__ i_visible_width; scalar_t__ i_visible_height; TYPE_3__ mastering; } ;
struct TYPE_35__ {int /*<<< orphan*/  force; } ;
struct TYPE_38__ {TYPE_8__* sys; int /*<<< orphan*/  close; int /*<<< orphan*/  control; int /*<<< orphan*/  display; int /*<<< orphan*/  prepare; int /*<<< orphan*/  pool; TYPE_2__ fmt; TYPE_1__ info; TYPE_5__ source; TYPE_4__ obj; } ;
typedef  TYPE_7__ vout_display_t ;
struct TYPE_37__ {scalar_t__ MaxTextureWidth; scalar_t__ MaxTextureHeight; int SrcBlendCaps; int DestBlendCaps; int TextureCaps; int TextureOpCaps; } ;
struct TYPE_32__ {TYPE_6__ caps; } ;
struct TYPE_39__ {int reset_device; int lost_not_ready; scalar_t__ d3dregion_format; int /*<<< orphan*/  sys; TYPE_25__ d3d_dev; int /*<<< orphan*/  allow_hw_yuv; int /*<<< orphan*/  hxdll; int /*<<< orphan*/  area; int /*<<< orphan*/ * swapCb; int /*<<< orphan*/  hd3d; int /*<<< orphan*/ * startEndRenderingCb; int /*<<< orphan*/ * updateOutputCb; TYPE_7__* outside_opaque; } ;
typedef  TYPE_8__ vout_display_sys_t ;
typedef  int /*<<< orphan*/  vout_display_cfg_t ;
typedef  int /*<<< orphan*/  vlc_video_context ;
typedef  int /*<<< orphan*/  video_format_t ;
struct TYPE_40__ {int /*<<< orphan*/  dev; } ;
typedef  TYPE_9__ d3d9_video_context_t ;
struct TYPE_30__ {int adapter; int /*<<< orphan*/ * device; } ;
typedef  TYPE_10__ d3d9_decoder_device_t ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/ * HMODULE ;

/* Variables and functions */
 int /*<<< orphan*/  Close ; 
 int /*<<< orphan*/  CommonInit (TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  CommonPlacePicture (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CommonWindowClean (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ CommonWindowInit (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Control ; 
 int /*<<< orphan*/  D3D9_CloneExternal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ D3D9_Create (TYPE_7__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  D3D9_CreateDevice (TYPE_7__*,int /*<<< orphan*/ *,int,TYPE_25__*) ; 
 int /*<<< orphan*/  D3D9_CreateDeviceExternal (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_25__*) ; 
 int /*<<< orphan*/  D3D9_Destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ D3DFMT_UNKNOWN ; 
 int D3DPBLENDCAPS_INVSRCALPHA ; 
 int D3DPBLENDCAPS_SRCALPHA ; 
 int D3DPTEXTURECAPS_ALPHA ; 
 int D3DTEXOPCAPS_MODULATE ; 
 int D3DTEXOPCAPS_SELECTARG1 ; 
 int /*<<< orphan*/  Direct3D9Close (TYPE_7__*) ; 
 int /*<<< orphan*/  Direct3D9Destroy (TYPE_8__*) ; 
 int /*<<< orphan*/  Direct3D9LoadShaderLibrary () ; 
 scalar_t__ Direct3D9Open (TYPE_7__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Display ; 
 int /*<<< orphan*/  DisplayPool ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 TYPE_9__* GetD3D9ContextPrivate (int /*<<< orphan*/ *) ; 
 TYPE_10__* GetD3D9OpaqueContext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetModuleHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GetProcAddress (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * LocalSwapchainSwap ; 
 int /*<<< orphan*/ * LocalSwapchainUpdateOutput ; 
 scalar_t__ PROJECTION_MODE_RECTANGULAR ; 
 int /*<<< orphan*/  Prepare ; 
 int /*<<< orphan*/  TEXT (char*) ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int /*<<< orphan*/  VLC_OBJECT (TYPE_7__*) ; 
 scalar_t__ VLC_SUCCESS ; 
 TYPE_8__* calloc (int,int) ; 
 int /*<<< orphan*/ * d3d_subpicture_chromas ; 
 int /*<<< orphan*/  free (TYPE_8__*) ; 
 scalar_t__ is_d3d9_opaque (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Err (TYPE_7__*,char*,...) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_7__*,char*) ; 
 int /*<<< orphan*/  var_CreateGetBool (TYPE_7__*,char*) ; 
 void* var_InheritAddress (TYPE_7__*,char*) ; 
 scalar_t__ var_InheritBool (TYPE_7__*,char*) ; 
 int /*<<< orphan*/  video_format_Clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_format_Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int Open(vout_display_t *vd, const vout_display_cfg_t *cfg,
                video_format_t *fmtp, vlc_video_context *context)
{
    vout_display_sys_t *sys;

    if ( !vd->obj.force && vd->source.projection_mode != PROJECTION_MODE_RECTANGULAR)
        return VLC_EGENERIC; /* let a module who can handle it do it */

    if ( !vd->obj.force && vd->source.mastering.max_luminance != 0)
        return VLC_EGENERIC; /* let a module who can handle it do it */

    /* do not use D3D9 on XP unless forced */
    if (!vd->obj.force)
    {
        bool isVistaOrGreater = false;
        HMODULE hKernel32 = GetModuleHandle(TEXT("kernel32.dll"));
        if (likely(hKernel32 != NULL))
            isVistaOrGreater = GetProcAddress(hKernel32, "EnumResourceLanguagesExW") != NULL;
        if (!isVistaOrGreater)
            return VLC_EGENERIC;
    }

    /* Allocate structure */
    vd->sys = sys = calloc(1, sizeof(vout_display_sys_t));
    if (!sys)
        return VLC_ENOMEM;

    CommonInit(vd, &sys->area, cfg);

    sys->outside_opaque = var_InheritAddress( vd, "vout-cb-opaque" );
    sys->updateOutputCb      = var_InheritAddress( vd, "vout-cb-update-output" );
    sys->swapCb              = var_InheritAddress( vd, "vout-cb-swap" );
    sys->startEndRenderingCb = var_InheritAddress( vd, "vout-cb-make-current" );

    if ( sys->swapCb == NULL || sys->startEndRenderingCb == NULL || sys->updateOutputCb == NULL )
    {
        /* use our own callbacks, since there isn't any external ones */
        if (CommonWindowInit(VLC_OBJECT(vd), &sys->area, &sys->sys, false))
            goto error;

        sys->outside_opaque = vd;
        sys->updateOutputCb      = LocalSwapchainUpdateOutput;
        sys->swapCb              = LocalSwapchainSwap;
        sys->startEndRenderingCb = NULL;
    }

    d3d9_decoder_device_t *d3d9_decoder = GetD3D9OpaqueContext(context);
    if ( d3d9_decoder == NULL )
    {
        // No d3d9 device, we create one
        if (D3D9_Create(vd, &sys->hd3d) != VLC_SUCCESS)
            goto error;
    }
    if (d3d9_decoder != NULL && d3d9_decoder->device != NULL)
        D3D9_CloneExternal( &sys->hd3d, d3d9_decoder->device );

    d3d9_video_context_t *octx = GetD3D9ContextPrivate(context);
    HRESULT hr;
    if (octx != NULL)
        hr = D3D9_CreateDeviceExternal(octx->dev, &sys->hd3d, &sys->d3d_dev);
    else
        hr = D3D9_CreateDevice(vd, &sys->hd3d, d3d9_decoder ? d3d9_decoder->adapter : -1, &sys->d3d_dev);

    if (FAILED(hr)) {
        msg_Err( vd, "D3D9 Creation failed! (hr=0x%lX)", hr);
        D3D9_Destroy(&sys->hd3d);
        free(sys);
        return VLC_EGENERIC;
    }

    if ( vd->source.i_visible_width  > sys->d3d_dev.caps.MaxTextureWidth ||
         vd->source.i_visible_height > sys->d3d_dev.caps.MaxTextureHeight )
    {
        msg_Err(vd, "Textures too large %ux%u max possible: %lx%lx",
                vd->source.i_visible_width, vd->source.i_visible_height,
                sys->d3d_dev.caps.MaxTextureWidth,
                sys->d3d_dev.caps.MaxTextureHeight);
        goto error;
    }

    if (sys->swapCb == LocalSwapchainSwap)
        CommonPlacePicture(VLC_OBJECT(vd), &sys->area, &sys->sys);

    sys->hxdll = Direct3D9LoadShaderLibrary();
    if (!sys->hxdll)
        msg_Warn(vd, "cannot load Direct3D9 Shader Library; HLSL pixel shading will be disabled.");

    sys->reset_device = false;
    sys->lost_not_ready = false;
    sys->allow_hw_yuv = var_CreateGetBool(vd, "directx-hw-yuv");

    /* */
    video_format_t fmt;
    if (Direct3D9Open(vd, &fmt)) {
        msg_Err(vd, "Direct3D9 could not be opened");
        goto error;
    }

    /* Setup vout_display now that everything is fine */
    if (var_InheritBool(vd, "direct3d9-hw-blending") &&
        sys->d3dregion_format != D3DFMT_UNKNOWN &&
        (sys->d3d_dev.caps.SrcBlendCaps  & D3DPBLENDCAPS_SRCALPHA) &&
        (sys->d3d_dev.caps.DestBlendCaps & D3DPBLENDCAPS_INVSRCALPHA) &&
        (sys->d3d_dev.caps.TextureCaps   & D3DPTEXTURECAPS_ALPHA) &&
        (sys->d3d_dev.caps.TextureOpCaps & D3DTEXOPCAPS_SELECTARG1) &&
        (sys->d3d_dev.caps.TextureOpCaps & D3DTEXOPCAPS_MODULATE))
        vd->info.subpicture_chromas = d3d_subpicture_chromas;
    else
        vd->info.subpicture_chromas = NULL;

    video_format_Clean(fmtp);
    video_format_Copy(fmtp, &fmt);

    if ( is_d3d9_opaque(vd->fmt.i_chroma) )
        vd->pool = DisplayPool;
    vd->prepare = Prepare;
    vd->display = Display;
    vd->control = Control;
    vd->close = Close;

    return VLC_SUCCESS;
error:
    Direct3D9Close(vd);
    CommonWindowClean(VLC_OBJECT(vd), &sys->sys);
    Direct3D9Destroy(sys);
    free(vd->sys);
    return VLC_EGENERIC;
}