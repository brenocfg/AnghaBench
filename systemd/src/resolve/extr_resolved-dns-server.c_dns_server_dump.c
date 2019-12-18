#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ type; char* ifname; int received_udp_packet_max; int n_failed_udp; char* n_failed_tcp; int /*<<< orphan*/  packet_bad_opt; int /*<<< orphan*/  packet_truncated; int /*<<< orphan*/  packet_rrsig_missing; int /*<<< orphan*/  possible_feature_level; int /*<<< orphan*/  verified_feature_level; struct TYPE_7__* link; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__ DnsServer ;

/* Variables and functions */
 scalar_t__ DNS_SERVER_LINK ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  dns_server_dnssec_supported (TYPE_1__*) ; 
 int /*<<< orphan*/  dns_server_feature_level_to_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dns_server_get_dnssec_mode (TYPE_1__*) ; 
 char* dns_server_string (TYPE_1__*) ; 
 char* dns_server_type_to_string (scalar_t__) ; 
 int /*<<< orphan*/  dnssec_mode_to_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int,int,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stdout ; 
 char* strna (int /*<<< orphan*/ ) ; 
 char* yes_no (int /*<<< orphan*/ ) ; 

void dns_server_dump(DnsServer *s, FILE *f) {
        assert(s);

        if (!f)
                f = stdout;

        fputs("[Server ", f);
        fputs(dns_server_string(s), f);
        fputs(" type=", f);
        fputs(dns_server_type_to_string(s->type), f);

        if (s->type == DNS_SERVER_LINK) {
                assert(s->link);

                fputs(" interface=", f);
                fputs(s->link->ifname, f);
        }

        fputs("]\n", f);

        fputs("\tVerified feature level: ", f);
        fputs(strna(dns_server_feature_level_to_string(s->verified_feature_level)), f);
        fputc('\n', f);

        fputs("\tPossible feature level: ", f);
        fputs(strna(dns_server_feature_level_to_string(s->possible_feature_level)), f);
        fputc('\n', f);

        fputs("\tDNSSEC Mode: ", f);
        fputs(strna(dnssec_mode_to_string(dns_server_get_dnssec_mode(s))), f);
        fputc('\n', f);

        fputs("\tCan do DNSSEC: ", f);
        fputs(yes_no(dns_server_dnssec_supported(s)), f);
        fputc('\n', f);

        fprintf(f,
                "\tMaximum UDP packet size received: %zu\n"
                "\tFailed UDP attempts: %u\n"
                "\tFailed TCP attempts: %u\n"
                "\tSeen truncated packet: %s\n"
                "\tSeen OPT RR getting lost: %s\n"
                "\tSeen RRSIG RR missing: %s\n",
                s->received_udp_packet_max,
                s->n_failed_udp,
                s->n_failed_tcp,
                yes_no(s->packet_truncated),
                yes_no(s->packet_bad_opt),
                yes_no(s->packet_rrsig_missing));
}