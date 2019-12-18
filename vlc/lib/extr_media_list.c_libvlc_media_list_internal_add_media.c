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
 int /*<<< orphan*/  libvlc_media_retain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  notify_item_addition (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_array_append_or_abort (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ vlc_array_count (int /*<<< orphan*/ *) ; 

void libvlc_media_list_internal_add_media( libvlc_media_list_t * p_mlist,
                                           libvlc_media_t * p_md )
{
    libvlc_media_retain( p_md );

    notify_item_addition( p_mlist, p_md, vlc_array_count( &p_mlist->items ),
                          EventWillHappen );
    vlc_array_append_or_abort( &p_mlist->items, p_md );
    notify_item_addition( p_mlist, p_md, vlc_array_count( &p_mlist->items )-1,
                          EventDidHappen );
}