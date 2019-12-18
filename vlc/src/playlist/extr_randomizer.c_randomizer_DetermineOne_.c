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
struct TYPE_2__ {size_t size; } ;
struct randomizer {size_t head; size_t history; int /*<<< orphan*/  xsubi; TYPE_1__ items; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 size_t nrand48 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swap_items (struct randomizer*,size_t,size_t) ; 

__attribute__((used)) static inline void
randomizer_DetermineOne_(struct randomizer *r, size_t avoid_last_n)
{
    assert(r->head < r->items.size);
    assert(r->items.size - r->head > avoid_last_n);
    size_t range_len = r->items.size - r->head - avoid_last_n;
    size_t selected = r->head + (nrand48(r->xsubi) % range_len);
    swap_items(r, r->head, selected);

    if (r->head == r->history)
        r->history++;
    r->head++;
}