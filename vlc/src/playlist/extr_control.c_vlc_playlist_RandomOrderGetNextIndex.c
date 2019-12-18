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
struct TYPE_4__ {int /*<<< orphan*/  randomizer; } ;
typedef  TYPE_1__ vlc_playlist_t ;
typedef  int /*<<< orphan*/  vlc_playlist_item_t ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * randomizer_PeekNext (int /*<<< orphan*/ *) ; 
 int vlc_playlist_IndexOf (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline size_t
vlc_playlist_RandomOrderGetNextIndex(vlc_playlist_t *playlist)
{
    vlc_playlist_item_t *next = randomizer_PeekNext(&playlist->randomizer);
    assert(next);
    ssize_t index = vlc_playlist_IndexOf(playlist, next);
    assert(index != -1);
    return (size_t) index;
}