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

/* Variables and functions */
 int /*<<< orphan*/  USEC_PER_SEC ; 
 scalar_t__ calendar_spec_from_string (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_notice (char*,char const*) ; 
 scalar_t__ parse_time (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ parse_timestamp (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void parsing_hint(const char *p, bool calendar, bool timestamp, bool timespan) {
        if (calendar && calendar_spec_from_string(p, NULL) >= 0)
                log_notice("Hint: this expression is a valid calendar specification. "
                           "Use 'systemd-analyze calendar \"%s\"' instead?", p);
        if (timestamp && parse_timestamp(p, NULL) >= 0)
                log_notice("Hint: this expression is a valid timestamp. "
                           "Use 'systemd-analyze timestamp \"%s\"' instead?", p);
        if (timespan && parse_time(p, NULL, USEC_PER_SEC) >= 0)
                log_notice("Hint: this expression is a valid timespan. "
                           "Use 'systemd-analyze timespan \"%s\"' instead?", p);
}