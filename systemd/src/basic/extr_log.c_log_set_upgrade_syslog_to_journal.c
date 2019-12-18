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
 scalar_t__ LOG_TARGET_JOURNAL ; 
 scalar_t__ LOG_TARGET_JOURNAL_OR_KMSG ; 
 scalar_t__ LOG_TARGET_SYSLOG ; 
 scalar_t__ LOG_TARGET_SYSLOG_OR_KMSG ; 
 scalar_t__ log_target ; 
 int upgrade_syslog_to_journal ; 

void log_set_upgrade_syslog_to_journal(bool b) {
        upgrade_syslog_to_journal = b;

        /* Make the change effective immediately */
        if (b) {
                if (log_target == LOG_TARGET_SYSLOG)
                        log_target = LOG_TARGET_JOURNAL;
                else if (log_target == LOG_TARGET_SYSLOG_OR_KMSG)
                        log_target = LOG_TARGET_JOURNAL_OR_KMSG;
        }
}