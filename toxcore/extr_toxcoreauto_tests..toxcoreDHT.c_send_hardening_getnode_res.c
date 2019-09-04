#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_8__ {int /*<<< orphan*/  ip; } ;
struct TYPE_7__ {int /*<<< orphan*/  net; int /*<<< orphan*/  self_secret_key; int /*<<< orphan*/  self_public_key; } ;
struct TYPE_6__ {TYPE_3__ ip_port; int /*<<< orphan*/  public_key; } ;
typedef  TYPE_1__ Node_format ;
typedef  TYPE_2__ DHT ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_TYPE_GETNODE_RES ; 
 int /*<<< orphan*/  CRYPTO_PACKET_HARDENING ; 
 int MAX_CRYPTO_REQUEST_SIZE ; 
 int create_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int crypto_box_PUBLICKEYBYTES ; 
 int /*<<< orphan*/  ip_isset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int sendpacket (int /*<<< orphan*/ ,TYPE_3__,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int send_hardening_getnode_res(const DHT *dht, const Node_format *sendto, const uint8_t *queried_client_id,
                                      const uint8_t *nodes_data, uint16_t nodes_data_length)
{
    if (!ip_isset(&sendto->ip_port.ip))
        return -1;

    uint8_t packet[MAX_CRYPTO_REQUEST_SIZE];
    uint8_t data[1 + crypto_box_PUBLICKEYBYTES + nodes_data_length];
    data[0] = CHECK_TYPE_GETNODE_RES;
    memcpy(data + 1, queried_client_id, crypto_box_PUBLICKEYBYTES);
    memcpy(data + 1 + crypto_box_PUBLICKEYBYTES, nodes_data, nodes_data_length);
    int len = create_request(dht->self_public_key, dht->self_secret_key, packet, sendto->public_key, data,
                             sizeof(data), CRYPTO_PACKET_HARDENING);

    if (len == -1)
        return -1;

    return sendpacket(dht->net, sendto->ip_port, packet, len);
}