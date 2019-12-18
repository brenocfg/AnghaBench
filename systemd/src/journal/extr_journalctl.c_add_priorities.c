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
typedef  int /*<<< orphan*/  sd_journal ;
typedef  int /*<<< orphan*/  match ;

/* Variables and functions */
 int LOG_DEBUG ; 
 int LOG_EMERG ; 
 int arg_priorities ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int log_error_errno (int,char*) ; 
 int sd_journal_add_conjunction (int /*<<< orphan*/ *) ; 
 int sd_journal_add_match (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static int add_priorities(sd_journal *j) {
        char match[] = "PRIORITY=0";
        int i, r;
        assert(j);

        if (arg_priorities == 0xFF)
                return 0;

        for (i = LOG_EMERG; i <= LOG_DEBUG; i++)
                if (arg_priorities & (1 << i)) {
                        match[sizeof(match)-2] = '0' + i;

                        r = sd_journal_add_match(j, match, strlen(match));
                        if (r < 0)
                                return log_error_errno(r, "Failed to add match: %m");
                }

        r = sd_journal_add_conjunction(j);
        if (r < 0)
                return log_error_errno(r, "Failed to add conjunction: %m");

        return 0;
}