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
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_NOTICE ; 
 scalar_t__ arg_user ; 
 int /*<<< orphan*/  log_full (int /*<<< orphan*/ ,char*,char const*,unsigned int,char*) ; 
 int /*<<< orphan*/  log_notice (char*) ; 

__attribute__((used)) static int log_unresolvable_specifier(const char *filename, unsigned line) {
        static bool notified = false;

        /* In system mode, this is called when /etc is not fully initialized (e.g.
         * in a chroot environment) where some specifiers are unresolvable. In user
         * mode, this is called when some variables are not defined. These cases are
         * not considered as an error so log at LOG_NOTICE only for the first time
         * and then downgrade this to LOG_DEBUG for the rest. */

        log_full(notified ? LOG_DEBUG : LOG_NOTICE,
                 "[%s:%u] Failed to resolve specifier: %s, skipping",
                 filename, line,
                 arg_user ? "Required $XDG_... variable not defined" : "uninitialized /etc detected");

        if (!notified)
                log_notice("All rules containing unresolvable specifiers will be skipped.");

        notified = true;
        return 0;
}