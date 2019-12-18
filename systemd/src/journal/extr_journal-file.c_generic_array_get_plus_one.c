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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  Object ;
typedef  int /*<<< orphan*/  JournalFile ;

/* Variables and functions */
 int /*<<< orphan*/  OBJECT_ENTRY ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int generic_array_get (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ **,scalar_t__*) ; 
 int journal_file_move_to_object (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int generic_array_get_plus_one(
                JournalFile *f,
                uint64_t extra,
                uint64_t first,
                uint64_t i,
                Object **ret, uint64_t *offset) {

        Object *o;

        assert(f);

        if (i == 0) {
                int r;

                r = journal_file_move_to_object(f, OBJECT_ENTRY, extra, &o);
                if (r < 0)
                        return r;

                if (ret)
                        *ret = o;

                if (offset)
                        *offset = extra;

                return 1;
        }

        return generic_array_get(f, first, i-1, ret, offset);
}