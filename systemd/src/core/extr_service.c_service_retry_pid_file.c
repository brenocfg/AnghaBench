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
struct TYPE_6__ {int /*<<< orphan*/  state; int /*<<< orphan*/  pid_file; } ;
typedef  TYPE_1__ Service ;

/* Variables and functions */
 int /*<<< orphan*/  IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SERVICE_START ; 
 int /*<<< orphan*/  SERVICE_START_POST ; 
 int /*<<< orphan*/  SERVICE_SUCCESS ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  service_enter_running (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int service_load_pid_file (TYPE_1__*,int) ; 
 int /*<<< orphan*/  service_unwatch_pid_file (TYPE_1__*) ; 

__attribute__((used)) static int service_retry_pid_file(Service *s) {
        int r;

        assert(s->pid_file);
        assert(IN_SET(s->state, SERVICE_START, SERVICE_START_POST));

        r = service_load_pid_file(s, false);
        if (r < 0)
                return r;

        service_unwatch_pid_file(s);

        service_enter_running(s, SERVICE_SUCCESS);
        return 0;
}