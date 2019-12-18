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
typedef  int /*<<< orphan*/  vlc_playlist_item_t ;
struct randomizer {int /*<<< orphan*/  items; } ;

/* Variables and functions */
 int /*<<< orphan*/  randomizer_RemoveOne (struct randomizer*,int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  vlc_vector_autoshrink (int /*<<< orphan*/ *) ; 

void
randomizer_Remove(struct randomizer *r, vlc_playlist_item_t *const items[],
                  size_t count)
{
    for (size_t i = 0; i < count; ++i)
        randomizer_RemoveOne(r, items[i]);

    vlc_vector_autoshrink(&r->items);
}