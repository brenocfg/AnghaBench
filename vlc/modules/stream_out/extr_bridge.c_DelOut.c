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
struct TYPE_5__ {scalar_t__ p_sys; } ;
typedef  TYPE_1__ sout_stream_t ;
struct TYPE_6__ {int b_inited; TYPE_3__* p_es; } ;
typedef  TYPE_2__ out_sout_stream_sys_t ;
struct TYPE_7__ {int b_empty; int b_changed; int /*<<< orphan*/ * p_block; } ;
typedef  TYPE_3__ bridged_es_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_UNUSED (void*) ; 
 int /*<<< orphan*/  block_ChainRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void DelOut( sout_stream_t *p_stream, void *id )
{
    VLC_UNUSED(id);
    out_sout_stream_sys_t *p_sys = (out_sout_stream_sys_t *)p_stream->p_sys;
    bridged_es_t *p_es;

    if ( !p_sys->b_inited )
        return;

    vlc_mutex_lock( &lock );

    p_es = p_sys->p_es;

    p_es->b_empty = true;
    block_ChainRelease( p_es->p_block );
    p_es->p_block = NULL;

    p_es->b_changed = true;
    vlc_mutex_unlock( &lock );

    p_sys->b_inited = false;
}