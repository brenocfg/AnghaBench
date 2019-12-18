#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  p_data; int /*<<< orphan*/  (* pf_callback ) (int /*<<< orphan*/ ,int) ;TYPE_2__* p_update; } ;
typedef  TYPE_1__ update_check_thread_t ;
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  EmptyRelease (TYPE_2__*) ; 
 int GetUpdateFile (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_restorecancel (int) ; 
 int vlc_savecancel () ; 

void* update_CheckReal( void *obj )
{
    update_check_thread_t *p_uct = (update_check_thread_t *)obj;
    bool b_ret;
    int canc;

    canc = vlc_savecancel ();
    vlc_mutex_lock( &p_uct->p_update->lock );

    EmptyRelease( p_uct->p_update );
    b_ret = GetUpdateFile( p_uct->p_update );
    vlc_mutex_unlock( &p_uct->p_update->lock );

    if( p_uct->pf_callback )
        (p_uct->pf_callback)( p_uct->p_data, b_ret );

    vlc_restorecancel (canc);
    return NULL;
}