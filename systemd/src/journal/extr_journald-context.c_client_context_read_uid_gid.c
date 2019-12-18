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
struct ucred {int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
struct TYPE_5__ {int /*<<< orphan*/  gid; int /*<<< orphan*/  pid; int /*<<< orphan*/  uid; } ;
typedef  TYPE_1__ ClientContext ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  get_process_gid (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_process_uid (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ gid_is_valid (int /*<<< orphan*/ ) ; 
 TYPE_1__* pid_is_valid (int /*<<< orphan*/ ) ; 
 scalar_t__ uid_is_valid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void client_context_read_uid_gid(ClientContext *c, const struct ucred *ucred) {
        assert(c);
        assert(pid_is_valid(c->pid));

        /* The ucred data passed in is always the most current and accurate, if we have any. Use it. */
        if (ucred && uid_is_valid(ucred->uid))
                c->uid = ucred->uid;
        else
                (void) get_process_uid(c->pid, &c->uid);

        if (ucred && gid_is_valid(ucred->gid))
                c->gid = ucred->gid;
        else
                (void) get_process_gid(c->pid, &c->gid);
}