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
typedef  int /*<<< orphan*/  usec_t ;
struct TYPE_4__ {int /*<<< orphan*/  watchdog_original_usec; int /*<<< orphan*/  watchdog_override_usec; scalar_t__ watchdog_override_enable; } ;
typedef  TYPE_1__ Service ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

__attribute__((used)) static usec_t service_get_watchdog_usec(Service *s) {
        assert(s);

        if (s->watchdog_override_enable)
                return s->watchdog_override_usec;

        return s->watchdog_original_usec;
}