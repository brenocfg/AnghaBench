#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_8__ ;
typedef  struct TYPE_34__   TYPE_7__ ;
typedef  struct TYPE_33__   TYPE_6__ ;
typedef  struct TYPE_32__   TYPE_5__ ;
typedef  struct TYPE_31__   TYPE_4__ ;
typedef  struct TYPE_30__   TYPE_3__ ;
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_20__ ;
typedef  struct TYPE_27__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const uint8_t ;
struct TYPE_27__ {scalar_t__ i_chroma; scalar_t__ i_visible_height; scalar_t__ i_y_offset; } ;
struct TYPE_29__ {TYPE_1__ format; int /*<<< orphan*/ * context; } ;
typedef  TYPE_2__ picture_t ;
struct TYPE_30__ {int /*<<< orphan*/  context; int /*<<< orphan*/  processorInput; int /*<<< orphan*/ ** resource; scalar_t__ slice_index; } ;
typedef  TYPE_3__ picture_sys_d3d11_t ;
struct TYPE_31__ {TYPE_5__* p_sys; } ;
typedef  TYPE_4__ filter_t ;
struct TYPE_28__ {int /*<<< orphan*/  videoProcessor; int /*<<< orphan*/  d3dvidctx; scalar_t__ procEnumerator; } ;
struct TYPE_32__ {int /*<<< orphan*/  staging_lock; int /*<<< orphan*/  staging_resource; int /*<<< orphan*/  cache; int /*<<< orphan*/  staging; int /*<<< orphan*/ * procOutResource; int /*<<< orphan*/  processorOutput; TYPE_20__ d3d_proc; } ;
typedef  TYPE_5__ filter_sys_t ;
typedef  scalar_t__ UINT ;
struct TYPE_35__ {int RowPitch; int /*<<< orphan*/  const* pData; } ;
struct TYPE_34__ {scalar_t__ Format; size_t const Height; } ;
struct TYPE_33__ {int /*<<< orphan*/  pInputSurface; int /*<<< orphan*/  Enable; } ;
typedef  int /*<<< orphan*/  ID3D11Resource ;
typedef  scalar_t__ HRESULT ;
typedef  TYPE_6__ D3D11_VIDEO_PROCESSOR_STREAM ;
typedef  TYPE_7__ D3D11_TEXTURE2D_DESC ;
typedef  TYPE_8__ D3D11_MAPPED_SUBRESOURCE ;

