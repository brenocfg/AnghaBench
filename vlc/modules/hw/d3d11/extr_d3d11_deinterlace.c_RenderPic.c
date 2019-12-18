#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_9__ ;
typedef  struct TYPE_30__   TYPE_8__ ;
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_18__ ;

/* Type definitions */
struct TYPE_24__ {int /*<<< orphan*/  i_width; int /*<<< orphan*/  i_height; scalar_t__ i_visible_height; scalar_t__ i_visible_width; scalar_t__ i_y_offset; scalar_t__ i_x_offset; } ;
struct TYPE_25__ {TYPE_2__ format; } ;
typedef  TYPE_3__ picture_t ;
struct TYPE_26__ {int /*<<< orphan*/  slice_index; int /*<<< orphan*/ * resource; int /*<<< orphan*/  context; int /*<<< orphan*/  processorInput; } ;
typedef  TYPE_4__ picture_sys_d3d11_t ;
struct TYPE_27__ {TYPE_6__* p_sys; } ;
typedef  TYPE_5__ filter_t ;
struct TYPE_22__ {int /*<<< orphan*/  videoProcessor; int /*<<< orphan*/  d3dvidctx; } ;
struct TYPE_23__ {TYPE_3__** pp_history; } ;
struct TYPE_28__ {int /*<<< orphan*/  outResource; int /*<<< orphan*/  processorOutput; TYPE_18__ d3d_proc; TYPE_1__ context; } ;
typedef  TYPE_6__ filter_sys_t ;
struct TYPE_31__ {int back; int /*<<< orphan*/  right; int /*<<< orphan*/  left; int /*<<< orphan*/  bottom; int /*<<< orphan*/  top; } ;
struct TYPE_30__ {int InputFrameOrField; int PastFrames; int FutureFrames; int /*<<< orphan*/  pInputSurface; int /*<<< orphan*/ * ppPastSurfaces; int /*<<< orphan*/ * ppFutureSurfaces; int /*<<< orphan*/  Enable; int /*<<< orphan*/  member_0; } ;
struct TYPE_29__ {scalar_t__ top; scalar_t__ bottom; scalar_t__ left; scalar_t__ right; } ;
typedef  TYPE_7__ RECT ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_8__ D3D11_VIDEO_PROCESSOR_STREAM ;
typedef  int /*<<< orphan*/  D3D11_VIDEO_FRAME_FORMAT ;
typedef  TYPE_9__ D3D11_BOX ;

