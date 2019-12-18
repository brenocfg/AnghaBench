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
struct TYPE_4__ {int /*<<< orphan*/  items; } ;
typedef  TYPE_1__ libvlc_media_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  EventDidHappen ; 
 int /*<<< orphan*/  EventWillHappen ; 
 int /*<<< orphan*/  libvlc_media_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_printerr (char*) ; 
 int /*<<< orphan*/  notify_item_deletion (TYPE_1__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 size_t vlc_array_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_array_item_at_index (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vlc_array_remove (int /*<<< orphan*/ *,int) ; 

int libvlc_media_list_internal_remove_index( libvlc_media_list_t * p_mlist,
                                             int index )
{
    libvlc_media_t * p_md;

    if( (size_t) index >= vlc_array_count( &p_mlist->items ))
    {
        libvlc_printerr( "Index out of bounds" );
        return -1;
    }

    p_md = vlc_array_item_at_index( &p_mlist->items, index );

    notify_item_deletion( p_mlist, p_md, index, EventWillHappen );
    vlc_array_remove( &p_mlist->items, index );
    notify_item_deletion( p_mlist, p_md, index, EventDidHappen );

    libvlc_media_release( p_md );
    return 0;
}