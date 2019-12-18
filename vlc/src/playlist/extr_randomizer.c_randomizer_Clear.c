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
struct randomizer {scalar_t__ history; scalar_t__ next; scalar_t__ head; int /*<<< orphan*/  items; } ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_vector_clear (int /*<<< orphan*/ *) ; 

void
randomizer_Clear(struct randomizer *r)
{
    vlc_vector_clear(&r->items);
    r->head = 0;
    r->next = 0;
    r->history = 0;
}