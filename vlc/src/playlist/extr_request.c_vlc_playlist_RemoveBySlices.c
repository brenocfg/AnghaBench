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
 int /*<<< orphan*/  vlc_playlist_Remove (int /*<<< orphan*/ *,size_t,size_t) ; 

__attribute__((used)) static void
vlc_playlist_RemoveBySlices(vlc_playlist_t *playlist, size_t sorted_indices[],
                            size_t count)
{
    assert(count > 0);
    size_t last_index = sorted_indices[count - 1];
    size_t slice_size = 1;
    /* size_t is unsigned, take care not to test for non-negativity */
    for (size_t i = count - 1; i != 0; --i)
    {
        size_t index = sorted_indices[i - 1];
        if (index == last_index - 1)
            slice_size++;
        else
        {
            /* the previous slice is complete */
            vlc_playlist_Remove(playlist, last_index, slice_size);
            slice_size = 1;
        }
        last_index = index;
    }
    /* remove the last slice */
    vlc_playlist_Remove(playlist, last_index, slice_size);
}