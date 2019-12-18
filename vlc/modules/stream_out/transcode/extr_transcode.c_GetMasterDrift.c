#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_tick_t ;
struct TYPE_5__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ sout_stream_t ;
struct TYPE_6__ {int /*<<< orphan*/  lock; TYPE_1__* id_master_sync; } ;
typedef  TYPE_3__ sout_stream_sys_t ;
struct TYPE_4__ {int /*<<< orphan*/  i_drift; } ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static vlc_tick_t GetMasterDrift( void *cbdata )
{
    sout_stream_t *p_stream = cbdata;
    sout_stream_sys_t *p_sys = p_stream->p_sys;
    vlc_mutex_lock( &p_sys->lock );
    vlc_tick_t drift = 0;
    if( p_sys->id_master_sync )
        drift = p_sys->id_master_sync->i_drift;
    vlc_mutex_unlock( &p_sys->lock );
    return drift;
}