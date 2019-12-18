#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  libvlc_media_list_t ;

/* Variables and functions */
 int libvlc_media_list_internal_remove_index (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mlist_is_writable (int /*<<< orphan*/ *) ; 

int libvlc_media_list_remove_index( libvlc_media_list_t * p_mlist,
                                     int index )
{
    if( !mlist_is_writable(p_mlist) )
        return -1;
    return libvlc_media_list_internal_remove_index( p_mlist, index );
}