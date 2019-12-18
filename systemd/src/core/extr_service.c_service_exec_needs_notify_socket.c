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
struct TYPE_4__ {scalar_t__ notify_access; } ;
typedef  TYPE_1__ Service ;
typedef  int ExecFlags ;

/* Variables and functions */
 int EXEC_IS_CONTROL ; 
 int IN_SET (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NOTIFY_ALL ; 
 int /*<<< orphan*/  NOTIFY_EXEC ; 
 scalar_t__ NOTIFY_NONE ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

__attribute__((used)) static bool service_exec_needs_notify_socket(Service *s, ExecFlags flags) {
        assert(s);

        /* Notifications are accepted depending on the process and
         * the access setting of the service:
         *     process: \ access:  NONE  MAIN  EXEC   ALL
         *     main                  no   yes   yes   yes
         *     control               no    no   yes   yes
         *     other (forked)        no    no    no   yes */

        if (flags & EXEC_IS_CONTROL)
                /* A control process */
                return IN_SET(s->notify_access, NOTIFY_EXEC, NOTIFY_ALL);

        /* We only spawn main processes and control processes, so any
         * process that is not a control process is a main process */
        return s->notify_access != NOTIFY_NONE;
}