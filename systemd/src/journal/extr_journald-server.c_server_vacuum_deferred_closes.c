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
struct TYPE_5__ {int /*<<< orphan*/  deferred_closes; } ;
typedef  TYPE_1__ Server ;
typedef  int /*<<< orphan*/  JournalFile ;

/* Variables and functions */
 scalar_t__ DEFERRED_CLOSES_MAX ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  assert_se (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  journal_file_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  server_process_deferred_closes (TYPE_1__*) ; 
 scalar_t__ set_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * set_steal_first (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void server_vacuum_deferred_closes(Server *s) {
        assert(s);

        /* Make some room in the deferred closes list, so that it doesn't grow without bounds */
        if (set_size(s->deferred_closes) < DEFERRED_CLOSES_MAX)
                return;

        /* Let's first remove all journal files that might already have completed closing */
        server_process_deferred_closes(s);

        /* And now, let's close some more until we reach the limit again. */
        while (set_size(s->deferred_closes) >= DEFERRED_CLOSES_MAX) {
                JournalFile *f;

                assert_se(f = set_steal_first(s->deferred_closes));
                journal_file_close(f);
        }
}