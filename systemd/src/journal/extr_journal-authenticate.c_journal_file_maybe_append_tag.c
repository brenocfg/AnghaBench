#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_7__ {int /*<<< orphan*/  seal; } ;
typedef  TYPE_1__ JournalFile ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int journal_file_append_tag (TYPE_1__*) ; 
 int journal_file_fsprg_evolve (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int journal_file_fsprg_need_evolve (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  now (int /*<<< orphan*/ ) ; 

int journal_file_maybe_append_tag(JournalFile *f, uint64_t realtime) {
        int r;

        assert(f);

        if (!f->seal)
                return 0;

        if (realtime <= 0)
                realtime = now(CLOCK_REALTIME);

        r = journal_file_fsprg_need_evolve(f, realtime);
        if (r <= 0)
                return 0;

        r = journal_file_append_tag(f);
        if (r < 0)
                return r;

        r = journal_file_fsprg_evolve(f, realtime);
        if (r < 0)
                return r;

        return 0;
}