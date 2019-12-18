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
typedef  int /*<<< orphan*/  sd_id128_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int get_boot_id_for_machine (char const*,int /*<<< orphan*/ *) ; 
 int log_error_errno (int,char*,...) ; 
 int sd_id128_get_boot (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sd_id128_to_string (int /*<<< orphan*/ ,char*) ; 
 int sd_journal_add_conjunction (int /*<<< orphan*/ *) ; 
 int sd_journal_add_match (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

int add_match_this_boot(sd_journal *j, const char *machine) {
        char match[9+32+1] = "_BOOT_ID=";
        sd_id128_t boot_id;
        int r;

        assert(j);

        if (machine) {
                r = get_boot_id_for_machine(machine, &boot_id);
                if (r < 0)
                        return log_error_errno(r, "Failed to get boot id of container %s: %m", machine);
        } else {
                r = sd_id128_get_boot(&boot_id);
                if (r < 0)
                        return log_error_errno(r, "Failed to get boot id: %m");
        }

        sd_id128_to_string(boot_id, match + 9);
        r = sd_journal_add_match(j, match, strlen(match));
        if (r < 0)
                return log_error_errno(r, "Failed to add match: %m");

        r = sd_journal_add_conjunction(j);
        if (r < 0)
                return log_error_errno(r, "Failed to add conjunction: %m");

        return 0;
}