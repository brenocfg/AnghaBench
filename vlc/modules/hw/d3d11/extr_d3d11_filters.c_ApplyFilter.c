#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ i_visible_height; scalar_t__ i_visible_width; scalar_t__ i_y_offset; scalar_t__ i_x_offset; } ;
typedef  TYPE_3__ video_format_t ;
struct TYPE_12__ {int Default; } ;
struct filter_level {TYPE_1__ Range; int /*<<< orphan*/  level; } ;
struct TYPE_13__ {int /*<<< orphan*/  videoProcessor; int /*<<< orphan*/  d3dvidctx; } ;
struct TYPE_15__ {TYPE_2__ d3d_proc; } ;
typedef  TYPE_4__ filter_sys_t ;
struct TYPE_17__ {int /*<<< orphan*/ * pInputSurface; int /*<<< orphan*/  Enable; int /*<<< orphan*/  member_0; } ;
struct TYPE_16__ {scalar_t__ top; scalar_t__ bottom; scalar_t__ left; scalar_t__ right; } ;
typedef  TYPE_5__ RECT ;
typedef  int /*<<< orphan*/  ID3D11VideoProcessorOutputView ;
typedef  int /*<<< orphan*/  ID3D11VideoProcessorInputView ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_6__ D3D11_VIDEO_PROCESSOR_STREAM ;
typedef  int /*<<< orphan*/  D3D11_VIDEO_PROCESSOR_FILTER ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  ID3D11VideoContext_VideoProcessorBlt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,TYPE_6__*) ; 
 int /*<<< orphan*/  ID3D11VideoContext_VideoProcessorSetStreamAutoProcessingMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ID3D11VideoContext_VideoProcessorSetStreamDestRect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  ID3D11VideoContext_VideoProcessorSetStreamFilter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ID3D11VideoContext_VideoProcessorSetStreamSourceRect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int atomic_load (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool ApplyFilter( filter_sys_t *p_sys,
                         D3D11_VIDEO_PROCESSOR_FILTER filter,
                         struct filter_level *p_level,
                         ID3D11VideoProcessorInputView *input,
                         ID3D11VideoProcessorOutputView *output,
                         const video_format_t *fmt)
{
    HRESULT hr;

    int level = atomic_load(&p_level->level);
    if (level == p_level->Range.Default)
        return false;

    ID3D11VideoContext_VideoProcessorSetStreamFilter(p_sys->d3d_proc.d3dvidctx,
                                                     p_sys->d3d_proc.videoProcessor,
                                                     0,
                                                     filter,
                                                     TRUE,
                                                     level);
    ID3D11VideoContext_VideoProcessorSetStreamAutoProcessingMode(p_sys->d3d_proc.d3dvidctx,
                                                                 p_sys->d3d_proc.videoProcessor,
                                                                 0, FALSE);

    RECT srcRect;
    srcRect.left   = fmt->i_x_offset;
    srcRect.top    = fmt->i_y_offset;
    srcRect.right  = srcRect.left + fmt->i_visible_width;
    srcRect.bottom = srcRect.top  + fmt->i_visible_height;
    ID3D11VideoContext_VideoProcessorSetStreamSourceRect(p_sys->d3d_proc.d3dvidctx, p_sys->d3d_proc.videoProcessor,
                                                         0, TRUE, &srcRect);
    ID3D11VideoContext_VideoProcessorSetStreamDestRect(p_sys->d3d_proc.d3dvidctx, p_sys->d3d_proc.videoProcessor,
                                                       0, TRUE, &srcRect);

    D3D11_VIDEO_PROCESSOR_STREAM stream = {0};
    stream.Enable = TRUE;
    stream.pInputSurface = input;

    hr = ID3D11VideoContext_VideoProcessorBlt(p_sys->d3d_proc.d3dvidctx,
                                              p_sys->d3d_proc.videoProcessor,
                                              output,
                                              0, 1, &stream);
    return SUCCEEDED(hr);
}