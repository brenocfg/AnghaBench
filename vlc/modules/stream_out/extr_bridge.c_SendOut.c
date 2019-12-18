#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ p_sys; } ;
typedef  TYPE_1__ sout_stream_t ;
struct TYPE_9__ {TYPE_3__* p_es; } ;
typedef  TYPE_2__ out_sout_stream_sys_t ;
struct TYPE_10__ {TYPE_4__** pp_last; } ;
typedef  TYPE_3__ bridged_es_t ;
struct TYPE_11__ {struct TYPE_11__* p_next; } ;
typedef  TYPE_4__ block_t ;

/* Variables and functions */
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  block_ChainRelease (TYPE_4__*) ; 
 int /*<<< orphan*/  lock ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int SendOut( sout_stream_t *p_stream, void *id, block_t *p_buffer )
{
    out_sout_stream_sys_t *p_sys = (out_sout_stream_sys_t *)p_stream->p_sys;
    bridged_es_t *p_es;

    if ( (out_sout_stream_sys_t *)id != p_sys )
    {
        block_ChainRelease( p_buffer );
        return VLC_SUCCESS;
    }

    vlc_mutex_lock( &lock );

    p_es = p_sys->p_es;
    *p_es->pp_last = p_buffer;
    while ( p_buffer != NULL )
    {
        p_es->pp_last = &p_buffer->p_next;
        p_buffer = p_buffer->p_next;
    }

    vlc_mutex_unlock( &lock );

    return VLC_SUCCESS;
}