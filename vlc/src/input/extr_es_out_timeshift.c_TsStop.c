#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  lock; TYPE_2__* p_storage_r; int /*<<< orphan*/  thread; } ;
typedef  TYPE_1__ ts_thread_t ;
typedef  int /*<<< orphan*/  ts_cmd_t ;
struct TYPE_7__ {int /*<<< orphan*/  p_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  CmdClean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TsDestroy (TYPE_1__*) ; 
 scalar_t__ TsPopCmdLocked (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TsStorageDelete (TYPE_2__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  vlc_cancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void TsStop( ts_thread_t *p_ts )
{
    vlc_cancel( p_ts->thread );
    vlc_join( p_ts->thread, NULL );

    vlc_mutex_lock( &p_ts->lock );
    for( ;; )
    {
        ts_cmd_t cmd;

        if( TsPopCmdLocked( p_ts, &cmd, true ) )
            break;

        CmdClean( &cmd );
    }
    assert( !p_ts->p_storage_r || !p_ts->p_storage_r->p_next );
    if( p_ts->p_storage_r )
        TsStorageDelete( p_ts->p_storage_r );
    vlc_mutex_unlock( &p_ts->lock );

    TsDestroy( p_ts );
}