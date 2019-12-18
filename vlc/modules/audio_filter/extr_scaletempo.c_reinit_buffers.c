#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ filter_t ;
struct TYPE_6__ {double ms_stride; double sample_rate; unsigned int bytes_stride; unsigned int bytes_per_frame; unsigned int percent_overlap; unsigned int bytes_overlap; int bytes_standing; int samples_standing; int bytes_per_sample; unsigned int samples_overlap; unsigned int samples_per_frame; float* table_blend; double frames_search; double ms_search; float* table_window; unsigned int bytes_queued; unsigned int bytes_to_slide; unsigned int bytes_queue_max; int bytes_stride_scaled; int scale; int frames_stride_scaled; void* buf_queue; int /*<<< orphan*/ * best_overlap_offset; void* buf_pre_corr; int /*<<< orphan*/ * output_overlap; void* buf_overlap; } ;
typedef  TYPE_2__ filter_sys_t ;

/* Variables and functions */
 int VLC_ENOMEM ; 
 int /*<<< orphan*/  VLC_OBJECT (TYPE_1__*) ; 
 int VLC_SUCCESS ; 
 unsigned int __MIN (unsigned int,unsigned int) ; 
 int /*<<< orphan*/ * best_overlap_offset_float ; 
 void* malloc (unsigned int) ; 
 int /*<<< orphan*/  memmove (void*,void*,unsigned int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ ,char*,int,int,int,int,int,unsigned int,int,char*) ; 
 int /*<<< orphan*/ * output_overlap_float ; 
 void* vlc_alloc (int,unsigned int) ; 

__attribute__((used)) static int reinit_buffers( filter_t *p_filter )
{
    filter_sys_t *p = p_filter->p_sys;
    unsigned i,j;

    unsigned frames_stride = p->ms_stride * p->sample_rate / 1000.0;
    p->bytes_stride = frames_stride * p->bytes_per_frame;

    /* overlap */
    unsigned frames_overlap = frames_stride * p->percent_overlap;
    if( frames_overlap < 1 )
    { /* if no overlap */
        p->bytes_overlap    = 0;
        p->bytes_standing   = p->bytes_stride;
        p->samples_standing = p->bytes_standing / p->bytes_per_sample;
        p->output_overlap   = NULL;
    }
    else
    {
        unsigned prev_overlap   = p->bytes_overlap;
        p->bytes_overlap    = frames_overlap * p->bytes_per_frame;
        p->samples_overlap  = frames_overlap * p->samples_per_frame;
        p->bytes_standing   = p->bytes_stride - p->bytes_overlap;
        p->samples_standing = p->bytes_standing / p->bytes_per_sample;
        p->buf_overlap      = vlc_alloc( 1, p->bytes_overlap );
        p->table_blend      = vlc_alloc( 4, p->samples_overlap ); /* sizeof (int32|float) */
        if( !p->buf_overlap || !p->table_blend )
            return VLC_ENOMEM;
        if( p->bytes_overlap > prev_overlap )
            memset( (uint8_t *)p->buf_overlap + prev_overlap, 0, p->bytes_overlap - prev_overlap );

        float *pb = p->table_blend;
        float t = (float)frames_overlap;
        for( i = 0; i<frames_overlap; i++ )
        {
            float v = i / t;
            for( j = 0; j < p->samples_per_frame; j++ )
                *pb++ = v;
        }
        p->output_overlap = output_overlap_float;
    }

    /* best overlap */
    p->frames_search = ( frames_overlap <= 1 ) ? 0 : p->ms_search * p->sample_rate / 1000.0;
    if( p->frames_search < 1 )
    { /* if no search */
        p->best_overlap_offset = NULL;
    }
    else
    {
        unsigned bytes_pre_corr = ( p->samples_overlap - p->samples_per_frame ) * 4; /* sizeof (int32|float) */
        p->buf_pre_corr = malloc( bytes_pre_corr );
        p->table_window = malloc( bytes_pre_corr );
        if( ! p->buf_pre_corr || ! p->table_window )
            return VLC_ENOMEM;
        float *pw = p->table_window;
        for( i = 1; i<frames_overlap; i++ )
        {
            float v = i * ( frames_overlap - i );
            for( j = 0; j < p->samples_per_frame; j++ )
                *pw++ = v;
        }
        p->best_overlap_offset = best_overlap_offset_float;
    }

    unsigned new_size = ( p->frames_search + frames_stride + frames_overlap ) * p->bytes_per_frame;
    if( p->bytes_queued > new_size )
    {
        if( p->bytes_to_slide > p->bytes_queued )
        {
          p->bytes_to_slide -= p->bytes_queued;
          p->bytes_queued    = 0;
        }
        else
        {
            unsigned new_queued = __MIN( p->bytes_queued - p->bytes_to_slide, new_size );
            memmove( p->buf_queue,
                     p->buf_queue + p->bytes_queued - new_queued,
                     new_queued );
            p->bytes_to_slide = 0;
            p->bytes_queued   = new_queued;
        }
    }
    p->bytes_queue_max = new_size;
    p->buf_queue = malloc( p->bytes_queue_max );
    if( ! p->buf_queue )
        return VLC_ENOMEM;

    p->bytes_stride_scaled  = p->bytes_stride * p->scale;
    p->frames_stride_scaled = p->bytes_stride_scaled / p->bytes_per_frame;

    msg_Dbg( VLC_OBJECT(p_filter),
             "%.3f scale, %.3f stride_in, %i stride_out, %i standing, %i overlap, %i search, %i queue, %s mode",
             p->scale,
             p->frames_stride_scaled,
             (int)( p->bytes_stride / p->bytes_per_frame ),
             (int)( p->bytes_standing / p->bytes_per_frame ),
             (int)( p->bytes_overlap / p->bytes_per_frame ),
             p->frames_search,
             (int)( p->bytes_queue_max / p->bytes_per_frame ),
             "fl32");

    return VLC_SUCCESS;
}