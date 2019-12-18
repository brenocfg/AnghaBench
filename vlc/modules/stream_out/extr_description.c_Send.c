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
struct TYPE_6__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ sout_stream_t ;
struct TYPE_7__ {scalar_t__ i_stream_start; TYPE_1__* data; } ;
typedef  TYPE_3__ sout_stream_sys_t ;
typedef  int /*<<< orphan*/  block_t ;
struct TYPE_5__ {int /*<<< orphan*/  sem; } ;

/* Variables and functions */
 int VLC_SUCCESS ; 
 scalar_t__ VLC_TICK_FROM_MS (int) ; 
 int /*<<< orphan*/  VLC_UNUSED (void*) ; 
 int /*<<< orphan*/  block_ChainRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_sem_post (int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_tick_now () ; 

__attribute__((used)) static int Send( sout_stream_t *p_stream, void *id, block_t *p_buffer )
{
    VLC_UNUSED(id);
    sout_stream_sys_t *p_sys = p_stream->p_sys;

    block_ChainRelease( p_buffer );

    if( p_sys->i_stream_start + VLC_TICK_FROM_MS(1500) < vlc_tick_now() )
        vlc_sem_post(p_sys->data->sem);

    return VLC_SUCCESS;
}