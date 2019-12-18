#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  libvlc_media_t ;
struct TYPE_4__ {scalar_t__ i_refcount; int /*<<< orphan*/  p_libvlc_instance; int /*<<< orphan*/  items; int /*<<< orphan*/  refcount_lock; int /*<<< orphan*/  object_lock; int /*<<< orphan*/ * p_md; int /*<<< orphan*/  event_manager; } ;
typedef  TYPE_1__ libvlc_media_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  libvlc_event_manager_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_media_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_array_clear (int /*<<< orphan*/ *) ; 
 size_t vlc_array_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_array_item_at_index (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

void libvlc_media_list_release( libvlc_media_list_t * p_mlist )
{
    vlc_mutex_lock( &p_mlist->refcount_lock );
    p_mlist->i_refcount--;
    if( p_mlist->i_refcount > 0 )
    {
        vlc_mutex_unlock( &p_mlist->refcount_lock );
        return;
    }
    vlc_mutex_unlock( &p_mlist->refcount_lock );

    /* Refcount null, time to free */

    libvlc_event_manager_destroy( &p_mlist->event_manager );
    libvlc_media_release( p_mlist->p_md );

    for( size_t i = 0; i < vlc_array_count( &p_mlist->items ); i++ )
    {
        libvlc_media_t* p_md = vlc_array_item_at_index( &p_mlist->items, i );
        libvlc_media_release( p_md );
    }

    vlc_mutex_destroy( &p_mlist->object_lock );
    vlc_mutex_destroy( &p_mlist->refcount_lock );
    vlc_array_clear( &p_mlist->items );

    libvlc_release( p_mlist->p_libvlc_instance );
    free( p_mlist );
}