/* Variables and functions */
 TYPE_3__* ActiveD3D11PictureSys (TYPE_2__*) ; 
 int /*<<< orphan*/  Copy420_16_SP_to_P (TYPE_2__*,int /*<<< orphan*/  const**,size_t const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Copy420_P_to_P (TYPE_2__*,int /*<<< orphan*/  const**,size_t const*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Copy420_SP_to_P (TYPE_2__*,int /*<<< orphan*/  const**,size_t const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ D3D11_Assert_ProcessorInput (TYPE_4__*,TYPE_20__*,TYPE_3__*) ; 
 int /*<<< orphan*/  D3D11_MAP_READ ; 
 scalar_t__ DXGI_FORMAT_NV12 ; 
 scalar_t__ DXGI_FORMAT_P010 ; 
 scalar_t__ DXGI_FORMAT_YUY2 ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  ID3D11DeviceContext_CopySubresourceRegion (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ ID3D11DeviceContext_Map (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_8__*) ; 
 int /*<<< orphan*/  ID3D11DeviceContext_Unmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ID3D11Texture2D_GetDesc (int /*<<< orphan*/ ,TYPE_7__*) ; 
 scalar_t__ ID3D11VideoContext_VideoProcessorBlt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_6__*) ; 
 size_t KNOWN_DXGI_INDEX ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ VLC_CODEC_I420 ; 
 scalar_t__ VLC_CODEC_I420_10L ; 
 scalar_t__ VLC_SUCCESS ; 
 int /*<<< orphan*/  __MIN (int,scalar_t__) ; 
 scalar_t__ assert_staging (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_4__*,char*,...) ; 
 int /*<<< orphan*/  picture_SwapUV (TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void D3D11_YUY2(filter_t *p_filter, picture_t *src, picture_t *dst)
{
    if (src->context == NULL)
    {
        /* the previous stages creating a D3D11 picture should always fill the context */
        msg_Err(p_filter, "missing source context");
        return;
    }

    filter_sys_t *sys = p_filter->p_sys;
    picture_sys_d3d11_t *p_sys = ActiveD3D11PictureSys(src);

    D3D11_TEXTURE2D_DESC desc;
    D3D11_MAPPED_SUBRESOURCE lock;

    vlc_mutex_lock(&sys->staging_lock);
    if (assert_staging(p_filter, p_sys) != VLC_SUCCESS)
    {
        vlc_mutex_unlock(&sys->staging_lock);
        return;
    }

    UINT srcSlice = p_sys->slice_index;
    ID3D11Resource *srcResource = p_sys->resource[KNOWN_DXGI_INDEX];

#if CAN_PROCESSOR
    if (sys->d3d_proc.procEnumerator)
    {
        HRESULT hr;
        if (FAILED( D3D11_Assert_ProcessorInput(p_filter, &sys->d3d_proc, p_sys) ))
            return;

        D3D11_VIDEO_PROCESSOR_STREAM stream = {
            .Enable = TRUE,
            .pInputSurface = p_sys->processorInput,
        };

        hr = ID3D11VideoContext_VideoProcessorBlt(sys->d3d_proc.d3dvidctx, sys->d3d_proc.videoProcessor,
                                                          sys->processorOutput,
                                                          0, 1, &stream);
        if (FAILED(hr))
        {
            msg_Err(p_filter, "Failed to process the video. (hr=0x%lX)", hr);
            vlc_mutex_unlock(&sys->staging_lock);
            return;
        }

        srcResource = sys->procOutResource;
        srcSlice = 0;
    }
#endif
    ID3D11DeviceContext_CopySubresourceRegion(p_sys->context, sys->staging_resource,
                                              0, 0, 0, 0,
                                              srcResource,
                                              srcSlice,
                                              NULL);

    HRESULT hr = ID3D11DeviceContext_Map(p_sys->context, sys->staging_resource,
                                         0, D3D11_MAP_READ, 0, &lock);
    if (FAILED(hr)) {
        msg_Err(p_filter, "Failed to map source surface. (hr=0x%lX)", hr);
        vlc_mutex_unlock(&sys->staging_lock);
        return;
    }

    if (dst->format.i_chroma == VLC_CODEC_I420)
        picture_SwapUV( dst );

    ID3D11Texture2D_GetDesc(sys->staging, &desc);

    if (desc.Format == DXGI_FORMAT_YUY2) {
        size_t chroma_pitch = (lock.RowPitch / 2);

        const size_t pitch[3] = {
            lock.RowPitch,
            chroma_pitch,
            chroma_pitch,
        };

        const uint8_t *plane[3] = {
            (uint8_t*)lock.pData,
            (uint8_t*)lock.pData + pitch[0] * desc.Height,
            (uint8_t*)lock.pData + pitch[0] * desc.Height
                                 + pitch[1] * desc.Height / 2,
        };

        Copy420_P_to_P(dst, plane, pitch,
                       src->format.i_visible_height + src->format.i_y_offset,
                       &sys->cache);
    } else if (desc.Format == DXGI_FORMAT_NV12 ||
               desc.Format == DXGI_FORMAT_P010) {
        const uint8_t *plane[2] = {
            lock.pData,
            (uint8_t*)lock.pData + lock.RowPitch * desc.Height
        };
        const size_t  pitch[2] = {
            lock.RowPitch,
            lock.RowPitch,
        };
        if (desc.Format == DXGI_FORMAT_NV12)
            Copy420_SP_to_P(dst, plane, pitch,
                            __MIN(desc.Height, src->format.i_y_offset + src->format.i_visible_height),
                            &sys->cache);
        else
            Copy420_16_SP_to_P(dst, plane, pitch,
                               __MIN(desc.Height, src->format.i_y_offset + src->format.i_visible_height),
                               6, &sys->cache);
        picture_SwapUV(dst);
    } else {
        msg_Err(p_filter, "Unsupported D3D11VA conversion from 0x%08X to YV12", desc.Format);
    }

    if (dst->format.i_chroma == VLC_CODEC_I420 || dst->format.i_chroma == VLC_CODEC_I420_10L)
        picture_SwapUV( dst );

    /* */
    ID3D11DeviceContext_Unmap(p_sys->context, sys->staging_resource, 0);
    vlc_mutex_unlock(&sys->staging_lock);
}