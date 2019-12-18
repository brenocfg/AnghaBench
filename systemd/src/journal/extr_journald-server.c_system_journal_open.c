#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {char* path; int /*<<< orphan*/  metrics; } ;
struct TYPE_8__ {int storage; int seal; TYPE_4__ runtime_storage; scalar_t__ runtime_journal; scalar_t__ system_journal; TYPE_4__ system_storage; } ;
typedef  TYPE_1__ Server ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  EROFS ; 
 scalar_t__ IN_SET (int,int,int /*<<< orphan*/ ) ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int /*<<< orphan*/  STORAGE_AUTO ; 
 scalar_t__ STORAGE_NONE ; 
 scalar_t__ STORAGE_PERSISTENT ; 
 int /*<<< orphan*/  cache_space_refresh (TYPE_1__*,TYPE_4__*) ; 
 scalar_t__ flushed_flag_is_set () ; 
 int log_error_errno (int,char*) ; 
 int /*<<< orphan*/  log_warning_errno (int,char*) ; 
 int /*<<< orphan*/  mkdir (char*,int) ; 
 int /*<<< orphan*/  mkdir_p (char*,int) ; 
 int /*<<< orphan*/  mkdir_parents (char const*,int) ; 
 int open_journal (TYPE_1__*,int,char const*,int,int,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  patch_min_use (TYPE_4__*) ; 
 int /*<<< orphan*/  server_add_acls (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  server_flush_to_var (TYPE_1__*,int) ; 
 char* strjoina (char*,char*) ; 

__attribute__((used)) static int system_journal_open(Server *s, bool flush_requested, bool relinquish_requested) {
        const char *fn;
        int r = 0;

        if (!s->system_journal &&
            IN_SET(s->storage, STORAGE_PERSISTENT, STORAGE_AUTO) &&
            (flush_requested || flushed_flag_is_set()) &&
            !relinquish_requested) {

                /* If in auto mode: first try to create the machine
                 * path, but not the prefix.
                 *
                 * If in persistent mode: create /var/log/journal and
                 * the machine path */

                if (s->storage == STORAGE_PERSISTENT)
                        (void) mkdir_p("/var/log/journal/", 0755);

                (void) mkdir(s->system_storage.path, 0755);

                fn = strjoina(s->system_storage.path, "/system.journal");
                r = open_journal(s, true, fn, O_RDWR|O_CREAT, s->seal, &s->system_storage.metrics, &s->system_journal);
                if (r >= 0) {
                        server_add_acls(s->system_journal, 0);
                        (void) cache_space_refresh(s, &s->system_storage);
                        patch_min_use(&s->system_storage);
                } else {
                        if (!IN_SET(r, -ENOENT, -EROFS))
                                log_warning_errno(r, "Failed to open system journal: %m");

                        r = 0;
                }

                /* If the runtime journal is open, and we're post-flush, we're
                 * recovering from a failed system journal rotate (ENOSPC)
                 * for which the runtime journal was reopened.
                 *
                 * Perform an implicit flush to var, leaving the runtime
                 * journal closed, now that the system journal is back.
                 */
                if (!flush_requested)
                        (void) server_flush_to_var(s, true);
        }

        if (!s->runtime_journal &&
            (s->storage != STORAGE_NONE)) {

                fn = strjoina(s->runtime_storage.path, "/system.journal");

                if (s->system_journal && !relinquish_requested) {

                        /* Try to open the runtime journal, but only
                         * if it already exists, so that we can flush
                         * it into the system journal */

                        r = open_journal(s, false, fn, O_RDWR, false, &s->runtime_storage.metrics, &s->runtime_journal);
                        if (r < 0) {
                                if (r != -ENOENT)
                                        log_warning_errno(r, "Failed to open runtime journal: %m");

                                r = 0;
                        }

                } else {

                        /* OK, we really need the runtime journal, so create
                         * it if necessary. */

                        (void) mkdir("/run/log", 0755);
                        (void) mkdir("/run/log/journal", 0755);
                        (void) mkdir_parents(fn, 0750);

                        r = open_journal(s, true, fn, O_RDWR|O_CREAT, false, &s->runtime_storage.metrics, &s->runtime_journal);
                        if (r < 0)
                                return log_error_errno(r, "Failed to open runtime journal: %m");
                }

                if (s->runtime_journal) {
                        server_add_acls(s->runtime_journal, 0);
                        (void) cache_space_refresh(s, &s->runtime_storage);
                        patch_min_use(&s->runtime_storage);
                }
        }

        return r;
}