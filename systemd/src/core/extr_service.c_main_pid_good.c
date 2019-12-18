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
struct TYPE_4__ {scalar_t__ main_pid; scalar_t__ main_pid_alien; scalar_t__ main_pid_known; } ;
typedef  TYPE_1__ Service ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int pid_is_alive (scalar_t__) ; 

__attribute__((used)) static int main_pid_good(Service *s) {
        assert(s);

        /* Returns 0 if the pid is dead, > 0 if it is good, < 0 if we don't know */

        /* If we know the pid file, then let's just check if it is
         * still valid */
        if (s->main_pid_known) {

                /* If it's an alien child let's check if it is still
                 * alive ... */
                if (s->main_pid_alien && s->main_pid > 0)
                        return pid_is_alive(s->main_pid);

                /* .. otherwise assume we'll get a SIGCHLD for it,
                 * which we really should wait for to collect exit
                 * status and code */
                return s->main_pid > 0;
        }

        /* We don't know the pid */
        return -EAGAIN;
}