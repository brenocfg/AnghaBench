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
struct TYPE_4__ {scalar_t__ state; scalar_t__ input_buffer_unscanned; scalar_t__ output_buffer_size; int /*<<< orphan*/  write_disconnected; int /*<<< orphan*/  current; int /*<<< orphan*/  read_disconnected; scalar_t__ connecting; } ;
typedef  TYPE_1__ Varlink ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int ENOTCONN ; 
 int EPOLLIN ; 
 int EPOLLOUT ; 
 scalar_t__ IN_SET (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VARLINK_AWAITING_REPLY ; 
 int /*<<< orphan*/  VARLINK_CALLING ; 
 scalar_t__ VARLINK_DISCONNECTED ; 
 int /*<<< orphan*/  VARLINK_IDLE_SERVER ; 
 int /*<<< orphan*/  assert_return (TYPE_1__*,int /*<<< orphan*/ ) ; 

int varlink_get_events(Varlink *v) {
        int ret = 0;

        assert_return(v, -EINVAL);

        if (v->state == VARLINK_DISCONNECTED)
                return -ENOTCONN;

        if (v->connecting) /* When processing an asynchronous connect(), we only wait for EPOLLOUT, which
                            * tells us that the connection is now complete. Before that we should neither
                            * write() or read() from the fd. */
                return EPOLLOUT;

        if (!v->read_disconnected &&
            IN_SET(v->state, VARLINK_AWAITING_REPLY, VARLINK_CALLING, VARLINK_IDLE_SERVER) &&
            !v->current &&
            v->input_buffer_unscanned <= 0)
                ret |= EPOLLIN;

        if (!v->write_disconnected &&
            v->output_buffer_size > 0)
                ret |= EPOLLOUT;

        return ret;
}