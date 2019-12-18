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
 int O_CREAT ; 
 int O_RDWR ; 
 int /*<<< orphan*/  assert_ret (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  journal_file_open (int,char const*,int,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

__attribute__((used)) static JournalFile *test_open(const char *name) {
        JournalFile *f;
        assert_ret(journal_file_open(-1, name, O_RDWR|O_CREAT, 0644, true, (uint64_t) -1, false, NULL, NULL, NULL, NULL, &f));
        return f;
}