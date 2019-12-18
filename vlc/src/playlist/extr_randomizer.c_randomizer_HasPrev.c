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
struct TYPE_2__ {int size; } ;
struct randomizer {int next; int history; TYPE_1__ items; int /*<<< orphan*/  loop; } ;

/* Variables and functions */

bool
randomizer_HasPrev(struct randomizer *r)
{
    if (!r->loop)
        /* a previous exists if the current is > 0, i.e. next > 1 */
        return r->next > 1;

    if (!r->items.size)
        /* avoid modulo 0 */
        return false;

    /* there is no previous only if (current - history) == 0 (modulo size),
     * i.e. (next - history) == 1 (modulo size) */
    return (r->next + r->items.size - r->history) % r->items.size != 1;
}