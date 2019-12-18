#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_13__ {int /*<<< orphan*/  i_format; int /*<<< orphan*/  i_rate; } ;
struct TYPE_10__ {TYPE_7__ audio; } ;
struct TYPE_9__ {TYPE_7__ audio; } ;
struct TYPE_11__ {int /*<<< orphan*/  pf_audio_filter; TYPE_2__ fmt_in; TYPE_1__ fmt_out; TYPE_4__* p_sys; } ;
typedef  TYPE_3__ filter_t ;
struct TYPE_12__ {double scale; int samples_per_frame; int bytes_per_sample; int bytes_per_frame; scalar_t__ frames_stride_error; scalar_t__ bytes_to_slide; scalar_t__ bytes_queued; scalar_t__ bytes_overlap; int /*<<< orphan*/ * table_window; int /*<<< orphan*/ * buf_pre_corr; int /*<<< orphan*/ * table_blend; int /*<<< orphan*/ * buf_overlap; int /*<<< orphan*/ * buf_queue; void* ms_search; int /*<<< orphan*/  percent_overlap; void* ms_stride; int /*<<< orphan*/  sample_rate; } ;
typedef  TYPE_4__ filter_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  Close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DoWork ; 
 int /*<<< orphan*/  VLC_CODEC_FL32 ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 scalar_t__ VLC_SUCCESS ; 
 int aout_FormatNbChannels (TYPE_7__*) ; 
 int /*<<< orphan*/  aout_FormatPrepare (TYPE_7__*) ; 
 TYPE_4__* malloc (int) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,void*,int,int,...) ; 
 scalar_t__ reinit_buffers (TYPE_3__*) ; 
 int /*<<< orphan*/  var_InheritFloat (int /*<<< orphan*/ *,char*) ; 
 void* var_InheritInteger (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int Open( vlc_object_t *p_this )
{
    filter_t     *p_filter = (filter_t *)p_this;

    /* Allocate structure */
    filter_sys_t *p_sys = p_filter->p_sys = malloc( sizeof(*p_sys) );
    if( ! p_sys )
        return VLC_ENOMEM;

    p_sys->scale             = 1.0;
    p_sys->sample_rate       = p_filter->fmt_in.audio.i_rate;
    p_sys->samples_per_frame = aout_FormatNbChannels( &p_filter->fmt_in.audio );
    p_sys->bytes_per_sample  = 4;
    p_sys->bytes_per_frame   = p_sys->samples_per_frame * p_sys->bytes_per_sample;

    msg_Dbg( p_this, "format: %5i rate, %i nch, %i bps, %s",
             p_sys->sample_rate,
             p_sys->samples_per_frame,
             p_sys->bytes_per_sample,
             "fl32" );

    p_sys->ms_stride       = var_InheritInteger( p_this, "scaletempo-stride" );
    p_sys->percent_overlap = var_InheritFloat( p_this, "scaletempo-overlap" );
    p_sys->ms_search       = var_InheritInteger( p_this, "scaletempo-search" );

    msg_Dbg( p_this, "params: %i stride, %.3f overlap, %i search",
             p_sys->ms_stride, p_sys->percent_overlap, p_sys->ms_search );

    p_sys->buf_queue      = NULL;
    p_sys->buf_overlap    = NULL;
    p_sys->table_blend    = NULL;
    p_sys->buf_pre_corr   = NULL;
    p_sys->table_window   = NULL;
    p_sys->bytes_overlap  = 0;
    p_sys->bytes_queued   = 0;
    p_sys->bytes_to_slide = 0;
    p_sys->frames_stride_error = 0;

    if( reinit_buffers( p_filter ) != VLC_SUCCESS )
    {
        Close( p_this );
        return VLC_EGENERIC;
    }

    p_filter->fmt_in.audio.i_format = VLC_CODEC_FL32;
    aout_FormatPrepare(&p_filter->fmt_in.audio);
    p_filter->fmt_out.audio = p_filter->fmt_in.audio;
    p_filter->pf_audio_filter = DoWork;

    return VLC_SUCCESS;
}