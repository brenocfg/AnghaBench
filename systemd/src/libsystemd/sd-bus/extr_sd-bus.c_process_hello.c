#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ state; int reply_cookie; TYPE_1__* header; } ;
typedef  TYPE_2__ sd_bus_message ;
typedef  TYPE_2__ sd_bus ;
struct TYPE_7__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 scalar_t__ BUS_HELLO ; 
 int EIO ; 
 int /*<<< orphan*/  IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SD_BUS_MESSAGE_METHOD_ERROR ; 
 int /*<<< orphan*/  SD_BUS_MESSAGE_METHOD_RETURN ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 

__attribute__((used)) static int process_hello(sd_bus *bus, sd_bus_message *m) {
        assert(bus);
        assert(m);

        if (bus->state != BUS_HELLO)
                return 0;

        /* Let's make sure the first message on the bus is the HELLO
         * reply. But note that we don't actually parse the message
         * here (we leave that to the usual handling), we just verify
         * we don't let any earlier msg through. */

        if (!IN_SET(m->header->type, SD_BUS_MESSAGE_METHOD_RETURN, SD_BUS_MESSAGE_METHOD_ERROR))
                return -EIO;

        if (m->reply_cookie != 1)
                return -EIO;

        return 0;
}