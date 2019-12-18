#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ pid_t ;
struct TYPE_8__ {scalar_t__ leader; int /*<<< orphan*/  audit_id; TYPE_1__* manager; } ;
struct TYPE_7__ {int /*<<< orphan*/  sessions_by_leader; } ;
typedef  TYPE_2__ Session ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PID_TO_PTR (scalar_t__) ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  audit_session_from_pid (scalar_t__,int /*<<< orphan*/ *) ; 
 int hashmap_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  hashmap_remove_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ pid_is_valid (scalar_t__) ; 

int session_set_leader(Session *s, pid_t pid) {
        int r;

        assert(s);

        if (!pid_is_valid(pid))
                return -EINVAL;

        if (s->leader == pid)
                return 0;

        r = hashmap_put(s->manager->sessions_by_leader, PID_TO_PTR(pid), s);
        if (r < 0)
                return r;

        if (pid_is_valid(s->leader))
                (void) hashmap_remove_value(s->manager->sessions_by_leader, PID_TO_PTR(s->leader), s);

        s->leader = pid;
        (void) audit_session_from_pid(pid, &s->audit_id);

        return 1;
}