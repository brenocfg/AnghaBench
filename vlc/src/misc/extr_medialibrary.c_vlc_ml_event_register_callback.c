#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vlc_ml_event_callback_t {int /*<<< orphan*/  node; void* p_data; int /*<<< orphan*/  pf_cb; } ;
typedef  struct vlc_ml_event_callback_t vlc_ml_event_callback_t ;
typedef  int /*<<< orphan*/  vlc_ml_callback_t ;
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  cbs; } ;
typedef  TYPE_1__ vlc_medialibrary_t ;

/* Variables and functions */
 struct vlc_ml_event_callback_t* malloc (int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_list_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

vlc_ml_event_callback_t*
vlc_ml_event_register_callback( vlc_medialibrary_t* p_ml, vlc_ml_callback_t cb,
                                void* p_data )
{
    struct vlc_ml_event_callback_t* p_cb = malloc( sizeof( *p_cb ) );
    if ( unlikely( p_cb == NULL ) )
        return NULL;
    p_cb->pf_cb = cb;
    p_cb->p_data = p_data;
    vlc_mutex_lock( &p_ml->lock );
    vlc_list_append( &p_cb->node, &p_ml->cbs );
    vlc_mutex_unlock( &p_ml->lock );
    return p_cb;
}