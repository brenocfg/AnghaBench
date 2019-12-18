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
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  DNS_TYPE_CAA ; 
 int /*<<< orphan*/  DNS_TYPE_CDNSKEY ; 
 int /*<<< orphan*/  DNS_TYPE_CERT ; 
 int /*<<< orphan*/  DNS_TYPE_DNSKEY ; 
 int /*<<< orphan*/  DNS_TYPE_DS ; 
 int /*<<< orphan*/  DNS_TYPE_IPSECKEY ; 
 int /*<<< orphan*/  DNS_TYPE_OPENPGPKEY ; 
 int /*<<< orphan*/  DNS_TYPE_SSHFP ; 
 int /*<<< orphan*/  DNS_TYPE_TLSA ; 
 int IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool dns_type_needs_authentication(uint16_t type) {

        /* Returns true for all (non-obsolete) RR types where records are not useful if they aren't
         * authenticated. I.e. everything that contains crypto keys. */

        return IN_SET(type,
                      DNS_TYPE_CERT,
                      DNS_TYPE_SSHFP,
                      DNS_TYPE_IPSECKEY,
                      DNS_TYPE_DS,
                      DNS_TYPE_DNSKEY,
                      DNS_TYPE_TLSA,
                      DNS_TYPE_CDNSKEY,
                      DNS_TYPE_OPENPGPKEY,
                      DNS_TYPE_CAA);
}