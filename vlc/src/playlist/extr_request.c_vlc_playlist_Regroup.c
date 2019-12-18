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
typedef  int /*<<< orphan*/  vlc_playlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  vlc_playlist_Move (int /*<<< orphan*/ *,size_t,size_t,size_t) ; 

__attribute__((used)) static size_t
vlc_playlist_Regroup(vlc_playlist_t *playlist, size_t indices[],
                     size_t head_index)
{
    size_t head = indices[head_index];
    if (head_index == 0)
        /* nothing to regroup */
        return head;

    size_t slice_size = 1;
    size_t last_index = indices[head_index - 1];

    /* size_t is unsigned, take care not to test for non-negativity */
    for (size_t i = head_index - 1; i != 0; --i)
    {
        size_t index = indices[i - 1];
        if (index == last_index - 1)
            slice_size++;
        else
        {
            assert(last_index != head);
            if (last_index < head)
            {
                assert(head >= slice_size);
                head -= slice_size;

                /* update index of items that will be moved as a side-effect */
                for (size_t j = 0; j <= i; ++j)
                    if (indices[j] >= last_index + slice_size && indices[j] < head)
                        indices[j] -= slice_size;
            }
            else
            {
                /* update index of items that will be moved as a side-effect */
                for (size_t j = 0; j <= i; ++j)
                    if (indices[j] >= head && indices[j] < last_index)
                        indices[j] += slice_size;
            }
            index = indices[i - 1]; /* current index might have been updated */

            /* the slice is complete, move it to build the unique slice */
            vlc_playlist_Move(playlist, last_index, slice_size, head);
            slice_size = 1;
        }

        last_index = index;
    }

    /* move the last slice to build the unique slice */
    if (last_index < head)
    {
        assert(head >= slice_size);
        head -= slice_size;
    }
    vlc_playlist_Move(playlist, last_index, slice_size, head);
    return head;
}