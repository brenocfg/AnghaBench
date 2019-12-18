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
struct randomizer {size_t history; size_t head; int next; TYPE_1__ items; } ;
typedef  int /*<<< orphan*/  selected ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ **,int /*<<< orphan*/ **,size_t) ; 

__attribute__((used)) static void
randomizer_SelectIndex(struct randomizer *r, size_t index)
{
    vlc_playlist_item_t *selected = r->items.data[index];
    if (r->history && index >= r->history)
    {
        if (index > r->history)
        {
            memmove(&r->items.data[r->history + 1],
                    &r->items.data[r->history],
                    (index - r->history) * sizeof(selected));
            index = r->history;
        }
        r->history = (r->history + 1) % r->items.size;
    }

    if (index >= r->head)
    {
        r->items.data[index] = r->items.data[r->head];
        r->items.data[r->head] = selected;
        r->head++;
    }
    else if (index < r->items.size - 1)
    {
        memmove(&r->items.data[index],
                &r->items.data[index + 1],
                (r->head - index - 1) * sizeof(selected));
        r->items.data[r->head - 1] = selected;
    }

    r->next = r->head;
}