#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_22__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ picture_t ;
struct TYPE_23__ {int /*<<< orphan*/  slice_index; int /*<<< orphan*/ * resource; int /*<<< orphan*/  context; int /*<<< orphan*/ * processorInput; } ;
typedef  TYPE_4__ picture_sys_d3d11_t ;
struct TYPE_20__ {int /*<<< orphan*/  video; } ;
struct TYPE_24__ {TYPE_1__ fmt_out; TYPE_6__* p_sys; } ;
typedef  TYPE_5__ filter_t ;
struct TYPE_25__ {int /*<<< orphan*/  d3d_dev; int /*<<< orphan*/ ** procOutput; TYPE_2__* out; int /*<<< orphan*/  Saturation; int /*<<< orphan*/  Hue; int /*<<< orphan*/  Brightness; int /*<<< orphan*/  Contrast; int /*<<< orphan*/ ** procInput; int /*<<< orphan*/  d3d_proc; } ;
typedef  TYPE_6__ filter_sys_t ;
struct TYPE_21__ {int /*<<< orphan*/  resource; } ;
typedef  int /*<<< orphan*/  ID3D11VideoProcessorOutputView ;
typedef  int /*<<< orphan*/  ID3D11VideoProcessorInputView ;

/* Variables and functions */
 TYPE_4__* ActiveD3D11PictureSys (TYPE_3__*) ; 
 scalar_t__ ApplyFilter (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  D3D11_Assert_ProcessorInput (TYPE_5__*,int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  D3D11_VIDEO_PROCESSOR_FILTER_BRIGHTNESS ; 
 int /*<<< orphan*/  D3D11_VIDEO_PROCESSOR_FILTER_CONTRAST ; 
 int /*<<< orphan*/  D3D11_VIDEO_PROCESSOR_FILTER_HUE ; 
 int /*<<< orphan*/  D3D11_VIDEO_PROCESSOR_FILTER_SATURATION ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ID3D11DeviceContext_CopySubresourceRegion (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 size_t KNOWN_DXGI_INDEX ; 
 int /*<<< orphan*/  d3d11_device_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d3d11_device_unlock (int /*<<< orphan*/ *) ; 
 TYPE_3__* filter_NewPicture (TYPE_5__*) ; 
 int /*<<< orphan*/  picture_CopyProperties (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  picture_Release (TYPE_3__*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static picture_t *Filter(filter_t *p_filter, picture_t *p_pic)
{
    filter_sys_t *p_sys = p_filter->p_sys;

    picture_sys_d3d11_t *p_src_sys = ActiveD3D11PictureSys(p_pic);
    if (FAILED( D3D11_Assert_ProcessorInput(p_filter, &p_sys->d3d_proc, p_src_sys) ))
    {
        picture_Release( p_pic );
        return NULL;
    }

    picture_t *p_outpic = filter_NewPicture( p_filter );
    if( !p_outpic )
    {
        picture_Release( p_pic );
        return NULL;
    }
    picture_sys_d3d11_t *p_out_sys = p_outpic->p_sys;
    if (unlikely(!p_out_sys))
    {
        /* the output filter configuration may have changed since the filter
         * was opened */
        picture_Release( p_pic );
        return NULL;
    }

    picture_CopyProperties( p_outpic, p_pic );

    ID3D11VideoProcessorInputView *inputs[4] = {
        p_src_sys->processorInput,
        p_sys->procInput[0],
        p_sys->procInput[1],
        p_sys->procInput[0]
    };

    ID3D11VideoProcessorOutputView *outputs[4] = {
        p_sys->procOutput[0],
        p_sys->procOutput[1],
        p_sys->procOutput[0],
        p_sys->procOutput[1]
    };

    d3d11_device_lock( &p_sys->d3d_dev );

    size_t idx = 0, count = 0;
    /* contrast */
    if ( ApplyFilter( p_sys,
                      D3D11_VIDEO_PROCESSOR_FILTER_CONTRAST, &p_sys->Contrast,
                      inputs[idx], outputs[idx], &p_filter->fmt_out.video ) )
    {
        idx++;
        count++;
    }
    /* brightness */
    if ( ApplyFilter( p_sys,
                      D3D11_VIDEO_PROCESSOR_FILTER_BRIGHTNESS, &p_sys->Brightness,
                      inputs[idx], outputs[idx], &p_filter->fmt_out.video ) )
    {
        idx++;
        count++;
    }
    /* hue */
    if ( ApplyFilter( p_sys,
                      D3D11_VIDEO_PROCESSOR_FILTER_HUE, &p_sys->Hue,
                      inputs[idx], outputs[idx], &p_filter->fmt_out.video ) )
    {
        idx++;
        count++;
    }
    /* saturation */
    if ( ApplyFilter( p_sys,
                      D3D11_VIDEO_PROCESSOR_FILTER_SATURATION, &p_sys->Saturation,
                      inputs[idx], outputs[idx], &p_filter->fmt_out.video ) )
    {
        idx++;
        count++;
    }

    if (count == 0)
    {
        ID3D11DeviceContext_CopySubresourceRegion(p_out_sys->context,
                                                  p_out_sys->resource[KNOWN_DXGI_INDEX],
                                                  p_out_sys->slice_index,
                                                  0, 0, 0,
                                                  p_src_sys->resource[KNOWN_DXGI_INDEX],
                                                  p_src_sys->slice_index,
                                                  NULL);
    }
    else
    {
        ID3D11DeviceContext_CopySubresourceRegion(p_out_sys->context,
                                                  p_out_sys->resource[KNOWN_DXGI_INDEX],
                                                  p_out_sys->slice_index,
                                                  0, 0, 0,
                                                  p_sys->out[outputs[idx] == p_sys->procOutput[0] ? 1 : 0].resource,
                                                  0,
                                                  NULL);
    }

    d3d11_device_unlock( &p_sys->d3d_dev );

    picture_Release( p_pic );
    return p_outpic;
}