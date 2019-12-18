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
typedef  int /*<<< orphan*/  OrderedSet ;

/* Variables and functions */
 int /*<<< orphan*/  free (void*) ; 
 int ordered_set_put (int /*<<< orphan*/ *,void*) ; 

int ordered_set_consume(OrderedSet *s, void *p) {
        int r;

        r = ordered_set_put(s, p);
        if (r <= 0)
                free(p);

        return r;
}