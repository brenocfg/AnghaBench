#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  event_manager; int /*<<< orphan*/  p_libvlc_instance; } ;
typedef  TYPE_3__ libvlc_media_t ;
typedef  int /*<<< orphan*/  libvlc_media_list_t ;
struct TYPE_11__ {TYPE_3__* new_child; } ;
struct TYPE_12__ {TYPE_1__ media_subitem_added; } ;
struct TYPE_14__ {TYPE_2__ u; int /*<<< orphan*/  type; } ;
typedef  TYPE_4__ libvlc_event_t ;
typedef  int /*<<< orphan*/  input_item_t ;

/* Variables and functions */
 int /*<<< orphan*/  libvlc_MediaSubItemAdded ; 
 int /*<<< orphan*/  libvlc_event_send (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  libvlc_media_list_internal_add_media (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  libvlc_media_list_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_media_list_unlock (int /*<<< orphan*/ *) ; 
 TYPE_3__* libvlc_media_new_from_input_item (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * media_get_subitems (TYPE_3__*,int) ; 

__attribute__((used)) static libvlc_media_t *input_item_add_subitem( libvlc_media_t *p_md,
                                               input_item_t *item )
{
    libvlc_media_t * p_md_child;
    libvlc_media_list_t *p_subitems;
    libvlc_event_t event;

    p_md_child = libvlc_media_new_from_input_item( p_md->p_libvlc_instance,
                                                   item );

    /* Add this to our media list */
    p_subitems = media_get_subitems( p_md, true );
    if( p_subitems != NULL )
    {
        libvlc_media_list_lock( p_subitems );
        libvlc_media_list_internal_add_media( p_subitems, p_md_child );
        libvlc_media_list_unlock( p_subitems );
    }

    /* Construct the event */
    event.type = libvlc_MediaSubItemAdded;
    event.u.media_subitem_added.new_child = p_md_child;

    /* Send the event */
    libvlc_event_send( &p_md->event_manager, &event );
    return p_md_child;
}