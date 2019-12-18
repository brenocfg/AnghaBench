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
 int /*<<< orphan*/  DNS_TYPE_A6 ; 
 int /*<<< orphan*/  DNS_TYPE_MAILA ; 
 int /*<<< orphan*/  DNS_TYPE_MAILB ; 
 int /*<<< orphan*/  DNS_TYPE_MB ; 
 int /*<<< orphan*/  DNS_TYPE_MD ; 
 int /*<<< orphan*/  DNS_TYPE_MF ; 
 int /*<<< orphan*/  DNS_TYPE_MG ; 
 int /*<<< orphan*/  DNS_TYPE_MINFO ; 
 int /*<<< orphan*/  DNS_TYPE_MR ; 
 int /*<<< orphan*/  DNS_TYPE_NULL ; 
 int /*<<< orphan*/  DNS_TYPE_NXT ; 
 int /*<<< orphan*/  DNS_TYPE_WKS ; 
 int IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool dns_type_is_obsolete(uint16_t type) {
        return IN_SET(type,
                      /* Obsoleted by RFC 973 */
                      DNS_TYPE_MD,
                      DNS_TYPE_MF,
                      DNS_TYPE_MAILA,

                      /* Kinda obsoleted by RFC 2505 */
                      DNS_TYPE_MB,
                      DNS_TYPE_MG,
                      DNS_TYPE_MR,
                      DNS_TYPE_MINFO,
                      DNS_TYPE_MAILB,

                      /* RFC1127 kinda obsoleted this by recommending against its use */
                      DNS_TYPE_WKS,

                      /* Declared historical by RFC 6563 */
                      DNS_TYPE_A6,

                      /* Obsoleted by DNSSEC-bis */
                      DNS_TYPE_NXT,

                      /* RFC 1035 removed support for concepts that needed this from RFC 883 */
                      DNS_TYPE_NULL);
}