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
struct TYPE_4__ {int /*<<< orphan*/  slice; int /*<<< orphan*/  manager; } ;
typedef  TYPE_1__ User ;

/* Variables and functions */
 int /*<<< orphan*/  KILL_ALL ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int manager_kill_unit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

int user_kill(User *u, int signo) {
        assert(u);

        return manager_kill_unit(u->manager, u->slice, KILL_ALL, signo, NULL);
}