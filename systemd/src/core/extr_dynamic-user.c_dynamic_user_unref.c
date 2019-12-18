#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ n_ref; } ;
typedef  TYPE_1__ DynamicUser ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static DynamicUser* dynamic_user_unref(DynamicUser *d) {
        if (!d)
                return NULL;

        /* Note that this doesn't actually release any resources itself. If a dynamic user should be fully destroyed
         * and its UID released, use dynamic_user_destroy() instead. NB: the dynamic user table may contain entries
         * with no references, which is commonly the case right before a daemon reload. */

        assert(d->n_ref > 0);
        d->n_ref--;

        return NULL;
}