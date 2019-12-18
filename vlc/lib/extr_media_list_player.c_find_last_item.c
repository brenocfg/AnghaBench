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
typedef  int /*<<< orphan*/  libvlc_media_list_path_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int libvlc_media_list_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_media_list_path_copy_by_appending (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  libvlc_media_list_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * libvlc_media_list_sublist_at_path (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static libvlc_media_list_path_t
find_last_item( libvlc_media_list_t * p_mlist, libvlc_media_list_path_t current_item )
{
    libvlc_media_list_t * p_sublist = libvlc_media_list_sublist_at_path(p_mlist, current_item);
    libvlc_media_list_path_t last_item_path = current_item;

    if(p_sublist)
    {
        int i_count = libvlc_media_list_count(p_sublist);
        if(i_count > 0)
        {
            /* Add the last sublist item to the path. */
            last_item_path = libvlc_media_list_path_copy_by_appending(current_item, i_count - 1);
            free(current_item);
            /* Check that sublist item for more descendants. */
            last_item_path = find_last_item(p_mlist, last_item_path);
        }

        libvlc_media_list_release(p_sublist);
    }

    return last_item_path;
}