/* Variables and functions */
 TYPE_4__* ActiveD3D11PictureSys (TYPE_3__*) ; 
 int /*<<< orphan*/  D3D11_Assert_ProcessorInput (TYPE_5__*,TYPE_18__*,TYPE_4__*) ; 
 int /*<<< orphan*/  D3D11_VIDEO_FRAME_FORMAT_INTERLACED_BOTTOM_FIELD_FIRST ; 
 int /*<<< orphan*/  D3D11_VIDEO_FRAME_FORMAT_INTERLACED_TOP_FIELD_FIRST ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  ID3D11DeviceContext_CopySubresourceRegion (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_9__*) ; 
 int /*<<< orphan*/  ID3D11VideoContext_VideoProcessorBlt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_8__*) ; 
 int /*<<< orphan*/  ID3D11VideoContext_VideoProcessorSetStreamAutoProcessingMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ID3D11VideoContext_VideoProcessorSetStreamDestRect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  ID3D11VideoContext_VideoProcessorSetStreamFrameFormat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ID3D11VideoContext_VideoProcessorSetStreamSourceRect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_7__*) ; 
 size_t KNOWN_DXGI_INDEX ; 
 int /*<<< orphan*/  TRUE ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_UNUSED (int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int RenderPic( filter_t *p_filter, picture_t *p_outpic, picture_t *p_pic,
                      int order, int i_field )
{
    VLC_UNUSED(order);
    HRESULT hr;
    filter_sys_t *p_sys = p_filter->p_sys;
    picture_sys_d3d11_t *p_out_sys = ActiveD3D11PictureSys(p_outpic);

    picture_t *p_prev = p_sys->context.pp_history[0];
    picture_t *p_cur  = p_sys->context.pp_history[1];
    picture_t *p_next = p_sys->context.pp_history[2];

    /* TODO adjust the format if it's the first or second field ? */
    D3D11_VIDEO_FRAME_FORMAT frameFormat = !i_field ?
                D3D11_VIDEO_FRAME_FORMAT_INTERLACED_TOP_FIELD_FIRST :
                D3D11_VIDEO_FRAME_FORMAT_INTERLACED_BOTTOM_FIELD_FIRST;

    ID3D11VideoContext_VideoProcessorSetStreamFrameFormat(p_sys->d3d_proc.d3dvidctx, p_sys->d3d_proc.videoProcessor, 0, frameFormat);
    ID3D11VideoContext_VideoProcessorSetStreamAutoProcessingMode(p_sys->d3d_proc.d3dvidctx, p_sys->d3d_proc.videoProcessor, 0, FALSE);

    D3D11_VIDEO_PROCESSOR_STREAM stream = {0};
    stream.Enable = TRUE;
    stream.InputFrameOrField = i_field ? 1 : 0;

    if( p_cur && p_next )
    {
        picture_sys_d3d11_t *picsys_next = ActiveD3D11PictureSys(p_next);
        if ( unlikely(!picsys_next) || FAILED(D3D11_Assert_ProcessorInput(p_filter, &p_sys->d3d_proc, picsys_next) ))
            return VLC_EGENERIC;

        picture_sys_d3d11_t *picsys_cur = ActiveD3D11PictureSys(p_cur);
        if ( unlikely(!picsys_cur) || FAILED( D3D11_Assert_ProcessorInput(p_filter, &p_sys->d3d_proc, picsys_cur) ))
            return VLC_EGENERIC;

        if ( p_prev )
        {
            picture_sys_d3d11_t *picsys_prev = ActiveD3D11PictureSys(p_prev);
            if ( unlikely(!picsys_prev) || FAILED( D3D11_Assert_ProcessorInput(p_filter, &p_sys->d3d_proc, picsys_prev) ))
                return VLC_EGENERIC;

            stream.pInputSurface    = picsys_cur->processorInput;
            stream.ppFutureSurfaces = &picsys_next->processorInput;
            stream.ppPastSurfaces   = &picsys_prev->processorInput;

            stream.PastFrames   = 1;
            stream.FutureFrames = 1;
        }
        else
        {
            /* p_next is the current, p_cur is the previous frame */
            stream.pInputSurface  = picsys_next->processorInput;
            stream.ppPastSurfaces = &picsys_cur->processorInput;
            stream.PastFrames = 1;
        }
    }
    else
    {
        picture_sys_d3d11_t *p_sys_src = ActiveD3D11PictureSys(p_pic);
        if ( unlikely(!p_sys_src) || FAILED( D3D11_Assert_ProcessorInput(p_filter, &p_sys->d3d_proc, p_sys_src) ))
            return VLC_EGENERIC;

        /* first single frame */
        stream.pInputSurface = p_sys_src->processorInput;
    }

    RECT srcRect;
    srcRect.left   = p_pic->format.i_x_offset;
    srcRect.top    = p_pic->format.i_y_offset;
    srcRect.right  = srcRect.left + p_pic->format.i_visible_width;
    srcRect.bottom = srcRect.top  + p_pic->format.i_visible_height;
    ID3D11VideoContext_VideoProcessorSetStreamSourceRect(p_sys->d3d_proc.d3dvidctx, p_sys->d3d_proc.videoProcessor,
                                                         0, TRUE, &srcRect);
    ID3D11VideoContext_VideoProcessorSetStreamDestRect(p_sys->d3d_proc.d3dvidctx, p_sys->d3d_proc.videoProcessor,
                                                         0, TRUE, &srcRect);

    hr = ID3D11VideoContext_VideoProcessorBlt(p_sys->d3d_proc.d3dvidctx, p_sys->d3d_proc.videoProcessor,
                                              p_sys->processorOutput,
                                              0, 1, &stream);
    if (FAILED(hr))
        return VLC_EGENERIC;

    D3D11_BOX box = {
        .top = 0,
        .bottom = p_outpic->format.i_height,
        .left = 0,
        .right = p_outpic->format.i_width,
        .back = 1,
    };

    ID3D11DeviceContext_CopySubresourceRegion(p_out_sys->context,
                                              p_out_sys->resource[KNOWN_DXGI_INDEX],
                                              p_out_sys->slice_index,
                                              0, 0, 0,
                                              p_sys->outResource,
                                              0, &box);
    return VLC_SUCCESS;
}