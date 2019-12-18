#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  usec_t ;
struct TYPE_9__ {int /*<<< orphan*/  monotonic; } ;
struct TYPE_8__ {int /*<<< orphan*/  monotonic; } ;
struct TYPE_11__ {TYPE_2__ state_change_timestamp; TYPE_1__ active_enter_timestamp; } ;
struct TYPE_10__ {int deserialized_state; int /*<<< orphan*/  timeout_stop_usec; int /*<<< orphan*/  runtime_max_usec; } ;
typedef  TYPE_3__ Scope ;

/* Variables and functions */
#define  SCOPE_RUNNING 130 
#define  SCOPE_STOP_SIGKILL 129 
#define  SCOPE_STOP_SIGTERM 128 
 TYPE_6__* UNIT (TYPE_3__*) ; 
 int /*<<< orphan*/  USEC_INFINITY ; 
 int /*<<< orphan*/  assert (TYPE_3__*) ; 
 int /*<<< orphan*/  usec_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static usec_t scope_coldplug_timeout(Scope *s) {
        assert(s);

        switch (s->deserialized_state) {

        case SCOPE_RUNNING:
                return usec_add(UNIT(s)->active_enter_timestamp.monotonic, s->runtime_max_usec);

        case SCOPE_STOP_SIGKILL:
        case SCOPE_STOP_SIGTERM:
                return usec_add(UNIT(s)->state_change_timestamp.monotonic, s->timeout_stop_usec);

        default:
                return USEC_INFINITY;
        }
}