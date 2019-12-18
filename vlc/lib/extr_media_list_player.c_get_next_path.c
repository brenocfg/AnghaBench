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
typedef  int /*<<< orphan*/  libvlc_media_list_t ;
struct TYPE_4__ {int* current_playing_item_path; int /*<<< orphan*/ * p_mlist; } ;
typedef  TYPE_1__ libvlc_media_list_player_t ;
typedef  int* libvlc_media_list_path_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert_locked (TYPE_1__*) ; 
 int /*<<< orphan*/  free (int*) ; 
 int libvlc_media_list_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * libvlc_media_list_parentlist_at_path (int /*<<< orphan*/ *,int*) ; 
 int* libvlc_media_list_path_copy (int*) ; 
 int* libvlc_media_list_path_copy_by_appending (int*,int /*<<< orphan*/ ) ; 
 int libvlc_media_list_path_depth (int*) ; 
 int* libvlc_media_list_path_with_root_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libvlc_media_list_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * libvlc_media_list_sublist_at_path (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static libvlc_media_list_path_t
get_next_path(libvlc_media_list_player_t * p_mlp, bool b_loop)
{
    assert_locked(p_mlp);

    /* We are entered with libvlc_media_list_lock(p_mlp->p_list) */
    libvlc_media_list_path_t ret;
    libvlc_media_list_t * p_parent_of_playing_item;
    libvlc_media_list_t * p_sublist_of_playing_item;

    if (!p_mlp->current_playing_item_path)
    {
        if (!libvlc_media_list_count(p_mlp->p_mlist))
            return NULL;
        return libvlc_media_list_path_with_root_index(0);
    }

    p_sublist_of_playing_item = libvlc_media_list_sublist_at_path(
                            p_mlp->p_mlist,
                            p_mlp->current_playing_item_path);

    /* If item just gained a sublist just play it */
    if (p_sublist_of_playing_item)
    {
        int i_count = libvlc_media_list_count(p_sublist_of_playing_item);
        libvlc_media_list_release(p_sublist_of_playing_item);
        if (i_count > 0)
            return libvlc_media_list_path_copy_by_appending(p_mlp->current_playing_item_path, 0);
    }

    /* Try to catch parent element */
    p_parent_of_playing_item = libvlc_media_list_parentlist_at_path(p_mlp->p_mlist,
                            p_mlp->current_playing_item_path);

    int depth = libvlc_media_list_path_depth(p_mlp->current_playing_item_path);
    if (depth < 1 || !p_parent_of_playing_item)
        return NULL;

    ret = libvlc_media_list_path_copy(p_mlp->current_playing_item_path);
    ret[depth - 1]++; /* set to next element */

    /* If this goes beyond the end of the list */
    while(ret[depth-1] >= libvlc_media_list_count(p_parent_of_playing_item))
    {
        depth--;
        if (depth <= 0)
        {
            if(b_loop)
            {
                ret[0] = 0;
                ret[1] = -1;
                break;
            }
            else
            {
                free(ret);
                libvlc_media_list_release(p_parent_of_playing_item);
                return NULL;
            }
        }
        ret[depth] = -1;
        ret[depth-1]++;
        p_parent_of_playing_item  = libvlc_media_list_parentlist_at_path(
                                        p_mlp->p_mlist,
                                        ret);
    }

    libvlc_media_list_release(p_parent_of_playing_item);
    return ret;
}