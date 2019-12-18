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
struct TYPE_4__ {scalar_t__ possible_feature_level; scalar_t__ n_failed_tcp; scalar_t__ packet_rrsig_missing; scalar_t__ packet_bad_opt; } ;
typedef  TYPE_1__ DnsServer ;

/* Variables and functions */
 scalar_t__ DNS_SERVER_FEATURE_LEVEL_DO ; 
 scalar_t__ DNS_SERVER_FEATURE_RETRY_ATTEMPTS ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

bool dns_server_dnssec_supported(DnsServer *server) {
        assert(server);

        /* Returns whether the server supports DNSSEC according to what we know about it */

        if (server->possible_feature_level < DNS_SERVER_FEATURE_LEVEL_DO)
                return false;

        if (server->packet_bad_opt)
                return false;

        if (server->packet_rrsig_missing)
                return false;

        /* DNSSEC servers need to support TCP properly (see RFC5966), if they don't, we assume DNSSEC is borked too */
        if (server->n_failed_tcp >= DNS_SERVER_FEATURE_RETRY_ATTEMPTS)
                return false;

        return true;
}