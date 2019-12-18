#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ output_buffer_size; scalar_t__ got_pollhup; scalar_t__ write_disconnected; int /*<<< orphan*/  state; scalar_t__ read_disconnected; scalar_t__ connecting; } ;
typedef  TYPE_1__ Varlink ;

/* Variables and functions */
 scalar_t__ IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  VARLINK_AWAITING_REPLY ; 
 int /*<<< orphan*/  VARLINK_CALLING ; 
 int /*<<< orphan*/  VARLINK_IDLE_CLIENT ; 
 int /*<<< orphan*/  VARLINK_IDLE_SERVER ; 
 int /*<<< orphan*/  VARLINK_PENDING_DISCONNECT ; 
 int /*<<< orphan*/  VARLINK_STATE_IS_ALIVE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  varlink_set_state (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int varlink_test_disconnect(Varlink *v) {
        assert(v);

        /* Tests whether we the the connection has been terminated. We are careful to not stop processing it
         * prematurely, since we want to handle half-open connections as well as possible and want to flush
         * out and read data before we close down if we can. */

        /* Already disconnected? */
        if (!VARLINK_STATE_IS_ALIVE(v->state))
                return 0;

        /* Wait until connection setup is complete, i.e. until asynchronous connect() completes */
        if (v->connecting)
                return 0;

        /* Still something to write and we can write? Stay around */
        if (v->output_buffer_size > 0 && !v->write_disconnected)
                return 0;

        /* Both sides gone already? Then there's no need to stick around */
        if (v->read_disconnected && v->write_disconnected)
                goto disconnect;

        /* If we are waiting for incoming data but the read side is shut down, disconnect. */
        if (IN_SET(v->state, VARLINK_AWAITING_REPLY, VARLINK_CALLING, VARLINK_IDLE_SERVER) && v->read_disconnected)
                goto disconnect;

        /* Similar, if are a client that hasn't written anything yet but the write side is dead, also
         * disconnect. We also explicitly check for POLLHUP here since we likely won't notice the write side
         * being down if we never wrote anything. */
        if (IN_SET(v->state, VARLINK_IDLE_CLIENT) && (v->write_disconnected || v->got_pollhup))
                goto disconnect;

        return 0;

disconnect:
        varlink_set_state(v, VARLINK_PENDING_DISCONNECT);
        return 1;
}