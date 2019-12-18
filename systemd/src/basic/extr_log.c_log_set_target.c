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
typedef  scalar_t__ LogTarget ;

/* Variables and functions */
 scalar_t__ LOG_TARGET_JOURNAL ; 
 scalar_t__ LOG_TARGET_JOURNAL_OR_KMSG ; 
 scalar_t__ LOG_TARGET_SYSLOG ; 
 scalar_t__ LOG_TARGET_SYSLOG_OR_KMSG ; 
 scalar_t__ _LOG_TARGET_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ log_target ; 
 scalar_t__ upgrade_syslog_to_journal ; 

void log_set_target(LogTarget target) {
        assert(target >= 0);
        assert(target < _LOG_TARGET_MAX);

        if (upgrade_syslog_to_journal) {
                if (target == LOG_TARGET_SYSLOG)
                        target = LOG_TARGET_JOURNAL;
                else if (target == LOG_TARGET_SYSLOG_OR_KMSG)
                        target = LOG_TARGET_JOURNAL_OR_KMSG;
        }

        log_target = target;
}