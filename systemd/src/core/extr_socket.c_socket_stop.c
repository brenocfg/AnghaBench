#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Unit ;
struct TYPE_7__ {scalar_t__ state; } ;
typedef  TYPE_1__ Socket ;

/* Variables and functions */
 int EAGAIN ; 
 TYPE_1__* IN_SET (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 TYPE_1__* SOCKET (int /*<<< orphan*/ *) ; 
 scalar_t__ SOCKET_CLEANING ; 
 int /*<<< orphan*/  SOCKET_FINAL_SIGKILL ; 
 int /*<<< orphan*/  SOCKET_FINAL_SIGTERM ; 
 int /*<<< orphan*/  SOCKET_LISTENING ; 
 int /*<<< orphan*/  SOCKET_RUNNING ; 
 int /*<<< orphan*/  SOCKET_START_CHOWN ; 
 int /*<<< orphan*/  SOCKET_START_POST ; 
 int /*<<< orphan*/  SOCKET_START_PRE ; 
 int /*<<< orphan*/  SOCKET_STOP_POST ; 
 int /*<<< orphan*/  SOCKET_STOP_PRE ; 
 int /*<<< orphan*/  SOCKET_STOP_PRE_SIGKILL ; 
 int /*<<< orphan*/  SOCKET_STOP_PRE_SIGTERM ; 
 int /*<<< orphan*/  SOCKET_SUCCESS ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  socket_enter_signal (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_enter_stop_pre (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int socket_stop(Unit *u) {
        Socket *s = SOCKET(u);

        assert(s);

        /* Already on it */
        if (IN_SET(s->state,
                   SOCKET_STOP_PRE,
                   SOCKET_STOP_PRE_SIGTERM,
                   SOCKET_STOP_PRE_SIGKILL,
                   SOCKET_STOP_POST,
                   SOCKET_FINAL_SIGTERM,
                   SOCKET_FINAL_SIGKILL))
                return 0;

        /* If there's already something running we go directly into
         * kill mode. */
        if (IN_SET(s->state,
                   SOCKET_START_PRE,
                   SOCKET_START_CHOWN,
                   SOCKET_START_POST)) {
                socket_enter_signal(s, SOCKET_STOP_PRE_SIGTERM, SOCKET_SUCCESS);
                return -EAGAIN;
        }

        /* If we are currently cleaning, then abort it, brutally. */
        if (s->state == SOCKET_CLEANING) {
                socket_enter_signal(s, SOCKET_FINAL_SIGKILL, SOCKET_SUCCESS);
                return 0;
        }

        assert(IN_SET(s->state, SOCKET_LISTENING, SOCKET_RUNNING));

        socket_enter_stop_pre(s, SOCKET_SUCCESS);
        return 1;
}