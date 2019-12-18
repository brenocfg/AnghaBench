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
struct TYPE_2__ {scalar_t__ size; int /*<<< orphan*/ ** data; } ;
struct randomizer {scalar_t__ next; scalar_t__ history; scalar_t__ head; TYPE_1__ items; int /*<<< orphan*/  loop; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  randomizer_AutoReshuffle (struct randomizer*) ; 
 int /*<<< orphan*/  randomizer_DetermineOne (struct randomizer*) ; 
 int /*<<< orphan*/  randomizer_HasNext (struct randomizer*) ; 

vlc_playlist_item_t *
randomizer_PeekNext(struct randomizer *r)
{
    assert(randomizer_HasNext(r));

    if (r->next == r->items.size && r->next == r->history)
    {
        assert(r->loop);
        randomizer_AutoReshuffle(r);
    }

    if (r->next == r->head)
        /* execute 1 step of the Fisher-Yates shuffle */
        randomizer_DetermineOne(r);

    return r->items.data[r->next];
}