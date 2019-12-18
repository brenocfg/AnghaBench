#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  resume; int /*<<< orphan*/  swap; } ;
typedef  TYPE_1__ HibernateLocation ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 TYPE_1__* mfree (TYPE_1__*) ; 
 int /*<<< orphan*/  swap_entry_free (int /*<<< orphan*/ ) ; 

HibernateLocation* hibernate_location_free(HibernateLocation *hl) {
        if (!hl)
                return NULL;

        swap_entry_free(hl->swap);
        free(hl->resume);

        return mfree(hl);
}