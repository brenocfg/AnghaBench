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
typedef  int /*<<< orphan*/  Server ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_warning_errno (int,char*) ; 
 int /*<<< orphan*/  now (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  server_sync (int /*<<< orphan*/ *) ; 
 int write_timestamp_file_atomic (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void server_full_sync(Server *s) {
        int r;

        assert(s);

        server_sync(s);

        /* Let clients know when the most recent sync happened. */
        r = write_timestamp_file_atomic("/run/systemd/journal/synced", now(CLOCK_MONOTONIC));
        if (r < 0)
                log_warning_errno(r, "Failed to write /run/systemd/journal/synced, ignoring: %m");

        return;
}