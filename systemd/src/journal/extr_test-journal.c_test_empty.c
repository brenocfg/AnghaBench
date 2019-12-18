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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  JournalFile ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int REMOVE_PHYSICAL ; 
 int REMOVE_ROOT ; 
 scalar_t__ arg_keep ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  journal_directory_vacuum (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  journal_file_close (int /*<<< orphan*/ *) ; 
 scalar_t__ journal_file_open (int,char*,int,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  journal_file_print_header (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_info (char*,...) ; 
 int /*<<< orphan*/  mkdtemp_chdir_chattr (char*) ; 
 int /*<<< orphan*/  puts (char*) ; 
 scalar_t__ rm_rf (char*,int) ; 
 int /*<<< orphan*/  test_setup_logging (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_empty(void) {
        JournalFile *f1, *f2, *f3, *f4;
        char t[] = "/var/tmp/journal-XXXXXX";

        test_setup_logging(LOG_DEBUG);

        mkdtemp_chdir_chattr(t);

        assert_se(journal_file_open(-1, "test.journal", O_RDWR|O_CREAT, 0666, false, (uint64_t) -1, false, NULL, NULL, NULL, NULL, &f1) == 0);

        assert_se(journal_file_open(-1, "test-compress.journal", O_RDWR|O_CREAT, 0666, true, (uint64_t) -1, false, NULL, NULL, NULL, NULL, &f2) == 0);

        assert_se(journal_file_open(-1, "test-seal.journal", O_RDWR|O_CREAT, 0666, false, (uint64_t) -1, true, NULL, NULL, NULL, NULL, &f3) == 0);

        assert_se(journal_file_open(-1, "test-seal-compress.journal", O_RDWR|O_CREAT, 0666, true, (uint64_t) -1, true, NULL, NULL, NULL, NULL, &f4) == 0);

        journal_file_print_header(f1);
        puts("");
        journal_file_print_header(f2);
        puts("");
        journal_file_print_header(f3);
        puts("");
        journal_file_print_header(f4);
        puts("");

        log_info("Done...");

        if (arg_keep)
                log_info("Not removing %s", t);
        else {
                journal_directory_vacuum(".", 3000000, 0, 0, NULL, true);

                assert_se(rm_rf(t, REMOVE_ROOT|REMOVE_PHYSICAL) >= 0);
        }

        (void) journal_file_close(f1);
        (void) journal_file_close(f2);
        (void) journal_file_close(f3);
        (void) journal_file_close(f4);
}