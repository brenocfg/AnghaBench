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
struct TYPE_4__ {int n_canceled; int /*<<< orphan*/  pid; } ;
typedef  TYPE_1__ Transfer ;

/* Variables and functions */
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int kill_and_sigcont (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int transfer_cancel(Transfer *t) {
        int r;

        assert(t);

        r = kill_and_sigcont(t->pid, t->n_canceled < 3 ? SIGTERM : SIGKILL);
        if (r < 0)
                return r;

        t->n_canceled++;
        return 0;
}