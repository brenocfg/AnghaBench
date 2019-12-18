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
struct TYPE_5__ {scalar_t__ storage; int /*<<< orphan*/  deferred_closes; int /*<<< orphan*/  user_journals; scalar_t__ system_journal; scalar_t__ runtime_journal; } ;
typedef  TYPE_1__ Server ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 scalar_t__ STORAGE_NONE ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 scalar_t__ errno ; 
 scalar_t__ journal_file_close (scalar_t__) ; 
 int /*<<< orphan*/  log_debug (char*) ; 
 int /*<<< orphan*/  log_warning_errno (scalar_t__,char*) ; 
 int /*<<< orphan*/  ordered_hashmap_clear_with_destructor (int /*<<< orphan*/ ,scalar_t__ (*) (scalar_t__)) ; 
 int /*<<< orphan*/  set_clear_with_destructor (int /*<<< orphan*/ ,scalar_t__ (*) (scalar_t__)) ; 
 int /*<<< orphan*/  system_journal_open (TYPE_1__*,int,int) ; 
 scalar_t__ unlink (char*) ; 

__attribute__((used)) static int server_relinquish_var(Server *s) {
        assert(s);

        if (s->storage == STORAGE_NONE)
                return 0;

        if (s->runtime_journal && !s->system_journal)
                return 0;

        log_debug("Relinquishing /var...");

        (void) system_journal_open(s, false, true);

        s->system_journal = journal_file_close(s->system_journal);
        ordered_hashmap_clear_with_destructor(s->user_journals, journal_file_close);
        set_clear_with_destructor(s->deferred_closes, journal_file_close);

        if (unlink("/run/systemd/journal/flushed") < 0 && errno != ENOENT)
                log_warning_errno(errno, "Failed to unlink /run/systemd/journal/flushed, ignoring: %m");

        return 0;
}