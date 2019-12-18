#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  be32_t ;
struct TYPE_4__ {int* data; int length; } ;
struct TYPE_5__ {int /*<<< orphan*/  max_optlen; TYPE_1__ client_id; int /*<<< orphan*/  server_id; int /*<<< orphan*/  requested_ip; int /*<<< orphan*/  lifetime; } ;
typedef  TYPE_2__ DHCPRequest ;
typedef  int /*<<< orphan*/  DHCPPacket ;

/* Variables and functions */
 int ENOMEM ; 
#define  SD_DHCP_OPTION_CLIENT_IDENTIFIER 132 
#define  SD_DHCP_OPTION_IP_ADDRESS_LEASE_TIME 131 
#define  SD_DHCP_OPTION_MAXIMUM_MESSAGE_SIZE 130 
#define  SD_DHCP_OPTION_REQUESTED_IP_ADDRESS 129 
#define  SD_DHCP_OPTION_SERVER_IDENTIFIER 128 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  free (int*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,int) ; 
 int* memdup (void const*,int) ; 
 int unaligned_read_be16 (void const*) ; 
 int /*<<< orphan*/  unaligned_read_be32 (void const*) ; 

__attribute__((used)) static int parse_request(uint8_t code, uint8_t len, const void *option, void *userdata) {
        DHCPRequest *req = userdata;

        assert(req);

        switch(code) {
        case SD_DHCP_OPTION_IP_ADDRESS_LEASE_TIME:
                if (len == 4)
                        req->lifetime = unaligned_read_be32(option);

                break;
        case SD_DHCP_OPTION_REQUESTED_IP_ADDRESS:
                if (len == 4)
                        memcpy(&req->requested_ip, option, sizeof(be32_t));

                break;
        case SD_DHCP_OPTION_SERVER_IDENTIFIER:
                if (len == 4)
                        memcpy(&req->server_id, option, sizeof(be32_t));

                break;
        case SD_DHCP_OPTION_CLIENT_IDENTIFIER:
                if (len >= 2) {
                        uint8_t *data;

                        data = memdup(option, len);
                        if (!data)
                                return -ENOMEM;

                        free(req->client_id.data);
                        req->client_id.data = data;
                        req->client_id.length = len;
                }

                break;
        case SD_DHCP_OPTION_MAXIMUM_MESSAGE_SIZE:

                if (len == 2 && unaligned_read_be16(option) >= sizeof(DHCPPacket))
                        req->max_optlen = unaligned_read_be16(option) - sizeof(DHCPPacket);

                break;
        }

        return 0;
}