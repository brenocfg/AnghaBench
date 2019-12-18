#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  usec_t ;
struct TYPE_11__ {int /*<<< orphan*/  cookie; scalar_t__ patch_sender; int /*<<< orphan*/  sender; scalar_t__ sealed; } ;
typedef  TYPE_1__ sd_bus_message ;
typedef  TYPE_1__ sd_bus ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_MESSAGE_COOKIE (TYPE_1__*) ; 
 int /*<<< orphan*/  MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int next_cookie (TYPE_1__*) ; 
 int sd_bus_get_method_call_timeout (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int sd_bus_message_seal (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sd_bus_message_set_sender (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static int bus_seal_message(sd_bus *b, sd_bus_message *m, usec_t timeout) {
        int r;

        assert(b);
        assert(m);

        if (m->sealed) {
                /* If we copy the same message to multiple
                 * destinations, avoid using the same cookie
                 * numbers. */
                b->cookie = MAX(b->cookie, BUS_MESSAGE_COOKIE(m));
                return 0;
        }

        if (timeout == 0) {
                r = sd_bus_get_method_call_timeout(b, &timeout);
                if (r < 0)
                        return r;
        }

        if (!m->sender && b->patch_sender) {
                r = sd_bus_message_set_sender(m, b->patch_sender);
                if (r < 0)
                        return r;
        }

        r = next_cookie(b);
        if (r < 0)
                return r;

        return sd_bus_message_seal(m, b->cookie, timeout);
}