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
typedef  int /*<<< orphan*/  Set ;
typedef  int /*<<< orphan*/  JournalFile ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * journal_file_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  journal_file_set_offline (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  log_debug_errno (int,char*) ; 
 int set_put (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

JournalFile* journal_initiate_close(
                JournalFile *f,
                Set *deferred_closes) {

        int r;

        assert(f);

        if (deferred_closes) {

                r = set_put(deferred_closes, f);
                if (r < 0)
                        log_debug_errno(r, "Failed to add file to deferred close set, closing immediately.");
                else {
                        (void) journal_file_set_offline(f, false);
                        return NULL;
                }
        }

        return journal_file_close(f);
}