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
 int /*<<< orphan*/  DNS_TYPE_DNAME ; 
 int /*<<< orphan*/  DNS_TYPE_NSEC3 ; 
 int /*<<< orphan*/  DNS_TYPE_SOA ; 
 int /*<<< orphan*/  IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dns_type_is_pseudo (int /*<<< orphan*/ ) ; 

bool dns_type_may_wildcard(uint16_t type) {

        /* The following records may not be expanded from wildcard RRsets */

        if (dns_type_is_pseudo(type))
                return false;

        return !IN_SET(type,
                       DNS_TYPE_NSEC3,
                       DNS_TYPE_SOA,

                       /* Prohibited by https://tools.ietf.org/html/rfc4592#section-4.4 */
                       DNS_TYPE_DNAME);
}