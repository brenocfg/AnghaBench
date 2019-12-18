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
typedef  int* libvlc_media_list_path_t ;

/* Variables and functions */
 int /*<<< orphan*/ * libvlc_media_list_item_at_index (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  libvlc_media_list_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_media_list_retain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_media_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * libvlc_media_subitems (int /*<<< orphan*/ *) ; 

__attribute__((used)) static libvlc_media_list_t *
libvlc_media_list_parentlist_at_path( libvlc_media_list_t * p_mlist, const libvlc_media_list_path_t path )
{
    libvlc_media_list_t * p_current_mlist = p_mlist;

    for( int i = 0; path[i] != -1; i++ )
    {
        if( p_current_mlist != p_mlist )
            libvlc_media_list_release( p_current_mlist );

        if( path[i+1] == -1 )
        {
            libvlc_media_list_retain(p_current_mlist);
            return p_current_mlist;
        }

        libvlc_media_t* p_md = libvlc_media_list_item_at_index( p_current_mlist, path[i] );

        p_current_mlist = libvlc_media_subitems( p_md );
        libvlc_media_release( p_md );

        if( !p_current_mlist )
            return NULL;

        /* Fetch next one */
    }
    /* Not found, shouldn't happen if the p_path is not empty */
    if( p_current_mlist != p_mlist )
        libvlc_media_list_release( p_current_mlist );
    return NULL;
}