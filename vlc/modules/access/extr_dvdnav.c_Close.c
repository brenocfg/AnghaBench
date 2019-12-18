#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_7__ {scalar_t__ es; int /*<<< orphan*/  fmt; scalar_t__ b_configured; } ;
typedef  TYPE_2__ ps_track_t ;
struct TYPE_8__ {int /*<<< orphan*/  out; TYPE_4__* p_sys; } ;
typedef  TYPE_3__ demux_t ;
struct TYPE_6__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  timer; scalar_t__ b_created; } ;
struct TYPE_9__ {int i_title; int /*<<< orphan*/  dvdnav; int /*<<< orphan*/ * title; TYPE_2__* tk; int /*<<< orphan*/  event_lock; TYPE_1__ still; } ;
typedef  TYPE_4__ demux_sys_t ;

/* Variables and functions */
 int PS_TK_COUNT ; 
 int /*<<< orphan*/  TAB_CLEAN (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvdnav_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  es_format_Clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  es_out_Del (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 int /*<<< orphan*/  vlc_input_title_Delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_timer_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Close( vlc_object_t *p_this )
{
    demux_t     *p_demux = (demux_t*)p_this;
    demux_sys_t *p_sys = p_demux->p_sys;

    /* Stop still image handler */
    if( p_sys->still.b_created )
        vlc_timer_destroy( p_sys->still.timer );
    vlc_mutex_destroy( &p_sys->still.lock );
    vlc_mutex_destroy( &p_sys->event_lock );

    for( int i = 0; i < PS_TK_COUNT; i++ )
    {
        ps_track_t *tk = &p_sys->tk[i];
        if( tk->b_configured )
        {
            es_format_Clean( &tk->fmt );
            if( tk->es ) es_out_Del( p_demux->out, tk->es );
        }
    }

    /* Free the array of titles */
    for( int i = 0; i < p_sys->i_title; i++ )
        vlc_input_title_Delete( p_sys->title[i] );
    TAB_CLEAN( p_sys->i_title, p_sys->title );

    dvdnav_close( p_sys->dvdnav );
    free( p_sys );
}