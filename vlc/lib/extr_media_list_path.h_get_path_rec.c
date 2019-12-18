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
typedef  int /*<<< orphan*/ * libvlc_media_list_path_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int libvlc_media_list_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * libvlc_media_list_item_at_index (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  libvlc_media_list_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * libvlc_media_list_path_copy_by_appending (int /*<<< orphan*/ * const,int) ; 
 int /*<<< orphan*/  libvlc_media_list_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_media_list_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_media_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * libvlc_media_subitems (int /*<<< orphan*/ *) ; 

__attribute__((used)) static libvlc_media_list_path_t
get_path_rec( const libvlc_media_list_path_t path, libvlc_media_list_t * p_current_mlist, libvlc_media_t * p_searched_md )
{
    int count = libvlc_media_list_count( p_current_mlist );

    for( int i = 0; i < count; i++ )
    {
        libvlc_media_t * p_md = libvlc_media_list_item_at_index( p_current_mlist, i );

        if( p_md == p_searched_md )
            return libvlc_media_list_path_copy_by_appending( path, i ); /* Found! */

        libvlc_media_list_t * p_subitems = libvlc_media_subitems( p_md );
        libvlc_media_release( p_md );
        if( p_subitems )
        {
            libvlc_media_list_path_t new_path = libvlc_media_list_path_copy_by_appending( path, i );
            libvlc_media_list_lock( p_subitems );
            libvlc_media_list_path_t ret = get_path_rec( new_path, p_subitems, p_searched_md );
            libvlc_media_list_unlock( p_subitems );
            free( new_path );
            libvlc_media_list_release( p_subitems );
            if( ret )
                return ret; /* Found in sublist! */
        }
    }
    return NULL;
}