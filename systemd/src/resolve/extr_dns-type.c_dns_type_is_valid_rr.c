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
 int /*<<< orphan*/  IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool dns_type_is_valid_rr(uint16_t type) {

        /* The types valid as RR in packets (but not necessarily
         * stored on servers). */

        return !IN_SET(type,
                       DNS_TYPE_ANY,
                       DNS_TYPE_AXFR,
                       DNS_TYPE_IXFR);
}