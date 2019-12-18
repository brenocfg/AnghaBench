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
struct TYPE_4__ {scalar_t__ current_invalidate_counter; scalar_t__ last_invalidate_counter; } ;
typedef  TYPE_1__ sd_journal ;

/* Variables and functions */
 int SD_JOURNAL_APPEND ; 
 int SD_JOURNAL_INVALIDATE ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

__attribute__((used)) static int determine_change(sd_journal *j) {
        bool b;

        assert(j);

        b = j->current_invalidate_counter != j->last_invalidate_counter;
        j->last_invalidate_counter = j->current_invalidate_counter;

        return b ? SD_JOURNAL_INVALIDATE : SD_JOURNAL_APPEND;
}