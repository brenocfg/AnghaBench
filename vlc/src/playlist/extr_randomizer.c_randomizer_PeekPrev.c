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
struct TYPE_2__ {int size; int /*<<< orphan*/ ** data; } ;
struct randomizer {int next; TYPE_1__ items; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  randomizer_HasPrev (struct randomizer*) ; 

vlc_playlist_item_t *
randomizer_PeekPrev(struct randomizer *r)
{
    assert(randomizer_HasPrev(r));
    size_t index = (r->next + r->items.size - 2) % r->items.size;
    return r->items.data[index];
}