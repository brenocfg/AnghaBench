#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  timer_event_source; } ;
typedef  TYPE_1__ sd_ipv4acd ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  ipv4acd_reset (TYPE_1__*) ; 
 TYPE_1__* mfree (TYPE_1__*) ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_ipv4acd_detach_event (TYPE_1__*) ; 

__attribute__((used)) static sd_ipv4acd *ipv4acd_free(sd_ipv4acd *acd) {
        assert(acd);

        acd->timer_event_source = sd_event_source_unref(acd->timer_event_source);

        ipv4acd_reset(acd);
        sd_ipv4acd_detach_event(acd);

        return mfree(acd);
}