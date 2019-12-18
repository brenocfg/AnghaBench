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
typedef  scalar_t__ uint8_t ;
typedef  size_t uint32_t ;
typedef  size_t uint16_t ;
struct TYPE_5__ {int /*<<< orphan*/  ip6; scalar_t__ family; int /*<<< orphan*/  ip4; } ;
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
 scalar_t__ const TOX_AF_INET ; 
 scalar_t__ const TOX_AF_INET6 ; 
 scalar_t__ const TOX_TCP_INET ; 
 scalar_t__ const TOX_TCP_INET6 ; 
 int crypto_box_PUBLICKEYBYTES ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__ const*,int) ; 

int unpack_nodes(Node_format *nodes, uint16_t max_num_nodes, uint16_t *processed_data_len, const uint8_t *data,
                 uint16_t length, uint8_t tcp_enabled)
{
    uint32_t num = 0, len_processed = 0;

    while (num < max_num_nodes && len_processed < length) {
        int ipv6 = -1;
        uint8_t host_family;

        if (data[len_processed] == TOX_AF_INET) {
            ipv6 = 0;
            host_family = AF_INET;
        } else if (data[len_processed] == TOX_TCP_INET) {
            if (!tcp_enabled)
                return -1;

            ipv6 = 0;
            host_family = TCP_INET;
        } else if (data[len_processed] == TOX_AF_INET6) {
            ipv6 = 1;
            host_family = AF_INET6;
        } else if (data[len_processed] == TOX_TCP_INET6) {
            if (!tcp_enabled)
                return -1;

            ipv6 = 1;
            host_family = TCP_INET6;
        } else {
            return -1;
        }

        if (ipv6 == 0) {
            uint32_t size = PACKED_NODE_SIZE_IP4;

            if (len_processed + size > length)
                return -1;

            nodes[num].ip_port.ip.family = host_family;
            memcpy(&nodes[num].ip_port.ip.ip4, data + len_processed + 1, SIZE_IP4);
            memcpy(&nodes[num].ip_port.port, data + len_processed + 1 + SIZE_IP4, sizeof(uint16_t));
            memcpy(nodes[num].public_key, data + len_processed + 1 + SIZE_IP4 + sizeof(uint16_t), crypto_box_PUBLICKEYBYTES);
            len_processed += size;
            ++num;
        } else if (ipv6 == 1) {
            uint32_t size = PACKED_NODE_SIZE_IP6;

            if (len_processed + size > length)
                return -1;

            nodes[num].ip_port.ip.family = host_family;
            memcpy(&nodes[num].ip_port.ip.ip6, data + len_processed + 1, SIZE_IP6);
            memcpy(&nodes[num].ip_port.port, data + len_processed + 1 + SIZE_IP6, sizeof(uint16_t));
            memcpy(nodes[num].public_key, data + len_processed + 1 + SIZE_IP6 + sizeof(uint16_t), crypto_box_PUBLICKEYBYTES);
            len_processed += size;
            ++num;
        } else {
            return -1;
        }
    }

    if (processed_data_len)
        *processed_data_len = len_processed;

    return num;
}