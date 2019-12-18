#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  usec_t ;
typedef  int /*<<< orphan*/  sd_event_source ;
struct TYPE_3__ {int /*<<< orphan*/  announce_event_source; } ;
typedef  TYPE_1__ DnsScope ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dns_scope_announce (TYPE_1__*,int) ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int on_announcement_timeout(sd_event_source *s, usec_t usec, void *userdata) {
        DnsScope *scope = userdata;

        assert(s);

        scope->announce_event_source = sd_event_source_unref(scope->announce_event_source);

        (void) dns_scope_announce(scope, false);
        return 0;
}