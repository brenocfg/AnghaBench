#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {TYPE_5__* sys; } ;
typedef  TYPE_4__ vlc_va_t ;
struct TYPE_22__ {int /*<<< orphan*/  decoder; } ;
struct TYPE_28__ {int ConfigBitstreamRaw; int /*<<< orphan*/  guidConfigBitstreamEncryption; } ;
struct TYPE_24__ {int /*<<< orphan*/ ** hw_surface; TYPE_3__ hw; TYPE_9__ cfg; TYPE_2__* selected_decoder; int /*<<< orphan*/  d3ddec; int /*<<< orphan*/  render; } ;
typedef  TYPE_5__ vlc_va_sys_t ;
struct TYPE_25__ {scalar_t__ i_frame_rate; scalar_t__ i_frame_rate_base; int /*<<< orphan*/  i_height; int /*<<< orphan*/  i_width; } ;
typedef  TYPE_6__ video_format_t ;
typedef  int /*<<< orphan*/  dsc ;
typedef  unsigned int UINT ;
struct TYPE_27__ {scalar_t__ VideoTransferFunction; scalar_t__ VideoPrimaries; scalar_t__ VideoLighting; scalar_t__ VideoTransferMatrix; scalar_t__ NominalRange; scalar_t__ VideoChromaSubsampling; scalar_t__ SampleFormat; } ;
struct TYPE_20__ {scalar_t__ Numerator; scalar_t__ Denominator; } ;
struct TYPE_26__ {TYPE_8__ SampleFormat; scalar_t__ Reserved; int /*<<< orphan*/  UABProtectionLevel; TYPE_1__ InputSampleFreq; TYPE_1__ OutputFrameFreq; int /*<<< orphan*/  Format; int /*<<< orphan*/  SampleHeight; int /*<<< orphan*/  SampleWidth; } ;
struct TYPE_21__ {int /*<<< orphan*/  guid; } ;
typedef  int /*<<< orphan*/  IDirect3DSurface9 ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_7__ DXVA2_VideoDesc ;
typedef  TYPE_8__ DXVA2_ExtendedFormat ;
typedef  TYPE_9__ DXVA2_ConfigPictureDecode ;

/* Variables and functions */
 int AV_CODEC_ID_H264 ; 
 int /*<<< orphan*/  CoTaskMemFree (TYPE_9__*) ; 
 int /*<<< orphan*/  D3DPOOL_DEFAULT ; 
 int /*<<< orphan*/  DXVA2_NoEncrypt ; 
 int /*<<< orphan*/  DXVA2_VideoDecoderRenderTarget ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IDirect3DSurface9_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirectXVideoDecoderService_CreateSurface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirectXVideoDecoderService_CreateVideoDecoder (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_7__*,TYPE_9__*,int /*<<< orphan*/ **,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirectXVideoDecoderService_GetDecoderConfigurations (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ *,unsigned int*,TYPE_9__**) ; 
 scalar_t__ IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_7__*,int) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_4__*,char*,...) ; 
 int /*<<< orphan*/  msg_Err (TYPE_4__*,char*,...) ; 

