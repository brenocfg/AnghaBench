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
 int /*<<< orphan*/  DNS_TYPE_ANY ; 
 int /*<<< orphan*/  DNS_TYPE_AXFR ; 
 int /*<<< orphan*/  DNS_TYPE_IXFR ; 
 int /*<<< orphan*/  DNS_TYPE_OPT ; 
 int /*<<< orphan*/  DNS_TYPE_TKEY ; 
 int /*<<< orphan*/  DNS_TYPE_TSIG ; 
 int IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool dns_type_is_pseudo(uint16_t type) {

        /* Checks whether the specified type is a "pseudo-type". What
         * a "pseudo-type" precisely is, is defined only very weakly,
         * but apparently entails all RR types that are not actually
         * stored as RRs on the server and should hence also not be
         * cached. We use this list primarily to validate NSEC type
         * bitfields, and to verify what to cache. */

        return IN_SET(type,
                      0, /* A Pseudo RR type, according to RFC 2931 */
                      DNS_TYPE_ANY,
                      DNS_TYPE_AXFR,
                      DNS_TYPE_IXFR,
                      DNS_TYPE_OPT,
                      DNS_TYPE_TSIG,
                      DNS_TYPE_TKEY
        );
}