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
struct TYPE_6__ {int /*<<< orphan*/  timezone; int /*<<< orphan*/  microsecond; int /*<<< orphan*/  minute; int /*<<< orphan*/  hour; int /*<<< orphan*/  day; int /*<<< orphan*/  month; int /*<<< orphan*/  year; } ;
typedef  TYPE_1__ CalendarSpec ;

/* Variables and functions */
 int /*<<< orphan*/  chain_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 TYPE_1__* mfree (TYPE_1__*) ; 

CalendarSpec* calendar_spec_free(CalendarSpec *c) {

        if (!c)
                return NULL;

        chain_free(c->year);
        chain_free(c->month);
        chain_free(c->day);
        chain_free(c->hour);
        chain_free(c->minute);
        chain_free(c->microsecond);
        free(c->timezone);

        return mfree(c);
}