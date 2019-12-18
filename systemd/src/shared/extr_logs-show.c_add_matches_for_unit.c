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
typedef  char const sd_journal ;

/* Variables and functions */
 int /*<<< orphan*/  assert (char const*) ; 
 scalar_t__ endswith (char const*,char*) ; 
 int sd_journal_add_disjunction (char const*) ; 
 int sd_journal_add_match (char const*,char const*,int /*<<< orphan*/ ) ; 
 char* strjoina (char*,char const*) ; 

int add_matches_for_unit(sd_journal *j, const char *unit) {
        const char *m1, *m2, *m3, *m4;
        int r;

        assert(j);
        assert(unit);

        m1 = strjoina("_SYSTEMD_UNIT=", unit);
        m2 = strjoina("COREDUMP_UNIT=", unit);
        m3 = strjoina("UNIT=", unit);
        m4 = strjoina("OBJECT_SYSTEMD_UNIT=", unit);

        (void)(
            /* Look for messages from the service itself */
            (r = sd_journal_add_match(j, m1, 0)) ||

            /* Look for coredumps of the service */
            (r = sd_journal_add_disjunction(j)) ||
            (r = sd_journal_add_match(j, "MESSAGE_ID=fc2e22bc6ee647b6b90729ab34a250b1", 0)) ||
            (r = sd_journal_add_match(j, "_UID=0", 0)) ||
            (r = sd_journal_add_match(j, m2, 0)) ||

             /* Look for messages from PID 1 about this service */
            (r = sd_journal_add_disjunction(j)) ||
            (r = sd_journal_add_match(j, "_PID=1", 0)) ||
            (r = sd_journal_add_match(j, m3, 0)) ||

            /* Look for messages from authorized daemons about this service */
            (r = sd_journal_add_disjunction(j)) ||
            (r = sd_journal_add_match(j, "_UID=0", 0)) ||
            (r = sd_journal_add_match(j, m4, 0))
        );

        if (r == 0 && endswith(unit, ".slice")) {
                const char *m5;

                m5 = strjoina("_SYSTEMD_SLICE=", unit);

                /* Show all messages belonging to a slice */
                (void)(
                        (r = sd_journal_add_disjunction(j)) ||
                        (r = sd_journal_add_match(j, m5, 0))
                        );
        }

        return r;
}