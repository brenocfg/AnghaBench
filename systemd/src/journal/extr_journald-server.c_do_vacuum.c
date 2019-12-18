#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  limit; } ;
struct TYPE_13__ {int /*<<< orphan*/  n_max_files; } ;
struct TYPE_14__ {TYPE_10__ space; int /*<<< orphan*/  path; int /*<<< orphan*/  oldest_file_usec; int /*<<< orphan*/  max_retention_usec; TYPE_1__ metrics; } ;
typedef  TYPE_2__ Server ;
typedef  TYPE_2__ JournalStorage ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  cache_space_invalidate (TYPE_10__*) ; 
 int /*<<< orphan*/  cache_space_refresh (TYPE_2__*,TYPE_2__*) ; 
 int journal_directory_vacuum (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  log_warning_errno (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  server_space_usage_message (TYPE_2__*,TYPE_2__*) ; 

__attribute__((used)) static void do_vacuum(Server *s, JournalStorage *storage, bool verbose) {

        int r;

        assert(s);
        assert(storage);

        (void) cache_space_refresh(s, storage);

        if (verbose)
                server_space_usage_message(s, storage);

        r = journal_directory_vacuum(storage->path, storage->space.limit,
                                     storage->metrics.n_max_files, s->max_retention_usec,
                                     &s->oldest_file_usec, verbose);
        if (r < 0 && r != -ENOENT)
                log_warning_errno(r, "Failed to vacuum %s, ignoring: %m", storage->path);

        cache_space_invalidate(&storage->space);
}