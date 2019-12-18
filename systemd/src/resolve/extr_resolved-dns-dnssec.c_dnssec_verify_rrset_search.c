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
typedef  int /*<<< orphan*/  usec_t ;
typedef  int /*<<< orphan*/  DnssecResult ;
typedef  int /*<<< orphan*/  DnsResourceRecord ;
typedef  int /*<<< orphan*/  DnsResourceKey ;
typedef  int /*<<< orphan*/  DnsAnswer ;

/* Variables and functions */
 int EOPNOTSUPP ; 

int dnssec_verify_rrset_search(
                DnsAnswer *a,
                const DnsResourceKey *key,
                DnsAnswer *validated_dnskeys,
                usec_t realtime,
                DnssecResult *result,
                DnsResourceRecord **ret_rrsig) {

        return -EOPNOTSUPP;
}