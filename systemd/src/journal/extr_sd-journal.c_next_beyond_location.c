#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_12__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_14__ {scalar_t__ type; } ;
struct TYPE_16__ {scalar_t__ location_type; scalar_t__ last_n_entries; scalar_t__ current_offset; TYPE_12__ current_location; int /*<<< orphan*/  last_direction; TYPE_1__* header; } ;
typedef  TYPE_2__ sd_journal ;
typedef  int /*<<< orphan*/  direction_t ;
struct TYPE_15__ {int /*<<< orphan*/  n_entries; } ;
typedef  int /*<<< orphan*/  Object ;
typedef  TYPE_2__ JournalFile ;

/* Variables and functions */
 int /*<<< orphan*/  DIRECTION_DOWN ; 
 scalar_t__ LOCATION_DISCRETE ; 
 scalar_t__ LOCATION_SEEK ; 
 scalar_t__ LOCATION_TAIL ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int compare_with_location (TYPE_2__*,TYPE_12__*) ; 
 int find_location_with_matches (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,scalar_t__*) ; 
 int /*<<< orphan*/  journal_file_save_location (TYPE_2__*,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ le64toh (int /*<<< orphan*/ ) ; 
 int next_with_matches (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,scalar_t__*) ; 

__attribute__((used)) static int next_beyond_location(sd_journal *j, JournalFile *f, direction_t direction) {
        Object *c;
        uint64_t cp, n_entries;
        int r;

        assert(j);
        assert(f);

        n_entries = le64toh(f->header->n_entries);

        /* If we hit EOF before, we don't need to look into this file again
         * unless direction changed or new entries appeared. */
        if (f->last_direction == direction && f->location_type == LOCATION_TAIL &&
            n_entries == f->last_n_entries)
                return 0;

        f->last_n_entries = n_entries;

        if (f->last_direction == direction && f->current_offset > 0) {
                /* LOCATION_SEEK here means we did the work in a previous
                 * iteration and the current location already points to a
                 * candidate entry. */
                if (f->location_type != LOCATION_SEEK) {
                        r = next_with_matches(j, f, direction, &c, &cp);
                        if (r <= 0)
                                return r;

                        journal_file_save_location(f, c, cp);
                }
        } else {
                f->last_direction = direction;

                r = find_location_with_matches(j, f, direction, &c, &cp);
                if (r <= 0)
                        return r;

                journal_file_save_location(f, c, cp);
        }

        /* OK, we found the spot, now let's advance until an entry
         * that is actually different from what we were previously
         * looking at. This is necessary to handle entries which exist
         * in two (or more) journal files, and which shall all be
         * suppressed but one. */

        for (;;) {
                bool found;

                if (j->current_location.type == LOCATION_DISCRETE) {
                        int k;

                        k = compare_with_location(f, &j->current_location);

                        found = direction == DIRECTION_DOWN ? k > 0 : k < 0;
                } else
                        found = true;

                if (found)
                        return 1;

                r = next_with_matches(j, f, direction, &c, &cp);
                if (r <= 0)
                        return r;

                journal_file_save_location(f, c, cp);
        }
}