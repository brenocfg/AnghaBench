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
typedef  int /*<<< orphan*/  libvlc_media_t ;
typedef  int /*<<< orphan*/  libvlc_media_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  libvlc_media_list_internal_insert_media (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mlist_is_writable (int /*<<< orphan*/ *) ; 

int libvlc_media_list_insert_media( libvlc_media_list_t * p_mlist,
                                    libvlc_media_t * p_md,
                                    int index )
{
    if( !mlist_is_writable(p_mlist) )
        return -1;
    libvlc_media_list_internal_insert_media( p_mlist, p_md, index );
    return 0;
}