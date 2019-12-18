#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_8__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ sout_mux_t ;
struct TYPE_9__ {size_t i_stream_video; int i_streams; TYPE_4__* stream; } ;
typedef  TYPE_3__ sout_mux_sys_t ;
typedef  int /*<<< orphan*/  bo_t ;
struct TYPE_10__ {scalar_t__ i_frames; int i_duration; int i_totalsize; TYPE_1__* p_bih; scalar_t__ f_fps; } ;
typedef  TYPE_4__ avi_stream_t ;
struct TYPE_7__ {int biWidth; int biHeight; } ;

/* Variables and functions */
 int AVIF_HASINDEX ; 
 int AVIF_ISINTERLEAVED ; 
 int AVIF_TRUSTCKTYPE ; 
 int /*<<< orphan*/  AVI_BOX_ENTER (char*) ; 
 int /*<<< orphan*/  AVI_BOX_EXIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bo_add_32le (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_2__*,char*) ; 

__attribute__((used)) static int avi_HeaderAdd_avih( sout_mux_t *p_mux,
                               bo_t *p_bo )
{
    sout_mux_sys_t  *p_sys = p_mux->p_sys;
    avi_stream_t    *p_video = NULL;
    int         i_stream;
    uint32_t    i_microsecperframe;
    int         i_maxbytespersec;
    int         i_totalframes;
    AVI_BOX_ENTER( "avih" );

    if( p_sys->i_stream_video >= 0 )
    {
        p_video = &p_sys->stream[p_sys->i_stream_video];
        if( p_video->i_frames <= 0 )
        {
        //    p_video = NULL;
        }
    }

    if( p_video )
    {
        i_microsecperframe =
            (uint32_t)( (float)1000000 /
                        (float)p_sys->stream[p_sys->i_stream_video].f_fps );
        i_totalframes = p_sys->stream[p_sys->i_stream_video].i_frames;
    }
    else
    {
        msg_Warn( p_mux, "avi file without video track isn't a good idea..." );
        i_microsecperframe = 0;
        i_totalframes = 0;
    }

    for( i_stream = 0,i_maxbytespersec = 0; i_stream < p_sys->i_streams; i_stream++ )
    {
        if( p_sys->stream[i_stream].i_duration > 0 )
        {
            i_maxbytespersec +=
                p_sys->stream[i_stream].i_totalsize /
                p_sys->stream[i_stream].i_duration;
        }
    }

    bo_add_32le( p_bo, i_microsecperframe );
    bo_add_32le( p_bo, i_maxbytespersec );
    bo_add_32le( p_bo, 0 );                   /* padding */
    bo_add_32le( p_bo, AVIF_TRUSTCKTYPE |
                       AVIF_HASINDEX |
                       AVIF_ISINTERLEAVED );  /* flags */
    bo_add_32le( p_bo, i_totalframes );
    bo_add_32le( p_bo, 0 );                   /* initial frame */
    bo_add_32le( p_bo, p_sys->i_streams );    /* streams count */
    bo_add_32le( p_bo, 1024 * 1024 );         /* suggested buffer size */
    if( p_video )
    {
        bo_add_32le( p_bo, p_video->p_bih->biWidth );
        bo_add_32le( p_bo, p_video->p_bih->biHeight );
    }
    else
    {
        bo_add_32le( p_bo, 0 );
        bo_add_32le( p_bo, 0 );
    }
    bo_add_32le( p_bo, 0 );                   /* ???? */
    bo_add_32le( p_bo, 0 );                   /* ???? */
    bo_add_32le( p_bo, 0 );                   /* ???? */
    bo_add_32le( p_bo, 0 );                   /* ???? */

    AVI_BOX_EXIT( 0 );
}