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
typedef  int /*<<< orphan*/  libvlc_media_t ;
struct TYPE_3__ {int /*<<< orphan*/  items; } ;
typedef  TYPE_1__ libvlc_media_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  libvlc_media_retain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_printerr (char*) ; 
 size_t vlc_array_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_array_item_at_index (int /*<<< orphan*/ *,int) ; 

libvlc_media_t *
libvlc_media_list_item_at_index( libvlc_media_list_t * p_mlist,
                                 int index )
{
    libvlc_media_t * p_md;

    if( (size_t) index >= vlc_array_count( &p_mlist->items ))
    {
        libvlc_printerr( "Index out of bounds" );
        return NULL;
    }

    p_md = vlc_array_item_at_index( &p_mlist->items, index );
    libvlc_media_retain( p_md );
    return p_md;
}