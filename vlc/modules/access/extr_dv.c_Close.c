#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_5__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ stream_t ;
struct TYPE_6__ {int /*<<< orphan*/  lock; scalar_t__ p_raw1394; int /*<<< orphan*/ * p_frame; TYPE_3__* p_ev; } ;
typedef  TYPE_2__ access_sys_t ;
struct TYPE_7__ {int /*<<< orphan*/ ** pp_last; int /*<<< orphan*/ * p_frame; int /*<<< orphan*/  lock; int /*<<< orphan*/  thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  AVCClose (TYPE_1__*) ; 
 int /*<<< orphan*/  block_ChainRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  raw1394_destroy_handle (scalar_t__) ; 
 int /*<<< orphan*/  raw1394_iso_shutdown (scalar_t__) ; 
 int /*<<< orphan*/  vlc_cancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Close( vlc_object_t *p_this )
{
    stream_t     *p_access = (stream_t*)p_this;
    access_sys_t *p_sys = p_access->p_sys;

    if( p_sys->p_ev )
    {
        /* stop the event handler */
        vlc_cancel( p_sys->p_ev->thread );

        if( p_sys->p_raw1394 )
            raw1394_iso_shutdown( p_sys->p_raw1394 );

        vlc_join( p_sys->p_ev->thread, NULL );
        vlc_mutex_destroy( &p_sys->p_ev->lock );

        /* Cleanup frame data */
        if( p_sys->p_ev->p_frame )
        {
            block_ChainRelease( p_sys->p_ev->p_frame );
            p_sys->p_ev->p_frame = NULL;
            p_sys->p_ev->pp_last = &p_sys->p_frame;
        }
        free( p_sys->p_ev );
    }

    if( p_sys->p_frame )
        block_ChainRelease( p_sys->p_frame );
    if( p_sys->p_raw1394 )
        raw1394_destroy_handle( p_sys->p_raw1394 );

    AVCClose( p_access );

    vlc_mutex_destroy( &p_sys->lock );
}