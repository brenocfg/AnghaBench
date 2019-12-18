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
struct siphash {int dummy; } ;
struct TYPE_4__ {int family; int from; int from_prefixlen; int to; int to_prefixlen; int tos; int fwmark; int fwmask; int priority; int table; int protocol; int sport; int dport; int* iif; int* oif; int /*<<< orphan*/  invert_rule; } ;
typedef  TYPE_1__ RoutingPolicyRule ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int FAMILY_ADDRESS_SIZE (int) ; 
 int /*<<< orphan*/  assert (TYPE_1__ const*) ; 
 int /*<<< orphan*/  siphash24_compress (int*,int,struct siphash*) ; 
 int /*<<< orphan*/  siphash24_compress_boolean (int /*<<< orphan*/ ,struct siphash*) ; 
 int strlen (int*) ; 

__attribute__((used)) static void routing_policy_rule_hash_func(const RoutingPolicyRule *rule, struct siphash *state) {
        assert(rule);

        siphash24_compress(&rule->family, sizeof(rule->family), state);

        switch (rule->family) {
        case AF_INET:
        case AF_INET6:
                siphash24_compress(&rule->from, FAMILY_ADDRESS_SIZE(rule->family), state);
                siphash24_compress(&rule->from_prefixlen, sizeof(rule->from_prefixlen), state);

                siphash24_compress(&rule->to, FAMILY_ADDRESS_SIZE(rule->family), state);
                siphash24_compress(&rule->to_prefixlen, sizeof(rule->to_prefixlen), state);

                siphash24_compress_boolean(rule->invert_rule, state);

                siphash24_compress(&rule->tos, sizeof(rule->tos), state);
                siphash24_compress(&rule->fwmark, sizeof(rule->fwmark), state);
                siphash24_compress(&rule->fwmask, sizeof(rule->fwmask), state);
                siphash24_compress(&rule->priority, sizeof(rule->priority), state);
                siphash24_compress(&rule->table, sizeof(rule->table), state);

                siphash24_compress(&rule->protocol, sizeof(rule->protocol), state);
                siphash24_compress(&rule->sport, sizeof(rule->sport), state);
                siphash24_compress(&rule->dport, sizeof(rule->dport), state);

                if (rule->iif)
                        siphash24_compress(rule->iif, strlen(rule->iif), state);

                if (rule->oif)
                        siphash24_compress(rule->oif, strlen(rule->oif), state);

                break;
        default:
                /* treat any other address family as AF_UNSPEC */
                break;
        }
}