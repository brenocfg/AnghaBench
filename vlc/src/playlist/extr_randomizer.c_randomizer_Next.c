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
struct TYPE_2__ {scalar_t__ size; } ;
struct randomizer {scalar_t__ next; scalar_t__ head; TYPE_1__ items; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  randomizer_HasNext (struct randomizer*) ; 
 int /*<<< orphan*/ * randomizer_PeekNext (struct randomizer*) ; 

vlc_playlist_item_t *
randomizer_Next(struct randomizer *r)
{
    assert(randomizer_HasNext(r));
    vlc_playlist_item_t *item = randomizer_PeekNext(r);
    r->next++;
    if (r->next == r->items.size && r->next != r->head)
        r->next = 0;
    return item;
}