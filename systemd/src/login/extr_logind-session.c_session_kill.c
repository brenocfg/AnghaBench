#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  scope; int /*<<< orphan*/  manager; } ;
typedef  TYPE_1__ Session ;
typedef  int /*<<< orphan*/  KillWho ;

/* Variables and functions */
 int ESRCH ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int manager_kill_unit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

int session_kill(Session *s, KillWho who, int signo) {
        assert(s);

        if (!s->scope)
                return -ESRCH;

        return manager_kill_unit(s->manager, s->scope, who, signo, NULL);
}