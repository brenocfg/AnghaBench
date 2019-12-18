#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  runtime_storage; scalar_t__ runtime_journal; int /*<<< orphan*/  system_storage; scalar_t__ system_journal; } ;
typedef  TYPE_1__ Server ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  log_warning_errno (int,char*) ; 
 int /*<<< orphan*/  now (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  patch_min_use (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  server_rotate (TYPE_1__*) ; 
 int /*<<< orphan*/  server_vacuum (TYPE_1__*,int) ; 
 int write_timestamp_file_atomic (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void server_full_rotate(Server *s) {
        int r;

        assert(s);

        server_rotate(s);
        server_vacuum(s, true);

        if (s->system_journal)
                patch_min_use(&s->system_storage);
        if (s->runtime_journal)
                patch_min_use(&s->runtime_storage);

        /* Let clients know when the most recent rotation happened. */
        r = write_timestamp_file_atomic("/run/systemd/journal/rotated", now(CLOCK_MONOTONIC));
        if (r < 0)
                log_warning_errno(r, "Failed to write /run/systemd/journal/rotated, ignoring: %m");
}