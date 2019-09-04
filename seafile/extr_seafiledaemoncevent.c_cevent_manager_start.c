#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  ev_base; } ;
struct TYPE_5__ {int /*<<< orphan*/  event; int /*<<< orphan*/ * pipefd; } ;
typedef  TYPE_1__ CEventManager ;

/* Variables and functions */
 int EV_PERSIST ; 
 int EV_READ ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  event_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  g_warning (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pipe_callback ; 
 TYPE_2__* seaf ; 
 scalar_t__ seaf_pipe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

int cevent_manager_start (CEventManager *manager)
{
    if (seaf_pipe(manager->pipefd) < 0) {
        g_warning ("pipe error: %s\n", strerror(errno));
        return -1;
    }

    manager->event = event_new (seaf->ev_base, manager->pipefd[0],
               EV_READ | EV_PERSIST, pipe_callback, manager);
    event_add (manager->event, NULL);

    return 0;
}