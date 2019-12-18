#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_2__* active; int /*<<< orphan*/  id; } ;
struct TYPE_12__ {TYPE_1__* user; } ;
struct TYPE_11__ {int /*<<< orphan*/  uid; } ;
struct TYPE_10__ {TYPE_3__* user; } ;
struct TYPE_9__ {int /*<<< orphan*/  uid; } ;
typedef  TYPE_4__ Session ;
typedef  TYPE_5__ Seat ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_5__*) ; 
 int devnode_acl_all (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int log_error_errno (int,char*) ; 

int seat_apply_acls(Seat *s, Session *old_active) {
        int r;

        assert(s);

        r = devnode_acl_all(s->id,
                            false,
                            !!old_active, old_active ? old_active->user->uid : 0,
                            !!s->active, s->active ? s->active->user->uid : 0);

        if (r < 0)
                return log_error_errno(r, "Failed to apply ACLs: %m");

        return 0;
}