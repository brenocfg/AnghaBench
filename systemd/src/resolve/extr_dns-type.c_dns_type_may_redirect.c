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
 int /*<<< orphan*/  DNS_TYPE_CNAME ; 
 int /*<<< orphan*/  DNS_TYPE_DNAME ; 
 int /*<<< orphan*/  DNS_TYPE_KEY ; 
 int /*<<< orphan*/  DNS_TYPE_NSEC ; 
 int /*<<< orphan*/  DNS_TYPE_NSEC3 ; 
 int /*<<< orphan*/  DNS_TYPE_NXT ; 
 int /*<<< orphan*/  DNS_TYPE_RRSIG ; 
 int /*<<< orphan*/  DNS_TYPE_SIG ; 
 int /*<<< orphan*/  IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dns_type_is_pseudo (int /*<<< orphan*/ ) ; 

bool dns_type_may_redirect(uint16_t type) {
        /* The following record types should never be redirected using
         * CNAME/DNAME RRs. See
         * <https://tools.ietf.org/html/rfc4035#section-2.5>. */

        if (dns_type_is_pseudo(type))
                return false;

        return !IN_SET(type,
                       DNS_TYPE_CNAME,
                       DNS_TYPE_DNAME,
                       DNS_TYPE_NSEC3,
                       DNS_TYPE_NSEC,
                       DNS_TYPE_RRSIG,
                       DNS_TYPE_NXT,
                       DNS_TYPE_SIG,
                       DNS_TYPE_KEY);
}