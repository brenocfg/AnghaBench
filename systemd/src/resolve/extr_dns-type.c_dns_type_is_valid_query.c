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
 int /*<<< orphan*/  DNS_TYPE_OPT ; 
 int /*<<< orphan*/  DNS_TYPE_RRSIG ; 
 int /*<<< orphan*/  DNS_TYPE_TKEY ; 
 int /*<<< orphan*/  DNS_TYPE_TSIG ; 
 int /*<<< orphan*/  IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool dns_type_is_valid_query(uint16_t type) {

        /* The types valid as questions in packets */

        return !IN_SET(type,
                       0,
                       DNS_TYPE_OPT,
                       DNS_TYPE_TSIG,
                       DNS_TYPE_TKEY,

                       /* RRSIG are technically valid as questions, but we refuse doing explicit queries for them, as
                        * they aren't really payload, but signatures for payload, and cannot be validated on their
                        * own. After all they are the signatures, and have no signatures of their own validating
                        * them. */
                       DNS_TYPE_RRSIG);
}