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
struct TYPE_4__ {int /*<<< orphan*/ * p_mlist; int /*<<< orphan*/  current_playing_item_path; } ;
typedef  TYPE_1__ libvlc_media_list_player_t ;
typedef  int* libvlc_media_list_path_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert_locked (TYPE_1__*) ; 
 int* find_last_item (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  free (int*) ; 
 int libvlc_media_list_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * libvlc_media_list_parentlist_at_path (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int* libvlc_media_list_path_copy (int /*<<< orphan*/ ) ; 
 int libvlc_media_list_path_depth (int /*<<< orphan*/ ) ; 
 int* libvlc_media_list_path_with_root_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libvlc_media_list_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static libvlc_media_list_path_t
get_previous_path(libvlc_media_list_player_t * p_mlp, bool b_loop)
{
    assert_locked(p_mlp);

    /* We are entered with libvlc_media_list_lock(p_mlp->p_list) */
    libvlc_media_list_path_t ret;
    libvlc_media_list_t * p_parent_of_playing_item;

    if (!p_mlp->current_playing_item_path)
    {
        if (!libvlc_media_list_count(p_mlp->p_mlist))
            return NULL;
        return libvlc_media_list_path_with_root_index(0);
    }

    /* Try to catch parent element */
    p_parent_of_playing_item = libvlc_media_list_parentlist_at_path(
                                            p_mlp->p_mlist,
                                            p_mlp->current_playing_item_path);

    int depth = libvlc_media_list_path_depth(p_mlp->current_playing_item_path);
    if (depth < 1 || !p_parent_of_playing_item)
        return NULL;

    /* Set the return path to the current path */
    ret = libvlc_media_list_path_copy(p_mlp->current_playing_item_path);

    /* Change the return path to the previous list entry */
    ret[depth - 1]--; /* set to previous element */
    ret[depth] = -1;

    /* Is the return path is beyond the start of the current list? */
    if(ret[depth - 1] < 0)
    {
        /* Move to parent of current item */
        depth--;

        /* Are we at the root level of the tree? */
        if (depth <= 0)
        {
            // Is looping enabled?
            if(b_loop)
            {
                int i_count = libvlc_media_list_count(p_parent_of_playing_item);

                /* Set current play item to the last element in the list */
                ret[0] = i_count - 1;
                ret[1] = -1;

                /* Set the return path to the last descendant item of the current item */
                ret = find_last_item(p_mlp->p_mlist, ret);
            }
            else
            {
                /* No looping so return empty path. */
                free(ret);
                ret = NULL;
            }
        }
        else
        {
            /* This is the case of moving backward from the beginning of the
            *  subitem list to its parent item.
            *  This ensures that current path is properly terminated to
            *  use that parent.
            */
            ret[depth] = -1;
        }
    }
    else
    {
        ret = find_last_item(p_mlp->p_mlist, ret);
    }

    libvlc_media_list_release(p_parent_of_playing_item);
    return ret;
}