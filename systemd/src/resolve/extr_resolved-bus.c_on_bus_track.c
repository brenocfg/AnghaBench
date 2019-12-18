#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  sd_bus_track ;
typedef  int /*<<< orphan*/  DnssdService ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dnssd_service_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_debug (char*) ; 

__attribute__((used)) static int on_bus_track(sd_bus_track *t, void *userdata) {
        DnssdService *s = userdata;

        assert(t);
        assert(s);

        log_debug("Client of active request vanished, destroying DNS-SD service.");
        dnssd_service_free(s);

        return 0;
}