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
struct TYPE_3__ {int /*<<< orphan*/ * n_dnssec_verdict; } ;
typedef  TYPE_1__ Manager ;
typedef  size_t DnssecVerdict ;
typedef  int /*<<< orphan*/  DnsResourceKey ;

/* Variables and functions */
 scalar_t__ DEBUG_LOGGING ; 
 int DNS_RESOURCE_KEY_STRING_MAX ; 
 size_t _DNSSEC_VERDICT_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dns_resource_key_to_string (int /*<<< orphan*/  const*,char*,int) ; 
 int /*<<< orphan*/  dnssec_verdict_to_string (size_t) ; 
 int /*<<< orphan*/  log_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void manager_dnssec_verdict(Manager *m, DnssecVerdict verdict, const DnsResourceKey *key) {

        assert(verdict >= 0);
        assert(verdict < _DNSSEC_VERDICT_MAX);

        if (DEBUG_LOGGING) {
                char s[DNS_RESOURCE_KEY_STRING_MAX];

                log_debug("Found verdict for lookup %s: %s",
                          dns_resource_key_to_string(key, s, sizeof s),
                          dnssec_verdict_to_string(verdict));
        }

        m->n_dnssec_verdict[verdict]++;
}