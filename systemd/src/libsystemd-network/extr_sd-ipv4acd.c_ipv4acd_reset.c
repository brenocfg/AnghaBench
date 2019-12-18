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
struct TYPE_5__ {int /*<<< orphan*/  fd; int /*<<< orphan*/  receive_message_event_source; int /*<<< orphan*/  timer_event_source; } ;
typedef  TYPE_1__ sd_ipv4acd ;

/* Variables and functions */
 int /*<<< orphan*/  IPV4ACD_STATE_INIT ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  event_source_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipv4acd_set_state (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  safe_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipv4acd_reset(sd_ipv4acd *acd) {
        assert(acd);

        (void) event_source_disable(acd->timer_event_source);
        acd->receive_message_event_source = sd_event_source_unref(acd->receive_message_event_source);

        acd->fd = safe_close(acd->fd);

        ipv4acd_set_state(acd, IPV4ACD_STATE_INIT, true);
}