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
 int EINVAL ; 
 int /*<<< orphan*/  FS_NOCOW_FL ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int REMOVE_PHYSICAL ; 
 int REMOVE_ROOT ; 
 int /*<<< orphan*/  SD_JOURNAL_LOCAL_ONLY ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  chattr_path (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_info (char*,...) ; 
 int mkdtemp (char*) ; 
 scalar_t__ rm_rf (char*,int) ; 
 int safe_atoi (char*,int*) ; 
 int /*<<< orphan*/  sd_journal_close (int /*<<< orphan*/ *) ; 
 int sd_journal_open (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int sd_journal_open_directory (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_setup_logging (int /*<<< orphan*/ ) ; 

int main(int argc, char *argv[]) {
        sd_journal *j;
        int r, i, I = 100;
        char t[] = "/var/tmp/journal-stream-XXXXXX";

        test_setup_logging(LOG_DEBUG);

        if (argc >= 2) {
                r = safe_atoi(argv[1], &I);
                if (r < 0)
                        log_info("Could not parse loop count argument. Using default.");
        }

        log_info("Running %d loops", I);

        assert_se(mkdtemp(t));
        (void) chattr_path(t, FS_NOCOW_FL, FS_NOCOW_FL, NULL);

        for (i = 0; i < I; i++) {
                r = sd_journal_open(&j, SD_JOURNAL_LOCAL_ONLY);
                assert_se(r == 0);

                sd_journal_close(j);

                r = sd_journal_open_directory(&j, t, 0);
                assert_se(r == 0);

                sd_journal_close(j);

                j = NULL;
                r = sd_journal_open_directory(&j, t, SD_JOURNAL_LOCAL_ONLY);
                assert_se(r == -EINVAL);
                assert_se(j == NULL);
        }

        assert_se(rm_rf(t, REMOVE_ROOT|REMOVE_PHYSICAL) >= 0);

        return 0;
}