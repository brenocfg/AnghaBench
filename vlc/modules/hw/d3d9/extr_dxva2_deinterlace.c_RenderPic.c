#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_37__   TYPE_9__ ;
typedef  struct TYPE_36__   TYPE_8__ ;
typedef  struct TYPE_35__   TYPE_7__ ;
typedef  struct TYPE_34__   TYPE_6__ ;
typedef  struct TYPE_33__   TYPE_5__ ;
typedef  struct TYPE_32__   TYPE_4__ ;
typedef  struct TYPE_31__   TYPE_3__ ;
typedef  struct TYPE_30__   TYPE_2__ ;
typedef  struct TYPE_29__   TYPE_1__ ;
typedef  struct TYPE_28__   TYPE_18__ ;
typedef  struct TYPE_27__   TYPE_11__ ;
typedef  struct TYPE_26__   TYPE_10__ ;

/* Type definitions */
struct TYPE_33__ {int /*<<< orphan*/  format; TYPE_6__* p_sys; } ;
typedef  TYPE_5__ picture_t ;
struct TYPE_34__ {int /*<<< orphan*/  surface; } ;
typedef  TYPE_6__ picture_sys_d3d9_t ;
struct TYPE_30__ {int /*<<< orphan*/  video; } ;
struct TYPE_35__ {TYPE_2__ fmt_out; TYPE_8__* p_sys; } ;
typedef  TYPE_7__ filter_t ;
struct TYPE_32__ {int /*<<< orphan*/  dev; } ;
struct TYPE_28__ {TYPE_5__** pp_history; } ;
struct TYPE_29__ {int NumBackwardRefSamples; int NumForwardRefSamples; } ;
struct TYPE_36__ {int /*<<< orphan*/  hw_surface; TYPE_4__ d3d_dev; int /*<<< orphan*/  processor; TYPE_18__ context; TYPE_1__ decoder_caps; } ;
typedef  TYPE_8__ filter_sys_t ;
struct TYPE_37__ {void* right; void* bottom; scalar_t__ left; scalar_t__ top; } ;
struct TYPE_31__ {int /*<<< orphan*/  SampleFormat; } ;
struct TYPE_27__ {int /*<<< orphan*/  Width; int /*<<< orphan*/  Height; } ;
struct TYPE_26__ {TYPE_3__ SampleFormat; } ;
typedef  TYPE_9__ RECT ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_10__ DXVA2_VideoSample ;
typedef  int /*<<< orphan*/  DXVA2_VideoProcessBltParams ;
typedef  TYPE_11__ D3DSURFACE_DESC ;

/* Variables and functions */
 TYPE_6__* ActiveD3D9PictureSys (TYPE_5__*) ; 
 int /*<<< orphan*/  D3DTEXF_NONE ; 
 int /*<<< orphan*/  DXVA2_SampleUnknown ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FillBlitParams (TYPE_8__*,int /*<<< orphan*/ *,TYPE_9__*,TYPE_10__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FillSample (TYPE_10__*,TYPE_18__*,TYPE_5__*,int /*<<< orphan*/ *,TYPE_9__*,int) ; 
 int /*<<< orphan*/  IDirect3DDevice9_StretchRect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirect3DSurface9_GetDesc (int /*<<< orphan*/ ,TYPE_11__*) ; 
 int /*<<< orphan*/  IDirectXVideoProcessor_VideoProcessBlt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_10__*,int const,int /*<<< orphan*/ *) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 void* __MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (scalar_t__) ; 

__attribute__((used)) static int RenderPic( filter_t *filter, picture_t *p_outpic, picture_t *src,
                      int order, int i_field )
{
    filter_sys_t *sys = filter->p_sys;
    picture_sys_d3d9_t *p_out_sys = p_outpic->p_sys;
    const int i_samples = sys->decoder_caps.NumBackwardRefSamples + 1 +
                          sys->decoder_caps.NumForwardRefSamples;
    HRESULT hr;
    DXVA2_VideoProcessBltParams params;
    DXVA2_VideoSample samples[i_samples];
    picture_t         *pictures[i_samples];
    D3DSURFACE_DESC srcDesc, dstDesc;
    RECT area;

    picture_t *p_prev = sys->context.pp_history[0];
    picture_t *p_cur  = sys->context.pp_history[1];
    picture_t *p_next = sys->context.pp_history[2];

    picture_sys_d3d9_t *p_sys_src = ActiveD3D9PictureSys(src);

    hr = IDirect3DSurface9_GetDesc( p_sys_src->surface, &srcDesc );
    if (unlikely(FAILED(hr)))
        return VLC_EGENERIC;
    hr = IDirect3DSurface9_GetDesc( sys->hw_surface, &dstDesc );
    if (unlikely(FAILED(hr)))
        return VLC_EGENERIC;

    area.top = area.left = 0;
    area.bottom = __MIN(srcDesc.Height, dstDesc.Height);
    area.right  = __MIN(srcDesc.Width,  dstDesc.Width);

    int idx = i_samples - 1;
    if (p_next)
    {
        pictures[idx--] = p_next;
        if (p_cur)
            pictures[idx--] = p_cur;
        if (p_prev)
            pictures[idx--] = p_prev;
    }
    else
        pictures[idx--] = src;
    while (idx >= 0)
        pictures[idx--] = NULL;

    for (idx = 0; idx <= i_samples-1; idx++)
    {
        if (pictures[idx])
            FillSample( &samples[idx], &sys->context, pictures[idx], &filter->fmt_out.video, &area, i_field);
        else
        {
            FillSample( &samples[idx], &sys->context, src, &filter->fmt_out.video, &area, i_field);
            samples[idx].SampleFormat.SampleFormat = DXVA2_SampleUnknown;
        }
    }

    FillBlitParams( sys, &params, &area, samples, order, &p_outpic->format );

    hr = IDirectXVideoProcessor_VideoProcessBlt( sys->processor,
                                                 sys->hw_surface,
                                                 &params,
                                                 samples,
                                                 i_samples, NULL );
    if (FAILED(hr))
        return VLC_EGENERIC;

    hr = IDirect3DDevice9_StretchRect( sys->d3d_dev.dev,
                                       sys->hw_surface, NULL,
                                       p_out_sys->surface, NULL,
                                       D3DTEXF_NONE);
    if (FAILED(hr))
        return VLC_EGENERIC;

    return VLC_SUCCESS;
}