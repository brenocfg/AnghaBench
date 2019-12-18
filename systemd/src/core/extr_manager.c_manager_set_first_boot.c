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
struct TYPE_5__ {int first_boot; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  MANAGER_IS_SYSTEM (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  touch (char*) ; 
 int /*<<< orphan*/  unlink (char*) ; 

void manager_set_first_boot(Manager *m, bool b) {
        assert(m);

        if (!MANAGER_IS_SYSTEM(m))
                return;

        if (m->first_boot != (int) b) {
                if (b)
                        (void) touch("/run/systemd/first-boot");
                else
                        (void) unlink("/run/systemd/first-boot");
        }

        m->first_boot = b;
}