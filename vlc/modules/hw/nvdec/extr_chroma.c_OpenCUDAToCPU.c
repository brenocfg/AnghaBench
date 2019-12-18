#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_7__ {scalar_t__ i_chroma; } ;
struct TYPE_8__ {TYPE_2__ video; } ;
struct TYPE_9__ {scalar_t__ i_chroma; } ;
struct TYPE_6__ {TYPE_4__ video; } ;
struct TYPE_10__ {int /*<<< orphan*/  pf_video_filter; TYPE_3__ fmt_out; TYPE_1__ fmt_in; } ;
typedef  TYPE_5__ filter_t ;

/* Variables and functions */
 int /*<<< orphan*/  FilterCUDAToCPU ; 
 scalar_t__ VLC_CODEC_NV12 ; 
 scalar_t__ VLC_CODEC_NVDEC_OPAQUE ; 
 scalar_t__ VLC_CODEC_NVDEC_OPAQUE_10B ; 
 scalar_t__ VLC_CODEC_NVDEC_OPAQUE_16B ; 
 scalar_t__ VLC_CODEC_P010 ; 
 scalar_t__ VLC_CODEC_P016 ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 

__attribute__((used)) static int OpenCUDAToCPU( vlc_object_t *p_this )
{
    filter_t *p_filter = (filter_t *)p_this;

    if ( !( ( p_filter->fmt_in.video.i_chroma  == VLC_CODEC_NVDEC_OPAQUE &&
              p_filter->fmt_out.video.i_chroma == VLC_CODEC_NV12 ) ||
            ( p_filter->fmt_in.video.i_chroma  == VLC_CODEC_NVDEC_OPAQUE_10B &&
              p_filter->fmt_out.video.i_chroma == VLC_CODEC_P010 ) ||
            ( p_filter->fmt_in.video.i_chroma  == VLC_CODEC_NVDEC_OPAQUE_16B &&
              p_filter->fmt_out.video.i_chroma == VLC_CODEC_P016 )
           ) )
        return VLC_EGENERIC;

    p_filter->pf_video_filter = FilterCUDAToCPU;

    return VLC_SUCCESS;
}