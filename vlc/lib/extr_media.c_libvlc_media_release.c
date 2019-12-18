#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ i_refcount; TYPE_6__* p_libvlc_instance; int /*<<< orphan*/  event_manager; int /*<<< orphan*/  subitems_lock; int /*<<< orphan*/  parsed_lock; int /*<<< orphan*/  parsed_cond; int /*<<< orphan*/  p_input_item; scalar_t__ p_subitems; } ;
typedef  TYPE_3__ libvlc_media_t ;
struct TYPE_11__ {TYPE_3__* md; } ;
struct TYPE_12__ {TYPE_1__ media_freed; } ;
struct TYPE_14__ {TYPE_2__ u; int /*<<< orphan*/  type; } ;
typedef  TYPE_4__ libvlc_event_t ;
struct TYPE_15__ {int /*<<< orphan*/  p_libvlc_int; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  input_item_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libvlc_MediaFreed ; 
 int /*<<< orphan*/  libvlc_MetadataCancel (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  libvlc_event_manager_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_event_send (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  libvlc_media_list_release (scalar_t__) ; 
 int /*<<< orphan*/  libvlc_release (TYPE_6__*) ; 
 int /*<<< orphan*/  uninstall_input_item_observer (TYPE_3__*) ; 
 int /*<<< orphan*/  vlc_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 

void libvlc_media_release( libvlc_media_t *p_md )
{
    if (!p_md)
        return;

    p_md->i_refcount--;

    if( p_md->i_refcount > 0 )
        return;

    uninstall_input_item_observer( p_md );

    /* Cancel asynchronous parsing (if any) */
    libvlc_MetadataCancel( p_md->p_libvlc_instance->p_libvlc_int, p_md );

    if( p_md->p_subitems )
        libvlc_media_list_release( p_md->p_subitems );

    input_item_Release( p_md->p_input_item );

    vlc_cond_destroy( &p_md->parsed_cond );
    vlc_mutex_destroy( &p_md->parsed_lock );
    vlc_mutex_destroy( &p_md->subitems_lock );

    /* Construct the event */
    libvlc_event_t event;
    event.type = libvlc_MediaFreed;
    event.u.media_freed.md = p_md;

    /* Send the event */
    libvlc_event_send( &p_md->event_manager, &event );

    libvlc_event_manager_destroy( &p_md->event_manager );
    libvlc_release( p_md->p_libvlc_instance );
    free( p_md );
}