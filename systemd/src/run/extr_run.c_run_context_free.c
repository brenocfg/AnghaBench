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
struct TYPE_4__ {int /*<<< orphan*/  result; int /*<<< orphan*/  active_state; int /*<<< orphan*/  event; int /*<<< orphan*/  bus; int /*<<< orphan*/  match; int /*<<< orphan*/  forward; } ;
typedef  TYPE_1__ RunContext ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pty_forward_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_bus_slot_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_bus_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_unref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void run_context_free(RunContext *c) {
        assert(c);

        c->forward = pty_forward_free(c->forward);
        c->match = sd_bus_slot_unref(c->match);
        c->bus = sd_bus_unref(c->bus);
        c->event = sd_event_unref(c->event);

        free(c->active_state);
        free(c->result);
}