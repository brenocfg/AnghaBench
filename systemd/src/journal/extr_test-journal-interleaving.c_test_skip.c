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
 int REMOVE_PHYSICAL ; 
 int REMOVE_ROOT ; 
 scalar_t__ arg_keep ; 
 int /*<<< orphan*/  assert_ret (int) ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  journal_directory_vacuum (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  log_info (char*,...) ; 
 int /*<<< orphan*/  mkdtemp_chdir_chattr (char*) ; 
 int /*<<< orphan*/  puts (char*) ; 
 scalar_t__ rm_rf (char*,int) ; 
 int /*<<< orphan*/  sd_journal_close (int /*<<< orphan*/ *) ; 
 int sd_journal_next (int /*<<< orphan*/ *) ; 
 int sd_journal_next_skip (int /*<<< orphan*/ *,int) ; 
 int sd_journal_open_directory (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ) ; 
 int sd_journal_previous (int /*<<< orphan*/ *) ; 
 int sd_journal_previous_skip (int /*<<< orphan*/ *,int) ; 
 int sd_journal_seek_head (int /*<<< orphan*/ *) ; 
 int sd_journal_seek_tail (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_check_numbers_down (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  test_check_numbers_up (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void test_skip(void (*setup)(void)) {
        char t[] = "/var/tmp/journal-skip-XXXXXX";
        sd_journal *j;
        int r;

        mkdtemp_chdir_chattr(t);

        setup();

        /* Seek to head, iterate down.
         */
        assert_ret(sd_journal_open_directory(&j, t, 0));
        assert_ret(sd_journal_seek_head(j));
        assert_ret(sd_journal_next(j));
        test_check_numbers_down(j, 4);
        sd_journal_close(j);

        /* Seek to tail, iterate up.
         */
        assert_ret(sd_journal_open_directory(&j, t, 0));
        assert_ret(sd_journal_seek_tail(j));
        assert_ret(sd_journal_previous(j));
        test_check_numbers_up(j, 4);
        sd_journal_close(j);

        /* Seek to tail, skip to head, iterate down.
         */
        assert_ret(sd_journal_open_directory(&j, t, 0));
        assert_ret(sd_journal_seek_tail(j));
        assert_ret(r = sd_journal_previous_skip(j, 4));
        assert_se(r == 4);
        test_check_numbers_down(j, 4);
        sd_journal_close(j);

        /* Seek to head, skip to tail, iterate up.
         */
        assert_ret(sd_journal_open_directory(&j, t, 0));
        assert_ret(sd_journal_seek_head(j));
        assert_ret(r = sd_journal_next_skip(j, 4));
        assert_se(r == 4);
        test_check_numbers_up(j, 4);
        sd_journal_close(j);

        log_info("Done...");

        if (arg_keep)
                log_info("Not removing %s", t);
        else {
                journal_directory_vacuum(".", 3000000, 0, 0, NULL, true);

                assert_se(rm_rf(t, REMOVE_ROOT|REMOVE_PHYSICAL) >= 0);
        }

        puts("------------------------------------------------------------");
}