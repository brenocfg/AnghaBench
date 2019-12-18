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
struct randomizer {scalar_t__ history; scalar_t__ next; int /*<<< orphan*/  items; } ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_vector_insert_all (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ **,size_t) ; 

bool
randomizer_Add(struct randomizer *r, vlc_playlist_item_t *items[], size_t count)
{
    if (!vlc_vector_insert_all(&r->items, r->history, items, count))
        return false;
    /* the insertion shifted history (and possibly next) */
    if (r->next > r->history)
        r->next += count;
    r->history += count;
    return true;
}