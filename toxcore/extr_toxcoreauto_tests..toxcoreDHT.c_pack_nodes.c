#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uint32_t ;
typedef  size_t uint16_t ;
struct TYPE_5__ {scalar_t__ family; int /*<<< orphan*/  ip6; int /*<<< orphan*/  ip4; } ;
struct TYPE_6__ {int /*<<< orphan*/  port; TYPE_1__ ip; } ;
struct TYPE_7__ {int /*<<< orphan*/ * public_key; TYPE_2__ ip_port; } ;
typedef  TYPE_3__ Node_format ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 size_t PACKED_NODE_SIZE_IP4 ; 
 size_t PACKED_NODE_SIZE_IP6 ; 
 int SIZE_IP4 ; 
 int SIZE_IP6 ; 
 scalar_t__ TCP_INET ; 
 scalar_t__ TCP_INET6 ; 
 int /*<<< orphan*/  TOX_AF_INET ; 
 int /*<<< orphan*/  TOX_AF_INET6 ; 
 int /*<<< orphan*/  TOX_TCP_INET ; 
 int /*<<< orphan*/  TOX_TCP_INET6 ; 
 int crypto_box_PUBLICKEYBYTES ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int pack_nodes(uint8_t *data, uint16_t length, const Node_format *nodes, uint16_t number)
{
    uint32_t i, packed_length = 0;

    for (i = 0; i < number; ++i) {
        int ipv6 = -1;
        uint8_t net_family;

        // FIXME use functions to convert endianness
        if (nodes[i].ip_port.ip.family == AF_INET) {
            ipv6 = 0;
            net_family = TOX_AF_INET;
        } else if (nodes[i].ip_port.ip.family == TCP_INET) {
            ipv6 = 0;
            net_family = TOX_TCP_INET;
        } else if (nodes[i].ip_port.ip.family == AF_INET6) {
            ipv6 = 1;
            net_family = TOX_AF_INET6;
        } else if (nodes[i].ip_port.ip.family == TCP_INET6) {
            ipv6 = 1;
            net_family = TOX_TCP_INET6;
        } else {
            return -1;
        }

        if (ipv6 == 0) {
            uint32_t size = PACKED_NODE_SIZE_IP4;

            if (packed_length + size > length)
                return -1;

            data[packed_length] = net_family;
            memcpy(data + packed_length + 1, &nodes[i].ip_port.ip.ip4, SIZE_IP4);
            memcpy(data + packed_length + 1 + SIZE_IP4, &nodes[i].ip_port.port, sizeof(uint16_t));
            memcpy(data + packed_length + 1 + SIZE_IP4 + sizeof(uint16_t), nodes[i].public_key, crypto_box_PUBLICKEYBYTES);
            packed_length += size;
        } else if (ipv6 == 1) {
            uint32_t size = PACKED_NODE_SIZE_IP6;

            if (packed_length + size > length)
                return -1;

            data[packed_length] = net_family;
            memcpy(data + packed_length + 1, &nodes[i].ip_port.ip.ip6, SIZE_IP6);
            memcpy(data + packed_length + 1 + SIZE_IP6, &nodes[i].ip_port.port, sizeof(uint16_t));
            memcpy(data + packed_length + 1 + SIZE_IP6 + sizeof(uint16_t), nodes[i].public_key, crypto_box_PUBLICKEYBYTES);
            packed_length += size;
        } else {
            return -1;
        }
    }

    return packed_length;
}