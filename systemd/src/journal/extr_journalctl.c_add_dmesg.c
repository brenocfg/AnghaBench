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

/* Variables and functions */
 int /*<<< orphan*/  STRLEN (char*) ; 
 int /*<<< orphan*/  arg_dmesg ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int log_error_errno (int,char*) ; 
 int sd_journal_add_conjunction (int /*<<< orphan*/ *) ; 
 int sd_journal_add_match (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int add_dmesg(sd_journal *j) {
        int r;
        assert(j);

        if (!arg_dmesg)
                return 0;

        r = sd_journal_add_match(j, "_TRANSPORT=kernel",
                                 STRLEN("_TRANSPORT=kernel"));
        if (r < 0)
                return log_error_errno(r, "Failed to add match: %m");

        r = sd_journal_add_conjunction(j);
        if (r < 0)
                return log_error_errno(r, "Failed to add conjunction: %m");

        return 0;
}