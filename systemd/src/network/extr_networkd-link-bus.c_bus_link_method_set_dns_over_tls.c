#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ dns_over_tls_mode; TYPE_1__* manager; } ;
typedef  TYPE_2__ sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
struct TYPE_11__ {int /*<<< orphan*/  polkit_registry; } ;
typedef  TYPE_2__ Link ;
typedef  scalar_t__ DnsOverTlsMode ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int /*<<< orphan*/  SD_BUS_ERROR_INVALID_ARGS ; 
 int /*<<< orphan*/  UID_INVALID ; 
 scalar_t__ _DNS_OVER_TLS_MODE_INVALID ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int bus_verify_polkit_async (TYPE_2__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ dns_over_tls_mode_from_string (char const*) ; 
 scalar_t__ isempty (char const*) ; 
 int /*<<< orphan*/  link_dirty (TYPE_2__*) ; 
 int sd_bus_error_setf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*) ; 
 int sd_bus_message_read (TYPE_2__*,char*,char const**) ; 
 int sd_bus_reply_method_return (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int verify_managed_link (TYPE_2__*,int /*<<< orphan*/ *) ; 

int bus_link_method_set_dns_over_tls(sd_bus_message *message, void *userdata, sd_bus_error *error) {
        Link *l = userdata;
        const char *dns_over_tls;
        DnsOverTlsMode mode;
        int r;

        assert(message);
        assert(l);

        r = verify_managed_link(l, error);
        if (r < 0)
                return r;

        r = sd_bus_message_read(message, "s", &dns_over_tls);
        if (r < 0)
                return r;

        if (isempty(dns_over_tls))
                mode = _DNS_OVER_TLS_MODE_INVALID;
        else {
                mode = dns_over_tls_mode_from_string(dns_over_tls);
                if (mode < 0)
                        return sd_bus_error_setf(error, SD_BUS_ERROR_INVALID_ARGS, "Invalid DNSOverTLS setting: %s", dns_over_tls);
        }

        r = bus_verify_polkit_async(message, CAP_NET_ADMIN,
                                    "org.freedesktop.network1.set-dns-over-tls",
                                    NULL, true, UID_INVALID,
                                    &l->manager->polkit_registry, error);
        if (r < 0)
                return r;
        if (r == 0)
                return 1; /* Polkit will call us back */

        if (l->dns_over_tls_mode != mode) {
                l->dns_over_tls_mode = mode;
                (void) link_dirty(l);
        }

        return sd_bus_reply_method_return(message, NULL);
}