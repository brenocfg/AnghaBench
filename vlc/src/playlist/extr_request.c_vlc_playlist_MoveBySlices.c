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
 size_t vlc_playlist_Regroup (int /*<<< orphan*/ *,size_t*,size_t) ; 

__attribute__((used)) static void
vlc_playlist_MoveBySlices(vlc_playlist_t *playlist, size_t indices[],
                          size_t count, size_t target)
{
    assert(count > 0);

    /* pass the last slice */
    size_t i;
    for (i = count - 1; i != 0; --i)
        if (indices[i - 1] != indices[i] - 1)
            break;

    /* regroup items to form a unique slice */
    size_t head = vlc_playlist_Regroup(playlist, indices, i);

    /* move the unique slice to the requested target */
    if (head != target)
        vlc_playlist_Move(playlist, head, count, target);
}