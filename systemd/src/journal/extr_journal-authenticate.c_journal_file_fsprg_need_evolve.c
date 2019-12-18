#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_5__ {int /*<<< orphan*/  fsprg_state; int /*<<< orphan*/  seal; } ;
typedef  TYPE_1__ JournalFile ;

/* Variables and functions */
 int ESTALE ; 
 scalar_t__ FSPRG_GetEpoch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int journal_file_get_epoch (TYPE_1__*,scalar_t__,scalar_t__*) ; 

__attribute__((used)) static int journal_file_fsprg_need_evolve(JournalFile *f, uint64_t realtime) {
        uint64_t goal, epoch;
        int r;
        assert(f);

        if (!f->seal)
                return 0;

        r = journal_file_get_epoch(f, realtime, &goal);
        if (r < 0)
                return r;

        epoch = FSPRG_GetEpoch(f->fsprg_state);
        if (epoch > goal)
                return -ESTALE;

        return epoch != goal;
}