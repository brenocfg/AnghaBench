#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ n_fds; TYPE_1__* header; scalar_t__ accept_fd; scalar_t__ is_monitor; } ;
typedef  TYPE_2__ sd_bus_message ;
typedef  TYPE_2__ sd_bus ;
struct TYPE_8__ {scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  SD_BUS_ERROR_INCONSISTENT_MESSAGE ; 
 scalar_t__ SD_BUS_MESSAGE_METHOD_CALL ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int sd_bus_reply_method_errorf (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int process_fd_check(sd_bus *bus, sd_bus_message *m) {
        assert(bus);
        assert(m);

        /* If we got a message with a file descriptor which we didn't
         * want to accept, then let's drop it. How can this even
         * happen? For example, when the kernel queues a message into
         * an activatable names's queue which allows fds, and then is
         * delivered to us later even though we ourselves did not
         * negotiate it. */

        if (bus->is_monitor)
                return 0;

        if (m->n_fds <= 0)
                return 0;

        if (bus->accept_fd)
                return 0;

        if (m->header->type != SD_BUS_MESSAGE_METHOD_CALL)
                return 1; /* just eat it up */

        return sd_bus_reply_method_errorf(m, SD_BUS_ERROR_INCONSISTENT_MESSAGE, "Message contains file descriptors, which I cannot accept. Sorry.");
}