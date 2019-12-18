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
struct TYPE_3__ {int dhcp_send_hostname; int dhcp_use_mtu; int dhcp_use_routes; int dhcp_use_timezone; int /*<<< orphan*/  dhcp_vendor_class_identifier; int /*<<< orphan*/  dhcp_client_identifier; int /*<<< orphan*/  dhcp_anonymize; } ;
typedef  TYPE_1__ Network ;

/* Variables and functions */
 int /*<<< orphan*/  DHCP_CLIENT_ID_MAC ; 
 int /*<<< orphan*/  mfree (int /*<<< orphan*/ ) ; 

void network_apply_anonymize_if_set(Network *network) {
        if (!network->dhcp_anonymize)
                return;
        /* RFC7844 3.7
         SHOULD NOT send the Host Name option */
        network->dhcp_send_hostname = false;
        /* RFC7844 section 3.:
         MAY contain the Client Identifier option
         Section 3.5:
         clients MUST use client identifiers based solely
         on the link-layer address */
        /* NOTE: Using MAC, as it does not reveal extra information,
        * and some servers might not answer if this option is not sent */
        network->dhcp_client_identifier = DHCP_CLIENT_ID_MAC;
        /* RFC 7844 3.10:
         SHOULD NOT use the Vendor Class Identifier option */
        network->dhcp_vendor_class_identifier = mfree(network->dhcp_vendor_class_identifier);
        /* RFC7844 section 3.6.:
         The client intending to protect its privacy SHOULD only request a
         minimal number of options in the PRL and SHOULD also randomly shuffle
         the ordering of option codes in the PRL.  If this random ordering
         cannot be implemented, the client MAY order the option codes in the
         PRL by option code number (lowest to highest).
        */
        /* NOTE: dhcp_use_mtu is false by default,
        * though it was not initiallized to any value in network_load_one.
        * Maybe there should be another var called *send*?
        * (to use the MTU sent by the server but to do not send
        * the option in the PRL). */
        network->dhcp_use_mtu = false;
        /* NOTE: when Anonymize=yes, the PRL route options are sent by default,
         * but this is needed to use them. */
        network->dhcp_use_routes = true;
        /* RFC7844 section 3.6.
        * same comments as previous option */
        network->dhcp_use_timezone = false;
}