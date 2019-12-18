#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct iovec {int dummy; } ;
struct TYPE_4__ {scalar_t__ monotonic; scalar_t__ realtime; } ;
typedef  TYPE_1__ dual_timestamp ;
typedef  int /*<<< orphan*/  JournalFile ;

/* Variables and functions */
 struct iovec IOVEC_MAKE_STRING (char*) ; 
 scalar_t__ asprintf (char**,char*,int) ; 
 int /*<<< orphan*/  assert_ret (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  dual_timestamp_get (TYPE_1__*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  journal_file_append_entry (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,struct iovec*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void append_number(JournalFile *f, int n, uint64_t *seqnum) {
        char *p;
        dual_timestamp ts;
        static dual_timestamp previous_ts = {};
        struct iovec iovec[1];

        dual_timestamp_get(&ts);

        if (ts.monotonic <= previous_ts.monotonic)
                ts.monotonic = previous_ts.monotonic + 1;

        if (ts.realtime <= previous_ts.realtime)
                ts.realtime = previous_ts.realtime + 1;

        previous_ts = ts;

        assert_se(asprintf(&p, "NUMBER=%d", n) >= 0);
        iovec[0] = IOVEC_MAKE_STRING(p);
        assert_ret(journal_file_append_entry(f, &ts, NULL, iovec, 1, seqnum, NULL, NULL));
        free(p);
}