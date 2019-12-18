#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned int n_autovts; struct TYPE_5__* manager; } ;
typedef  TYPE_1__ Seat ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  log_debug (char*) ; 
 int log_error_errno (int,char*,unsigned int) ; 
 int /*<<< orphan*/  seat_has_vts (TYPE_1__*) ; 
 int vt_allocate (unsigned int) ; 

int seat_preallocate_vts(Seat *s) {
        int r = 0;
        unsigned i;

        assert(s);
        assert(s->manager);

        if (s->manager->n_autovts <= 0)
                return 0;

        if (!seat_has_vts(s))
                return 0;

        log_debug("Preallocating VTs...");

        for (i = 1; i <= s->manager->n_autovts; i++) {
                int q;

                q = vt_allocate(i);
                if (q < 0)
                        r = log_error_errno(q, "Failed to preallocate VT %u: %m", i);
        }

        return r;
}