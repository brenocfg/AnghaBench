#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_playlist_item_t ;
struct TYPE_2__ {int /*<<< orphan*/ ** data; } ;
struct randomizer {TYPE_1__ items; } ;

/* Variables and functions */

__attribute__((used)) static inline void
swap_items(struct randomizer *r, int i, int j)
{
    vlc_playlist_item_t *item = r->items.data[i];
    r->items.data[i] = r->items.data[j];
    r->items.data[j] = item;
}