#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_9__ {scalar_t__ i_chroma; scalar_t__ i_width; scalar_t__ i_height; scalar_t__ orientation; } ;
struct TYPE_10__ {TYPE_3__ video; } ;
struct TYPE_7__ {scalar_t__ i_chroma; scalar_t__ i_width; scalar_t__ i_height; scalar_t__ orientation; } ;
struct TYPE_8__ {TYPE_1__ video; } ;
struct TYPE_11__ {TYPE_4__ fmt_out; int /*<<< orphan*/  pf_video_filter; TYPE_2__ fmt_in; } ;
typedef  TYPE_5__ filter_t ;

/* Variables and functions */
 int /*<<< orphan*/  Convert_Filter ; 
 scalar_t__ VLC_CODEC_ARGB ; 
 scalar_t__ VLC_CODEC_BGRA ; 
 scalar_t__ VLC_CODEC_RGBA ; 
 scalar_t__ VLC_CODEC_YUVA ; 
 scalar_t__ VLC_CODEC_YUVP ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_5__*,char*,char const*) ; 

__attribute__((used)) static int Open( vlc_object_t *p_this )
{
    filter_t *p_filter = (filter_t*)p_this;

    /* It only supports YUVP to YUVA/RGBA without scaling
     * (if scaling is required another filter can do it) */
    if( p_filter->fmt_in.video.i_chroma != VLC_CODEC_YUVP ||
        ( p_filter->fmt_out.video.i_chroma != VLC_CODEC_YUVA &&
          p_filter->fmt_out.video.i_chroma != VLC_CODEC_RGBA &&
          p_filter->fmt_out.video.i_chroma != VLC_CODEC_ARGB &&
          p_filter->fmt_out.video.i_chroma != VLC_CODEC_BGRA ) ||
        p_filter->fmt_in.video.i_width  != p_filter->fmt_out.video.i_width ||
        p_filter->fmt_in.video.i_height != p_filter->fmt_out.video.i_height ||
        p_filter->fmt_in.video.orientation != p_filter->fmt_out.video.orientation )
    {
        return VLC_EGENERIC;
    }

    p_filter->pf_video_filter = Convert_Filter;

    msg_Dbg( p_filter, "YUVP to %4.4s converter",
             (const char*)&p_filter->fmt_out.video.i_chroma );

    return VLC_SUCCESS;
}