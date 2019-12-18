#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int start; int stop; struct TYPE_3__* next; } ;
typedef  TYPE_1__ CalendarComponent ;

/* Variables and functions */

__attribute__((used)) static void fix_year(CalendarComponent *c) {
        /* Turns 12 → 2012, 89 → 1989 */

        while (c) {
                if (c->start >= 0 && c->start < 70)
                        c->start += 2000;

                if (c->stop >= 0 && c->stop < 70)
                        c->stop += 2000;

                if (c->start >= 70 && c->start < 100)
                        c->start += 1900;

                if (c->stop >= 70 && c->stop < 100)
                        c->stop += 1900;

                c = c->next;
        }
}