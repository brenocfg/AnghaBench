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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  DHCPMessage ;

/* Variables and functions */
 int DHCP_FQDN_FLAG_E ; 
 int DHCP_FQDN_FLAG_S ; 
 int /*<<< orphan*/  DHCP_MAX_FQDN_LENGTH ; 
 int /*<<< orphan*/  SD_DHCP_OPTION_FQDN ; 
 int dhcp_option_append (int /*<<< orphan*/ *,size_t,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int dns_name_to_wire_format (char const*,int*,int,int) ; 

__attribute__((used)) static int client_append_fqdn_option(
                DHCPMessage *message,
                size_t optlen,
                size_t *optoffset,
                const char *fqdn) {

        uint8_t buffer[3 + DHCP_MAX_FQDN_LENGTH];
        int r;

        buffer[0] = DHCP_FQDN_FLAG_S | /* Request server to perform A RR DNS updates */
                    DHCP_FQDN_FLAG_E;  /* Canonical wire format */
        buffer[1] = 0;                 /* RCODE1 (deprecated) */
        buffer[2] = 0;                 /* RCODE2 (deprecated) */

        r = dns_name_to_wire_format(fqdn, buffer + 3, sizeof(buffer) - 3, false);
        if (r > 0)
                r = dhcp_option_append(message, optlen, optoffset, 0,
                                       SD_DHCP_OPTION_FQDN, 3 + r, buffer);

        return r;
}