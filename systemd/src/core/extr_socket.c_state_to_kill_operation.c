#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ SocketState ;
typedef  int /*<<< orphan*/  Socket ;

/* Variables and functions */
 int /*<<< orphan*/  JOB_RESTART ; 
 int KILL_KILL ; 
 int KILL_RESTART ; 
 int KILL_TERMINATE ; 
 scalar_t__ SOCKET_FINAL_SIGTERM ; 
 scalar_t__ SOCKET_STOP_PRE_SIGTERM ; 
 int /*<<< orphan*/  UNIT (int /*<<< orphan*/ *) ; 
 scalar_t__ unit_has_job_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int state_to_kill_operation(Socket *s, SocketState state) {
        if (state == SOCKET_STOP_PRE_SIGTERM && unit_has_job_type(UNIT(s), JOB_RESTART))
                return KILL_RESTART;

        if (state == SOCKET_FINAL_SIGTERM)
                return KILL_TERMINATE;

        return KILL_KILL;
}