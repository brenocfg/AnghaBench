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
 int /*<<< orphan*/  libvlc_printerr (char*) ; 
 int vlc_array_index_of_item (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int libvlc_media_list_index_of_item( libvlc_media_list_t * p_mlist,
                                     libvlc_media_t * p_searched_md )
{
    int idx = vlc_array_index_of_item( &p_mlist->items, p_searched_md );
    if( idx == -1 )
        libvlc_printerr( "Media not found" );

    return idx;
}