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
 int /*<<< orphan*/  DNS_TYPE_DNSKEY ; 
 int /*<<< orphan*/  DNS_TYPE_DS ; 
 int /*<<< orphan*/  DNS_TYPE_NSEC ; 
 int /*<<< orphan*/  DNS_TYPE_NSEC3 ; 
 int /*<<< orphan*/  DNS_TYPE_NSEC3PARAM ; 
 int /*<<< orphan*/  DNS_TYPE_RRSIG ; 
 int IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool dns_type_is_dnssec(uint16_t type) {
        return IN_SET(type,
                      DNS_TYPE_DS,
                      DNS_TYPE_DNSKEY,
                      DNS_TYPE_RRSIG,
                      DNS_TYPE_NSEC,
                      DNS_TYPE_NSEC3,
                      DNS_TYPE_NSEC3PARAM);
}