#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct iovec {int dummy; } ;
typedef  int /*<<< orphan*/  sd_id128_t ;
typedef  int /*<<< orphan*/  dual_timestamp ;
struct TYPE_6__ {int /*<<< orphan*/  seqnum; int /*<<< orphan*/  boot_id; } ;
struct TYPE_7__ {TYPE_1__ entry; } ;
typedef  TYPE_2__ Object ;
typedef  int /*<<< orphan*/  JournalFile ;

/* Variables and functions */
 int /*<<< orphan*/  DIRECTION_DOWN ; 
 int /*<<< orphan*/  DIRECTION_UP ; 
 struct iovec IOVEC_MAKE_STRING (char const*) ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int REMOVE_PHYSICAL ; 
 int REMOVE_ROOT ; 
 scalar_t__ arg_keep ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int dual_timestamp_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  journal_directory_vacuum (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ journal_file_append_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct iovec*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  journal_file_append_tag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  journal_file_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  journal_file_dump (int /*<<< orphan*/ *) ; 
 int journal_file_find_data_object (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int journal_file_move_to_entry_by_seqnum (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,TYPE_2__**,int /*<<< orphan*/ *) ; 
 int journal_file_next_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__**,int /*<<< orphan*/ *) ; 
 int journal_file_next_entry_for_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__**,int /*<<< orphan*/ *) ; 
 scalar_t__ journal_file_open (int,char*,int,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  journal_file_rotate (int /*<<< orphan*/ **,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int le64toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_info (char*,...) ; 
 int /*<<< orphan*/  mkdtemp_chdir_chattr (char*) ; 
 int /*<<< orphan*/  puts (char*) ; 
 scalar_t__ rm_rf (char*,int) ; 
 int sd_id128_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sd_id128_randomize (int /*<<< orphan*/ *) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  test_setup_logging (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_non_empty(void) {
        dual_timestamp ts;
        JournalFile *f;
        struct iovec iovec;
        static const char test[] = "TEST1=1", test2[] = "TEST2=2";
        Object *o;
        uint64_t p;
        sd_id128_t fake_boot_id;
        char t[] = "/var/tmp/journal-XXXXXX";

        test_setup_logging(LOG_DEBUG);

        mkdtemp_chdir_chattr(t);

        assert_se(journal_file_open(-1, "test.journal", O_RDWR|O_CREAT, 0666, true, (uint64_t) -1, true, NULL, NULL, NULL, NULL, &f) == 0);

        assert_se(dual_timestamp_get(&ts));
        assert_se(sd_id128_randomize(&fake_boot_id) == 0);

        iovec = IOVEC_MAKE_STRING(test);
        assert_se(journal_file_append_entry(f, &ts, NULL, &iovec, 1, NULL, NULL, NULL) == 0);

        iovec = IOVEC_MAKE_STRING(test2);
        assert_se(journal_file_append_entry(f, &ts, NULL, &iovec, 1, NULL, NULL, NULL) == 0);

        iovec = IOVEC_MAKE_STRING(test);
        assert_se(journal_file_append_entry(f, &ts, &fake_boot_id, &iovec, 1, NULL, NULL, NULL) == 0);

#if HAVE_GCRYPT
        journal_file_append_tag(f);
#endif
        journal_file_dump(f);

        assert_se(journal_file_next_entry(f, 0, DIRECTION_DOWN, &o, &p) == 1);
        assert_se(le64toh(o->entry.seqnum) == 1);

        assert_se(journal_file_next_entry(f, p, DIRECTION_DOWN, &o, &p) == 1);
        assert_se(le64toh(o->entry.seqnum) == 2);

        assert_se(journal_file_next_entry(f, p, DIRECTION_DOWN, &o, &p) == 1);
        assert_se(le64toh(o->entry.seqnum) == 3);
        assert_se(sd_id128_equal(o->entry.boot_id, fake_boot_id));

        assert_se(journal_file_next_entry(f, p, DIRECTION_DOWN, &o, &p) == 0);

        assert_se(journal_file_next_entry(f, 0, DIRECTION_DOWN, &o, &p) == 1);
        assert_se(le64toh(o->entry.seqnum) == 1);

        assert_se(journal_file_find_data_object(f, test, strlen(test), NULL, &p) == 1);
        assert_se(journal_file_next_entry_for_data(f, NULL, 0, p, DIRECTION_DOWN, &o, NULL) == 1);
        assert_se(le64toh(o->entry.seqnum) == 1);

        assert_se(journal_file_next_entry_for_data(f, NULL, 0, p, DIRECTION_UP, &o, NULL) == 1);
        assert_se(le64toh(o->entry.seqnum) == 3);

        assert_se(journal_file_find_data_object(f, test2, strlen(test2), NULL, &p) == 1);
        assert_se(journal_file_next_entry_for_data(f, NULL, 0, p, DIRECTION_UP, &o, NULL) == 1);
        assert_se(le64toh(o->entry.seqnum) == 2);

        assert_se(journal_file_next_entry_for_data(f, NULL, 0, p, DIRECTION_DOWN, &o, NULL) == 1);
        assert_se(le64toh(o->entry.seqnum) == 2);

        assert_se(journal_file_find_data_object(f, "quux", 4, NULL, &p) == 0);

        assert_se(journal_file_move_to_entry_by_seqnum(f, 1, DIRECTION_DOWN, &o, NULL) == 1);
        assert_se(le64toh(o->entry.seqnum) == 1);

        assert_se(journal_file_move_to_entry_by_seqnum(f, 3, DIRECTION_DOWN, &o, NULL) == 1);
        assert_se(le64toh(o->entry.seqnum) == 3);

        assert_se(journal_file_move_to_entry_by_seqnum(f, 2, DIRECTION_DOWN, &o, NULL) == 1);
        assert_se(le64toh(o->entry.seqnum) == 2);

        assert_se(journal_file_move_to_entry_by_seqnum(f, 10, DIRECTION_DOWN, &o, NULL) == 0);

        journal_file_rotate(&f, true, (uint64_t) -1, true, NULL);
        journal_file_rotate(&f, true, (uint64_t) -1, true, NULL);

        (void) journal_file_close(f);

        log_info("Done...");

        if (arg_keep)
                log_info("Not removing %s", t);
        else {
                journal_directory_vacuum(".", 3000000, 0, 0, NULL, true);

                assert_se(rm_rf(t, REMOVE_ROOT|REMOVE_PHYSICAL) >= 0);
        }

        puts("------------------------------------------------------------");
}