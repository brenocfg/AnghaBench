#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* manager; } ;
struct TYPE_9__ {scalar_t__ pipe_fd; scalar_t__ where; int /*<<< orphan*/  expire_tokens; int /*<<< orphan*/  tokens; int /*<<< orphan*/  pipe_event_source; } ;
struct TYPE_8__ {int /*<<< orphan*/  objective; } ;
typedef  TYPE_2__ Automount ;

/* Variables and functions */
 int /*<<< orphan*/  EHOSTDOWN ; 
 int /*<<< orphan*/  IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MANAGER_REEXECUTE ; 
 int /*<<< orphan*/  MANAGER_RELOAD ; 
 int /*<<< orphan*/  MNT_DETACH ; 
 TYPE_6__* UNIT (TYPE_2__*) ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  automount_send_ready (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_error_errno (int,char*) ; 
 int repeat_unmount (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ safe_close (scalar_t__) ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void unmount_autofs(Automount *a) {
        int r;

        assert(a);

        if (a->pipe_fd < 0)
                return;

        a->pipe_event_source = sd_event_source_unref(a->pipe_event_source);
        a->pipe_fd = safe_close(a->pipe_fd);

        /* If we reload/reexecute things we keep the mount point around */
        if (!IN_SET(UNIT(a)->manager->objective, MANAGER_RELOAD, MANAGER_REEXECUTE)) {

                automount_send_ready(a, a->tokens, -EHOSTDOWN);
                automount_send_ready(a, a->expire_tokens, -EHOSTDOWN);

                if (a->where) {
                        r = repeat_unmount(a->where, MNT_DETACH);
                        if (r < 0)
                                log_error_errno(r, "Failed to unmount: %m");
                }
        }
}