#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ protocol; TYPE_2__* manager; } ;
struct TYPE_14__ {scalar_t__ current_feature_level; scalar_t__ dns_udp_fd; int /*<<< orphan*/  sent; TYPE_9__* scope; int /*<<< orphan*/  server; int /*<<< orphan*/  dns_udp_event_source; TYPE_1__* key; } ;
struct TYPE_13__ {int /*<<< orphan*/  event; } ;
struct TYPE_12__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ DnsTransaction ;

/* Variables and functions */
 scalar_t__ DNS_PROTOCOL_DNS ; 
 scalar_t__ DNS_SERVER_FEATURE_LEVEL_IS_TLS (scalar_t__) ; 
 scalar_t__ DNS_SERVER_FEATURE_LEVEL_UDP ; 
 int EAGAIN ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  EPOLLIN ; 
 int /*<<< orphan*/  assert (TYPE_3__*) ; 
 int dns_scope_emit_udp (TYPE_9__*,int,int /*<<< orphan*/ ) ; 
 int dns_scope_socket_udp (TYPE_9__*,int /*<<< orphan*/ ,int) ; 
 int dns_server_adjust_opt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dns_server_dnssec_supported (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dns_transaction_close_connection (TYPE_3__*) ; 
 int dns_transaction_pick_server (TYPE_3__*) ; 
 int /*<<< orphan*/  dns_transaction_reset_answer (TYPE_3__*) ; 
 scalar_t__ dns_type_is_dnssec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  on_dns_packet ; 
 int /*<<< orphan*/  safe_close (int) ; 
 int sd_event_add_io (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  sd_event_source_set_description (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int dns_transaction_emit_udp(DnsTransaction *t) {
        int r;

        assert(t);

        if (t->scope->protocol == DNS_PROTOCOL_DNS) {

                r = dns_transaction_pick_server(t);
                if (r < 0)
                        return r;

                if (t->current_feature_level < DNS_SERVER_FEATURE_LEVEL_UDP || DNS_SERVER_FEATURE_LEVEL_IS_TLS(t->current_feature_level))
                        return -EAGAIN; /* Sorry, can't do UDP, try TCP! */

                if (!dns_server_dnssec_supported(t->server) && dns_type_is_dnssec(t->key->type))
                        return -EOPNOTSUPP;

                if (r > 0 || t->dns_udp_fd < 0) { /* Server changed, or no connection yet. */
                        int fd;

                        dns_transaction_close_connection(t);

                        fd = dns_scope_socket_udp(t->scope, t->server, 53);
                        if (fd < 0)
                                return fd;

                        r = sd_event_add_io(t->scope->manager->event, &t->dns_udp_event_source, fd, EPOLLIN, on_dns_packet, t);
                        if (r < 0) {
                                safe_close(fd);
                                return r;
                        }

                        (void) sd_event_source_set_description(t->dns_udp_event_source, "dns-transaction-udp");
                        t->dns_udp_fd = fd;
                }

                r = dns_server_adjust_opt(t->server, t->sent, t->current_feature_level);
                if (r < 0)
                        return r;
        } else
                dns_transaction_close_connection(t);

        r = dns_scope_emit_udp(t->scope, t->dns_udp_fd, t->sent);
        if (r < 0)
                return r;

        dns_transaction_reset_answer(t);

        return 0;
}