__attribute__((used)) static int DxCreateVideoDecoder(vlc_va_t *va, int codec_id,
                                const video_format_t *fmt, size_t surface_count)
{
    vlc_va_sys_t *sys = va->sys;
    HRESULT hr;

    hr = IDirectXVideoDecoderService_CreateSurface(sys->d3ddec,
                                                         fmt->i_width,
                                                         fmt->i_height,
                                                         surface_count - 1,
                                                         sys->render,
                                                         D3DPOOL_DEFAULT,
                                                         0,
                                                         DXVA2_VideoDecoderRenderTarget,
                                                         sys->hw_surface,
                                                         NULL);
    if (FAILED(hr)) {
        msg_Err(va, "IDirectXVideoAccelerationService_CreateSurface %zu failed (hr=0x%lX)", surface_count - 1, hr);
        return VLC_EGENERIC;
    }
    msg_Dbg(va, "IDirectXVideoAccelerationService_CreateSurface succeed with %zu surfaces (%dx%d)",
            surface_count, fmt->i_width, fmt->i_height);

    IDirect3DSurface9 *tstCrash;
    hr = IDirectXVideoDecoderService_CreateSurface(sys->d3ddec,
                                                         fmt->i_width,
                                                         fmt->i_height,
                                                         0,
                                                         sys->render,
                                                         D3DPOOL_DEFAULT,
                                                         0,
                                                         DXVA2_VideoDecoderRenderTarget,
                                                         &tstCrash,
                                                         NULL);
    if (FAILED(hr)) {
        msg_Err(va, "extra buffer impossible, avoid a crash (hr=0x%lX)", hr);
        goto error;
    }
    IDirect3DSurface9_Release(tstCrash);

    /* */
    DXVA2_VideoDesc dsc;
    ZeroMemory(&dsc, sizeof(dsc));
    dsc.SampleWidth     = fmt->i_width;
    dsc.SampleHeight    = fmt->i_height;
    dsc.Format          = sys->render;
    if (fmt->i_frame_rate > 0 && fmt->i_frame_rate_base > 0) {
        dsc.InputSampleFreq.Numerator   = fmt->i_frame_rate;
        dsc.InputSampleFreq.Denominator = fmt->i_frame_rate_base;
    } else {
        dsc.InputSampleFreq.Numerator   = 0;
        dsc.InputSampleFreq.Denominator = 0;
    }
    dsc.OutputFrameFreq = dsc.InputSampleFreq;
    dsc.UABProtectionLevel = FALSE;
    dsc.Reserved = 0;

    /* FIXME I am unsure we can let unknown everywhere */
    DXVA2_ExtendedFormat *ext = &dsc.SampleFormat;
    ext->SampleFormat = 0;//DXVA2_SampleUnknown;
    ext->VideoChromaSubsampling = 0;//DXVA2_VideoChromaSubsampling_Unknown;
    ext->NominalRange = 0;//DXVA2_NominalRange_Unknown;
    ext->VideoTransferMatrix = 0;//DXVA2_VideoTransferMatrix_Unknown;
    ext->VideoLighting = 0;//DXVA2_VideoLighting_Unknown;
    ext->VideoPrimaries = 0;//DXVA2_VideoPrimaries_Unknown;
    ext->VideoTransferFunction = 0;//DXVA2_VideoTransFunc_Unknown;

    /* List all configurations available for the decoder */
    UINT                      cfg_count = 0;
    DXVA2_ConfigPictureDecode *cfg_list = NULL;
    hr = IDirectXVideoDecoderService_GetDecoderConfigurations(sys->d3ddec,
                                                              sys->selected_decoder->guid,
                                                              &dsc,
                                                              NULL,
                                                              &cfg_count,
                                                              &cfg_list);
    if (FAILED(hr)) {
        msg_Err(va, "IDirectXVideoDecoderService_GetDecoderConfigurations failed. (hr=0x%lX)", hr);
        goto error;
    }
    msg_Dbg(va, "we got %d decoder configurations", cfg_count);

    /* Select the best decoder configuration */
    int cfg_score = 0;
    for (unsigned i = 0; i < cfg_count; i++) {
        const DXVA2_ConfigPictureDecode *cfg = &cfg_list[i];

        /* */
        msg_Dbg(va, "configuration[%d] ConfigBitstreamRaw %d",
                i, cfg->ConfigBitstreamRaw);

        /* */
        int score;
        if (cfg->ConfigBitstreamRaw == 1)
            score = 1;
        else if (codec_id == AV_CODEC_ID_H264 && cfg->ConfigBitstreamRaw == 2)
            score = 2;
        else
            continue;
        if (IsEqualGUID(&cfg->guidConfigBitstreamEncryption, &DXVA2_NoEncrypt))
            score += 16;

        if (cfg_score < score) {
            sys->cfg = *cfg;
            cfg_score = score;
        }
    }
    CoTaskMemFree(cfg_list);
    if (cfg_score <= 0) {
        msg_Err(va, "Failed to find a supported decoder configuration");
        goto error;
    }

    /* Create the decoder */
    /* adds a reference on each decoder surface */
    if (FAILED(IDirectXVideoDecoderService_CreateVideoDecoder(sys->d3ddec,
                                                              sys->selected_decoder->guid,
                                                              &dsc,
                                                              &sys->cfg,
                                                              sys->hw_surface,
                                                              surface_count,
                                                              &sys->hw.decoder))) {
        msg_Err(va, "IDirectXVideoDecoderService_CreateVideoDecoder failed");
        goto error;
    }

    msg_Dbg(va, "IDirectXVideoDecoderService_CreateVideoDecoder succeed");
    return VLC_SUCCESS;
error:
    for (size_t i = 0; i < surface_count; i++)
        IDirect3DSurface9_Release( sys->hw_surface[i] );
    return VLC_EGENERIC;
}