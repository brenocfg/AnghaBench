#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_4__ {int /*<<< orphan*/  monotonic; } ;
struct TYPE_5__ {TYPE_1__ entry; } ;
typedef  TYPE_2__ Object ;
typedef  int /*<<< orphan*/  JournalFile ;

/* Variables and functions */
 int /*<<< orphan*/  OBJECT_ENTRY ; 
 int TEST_FOUND ; 
 int TEST_LEFT ; 
 int TEST_RIGHT ; 
 int /*<<< orphan*/  assert (int) ; 
 int journal_file_move_to_object (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,TYPE_2__**) ; 
 scalar_t__ le64toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_object_monotonic(JournalFile *f, uint64_t p, uint64_t needle) {
        Object *o;
        int r;

        assert(f);
        assert(p > 0);

        r = journal_file_move_to_object(f, OBJECT_ENTRY, p, &o);
        if (r < 0)
                return r;

        if (le64toh(o->entry.monotonic) == needle)
                return TEST_FOUND;
        else if (le64toh(o->entry.monotonic) < needle)
                return TEST_LEFT;
        else
                return TEST_RIGHT;
}