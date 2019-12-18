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
struct TYPE_4__ {int utc; int weekdays_bits; int end_of_month; int /*<<< orphan*/  microsecond; int /*<<< orphan*/  minute; int /*<<< orphan*/  hour; int /*<<< orphan*/  day; int /*<<< orphan*/  month; int /*<<< orphan*/  year; int /*<<< orphan*/  timezone; } ;
typedef  TYPE_1__ CalendarSpec ;

/* Variables and functions */
 int BITS_WEEKDAYS ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  fix_year (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  normalize_chain (int /*<<< orphan*/ *) ; 
 scalar_t__ streq_ptr (int /*<<< orphan*/ ,char*) ; 

int calendar_spec_normalize(CalendarSpec *c) {
        assert(c);

        if (streq_ptr(c->timezone, "UTC")) {
                c->utc = true;
                c->timezone = mfree(c->timezone);
        }

        if (c->weekdays_bits <= 0 || c->weekdays_bits >= BITS_WEEKDAYS)
                c->weekdays_bits = -1;

        if (c->end_of_month && !c->day)
                c->end_of_month = false;

        fix_year(c->year);

        normalize_chain(&c->year);
        normalize_chain(&c->month);
        normalize_chain(&c->day);
        normalize_chain(&c->hour);
        normalize_chain(&c->minute);
        normalize_chain(&c->microsecond);

        return 0;
}