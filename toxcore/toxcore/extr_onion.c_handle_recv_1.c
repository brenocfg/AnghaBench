#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_9__ {scalar_t__ family; } ;
struct TYPE_11__ {TYPE_1__ ip; } ;
struct TYPE_10__ {int (* recv_1_function ) (int /*<<< orphan*/ ,TYPE_3__,scalar_t__ const*,scalar_t__) ;int /*<<< orphan*/  net; int /*<<< orphan*/  callback_object; int /*<<< orphan*/  secret_symmetric_key; } ;
typedef  TYPE_2__ Onion ;
typedef  TYPE_3__ IP_Port ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 scalar_t__ const NET_PACKET_ANNOUNCE_RESPONSE ; 
 scalar_t__ const NET_PACKET_ONION_DATA_RESPONSE ; 
 scalar_t__ ONION_MAX_PACKET_SIZE ; 
 int RETURN_1 ; 
 int SIZE_IPPORT ; 
 int /*<<< orphan*/  change_symmetric_key (TYPE_2__*) ; 
 int crypto_box_MACBYTES ; 
 int crypto_box_NONCEBYTES ; 
 int decrypt_data_symmetric (int /*<<< orphan*/ ,scalar_t__ const*,scalar_t__ const*,int,scalar_t__*) ; 
 int ipport_unpack (TYPE_3__*,scalar_t__*,int,int) ; 
 scalar_t__ sendpacket (int /*<<< orphan*/ ,TYPE_3__,scalar_t__ const*,scalar_t__) ; 
 int stub1 (int /*<<< orphan*/ ,TYPE_3__,scalar_t__ const*,scalar_t__) ; 

__attribute__((used)) static int handle_recv_1(void *object, IP_Port source, const uint8_t *packet, uint16_t length)
{
    Onion *onion = object;

    if (length > ONION_MAX_PACKET_SIZE)
        return 1;

    if (length <= 1 + RETURN_1)
        return 1;

    if (packet[1 + RETURN_1] != NET_PACKET_ANNOUNCE_RESPONSE &&
            packet[1 + RETURN_1] != NET_PACKET_ONION_DATA_RESPONSE) {
        return 1;
    }

    change_symmetric_key(onion);

    uint8_t plain[SIZE_IPPORT];
    int len = decrypt_data_symmetric(onion->secret_symmetric_key, packet + 1, packet + 1 + crypto_box_NONCEBYTES,
                                     SIZE_IPPORT + crypto_box_MACBYTES, plain);

    if ((uint32_t)len != SIZE_IPPORT)
        return 1;

    IP_Port send_to;

    if (ipport_unpack(&send_to, plain, len, 1) == -1)
        return 1;

    uint16_t data_len = length - (1 + RETURN_1);

    if (onion->recv_1_function && send_to.ip.family != AF_INET && send_to.ip.family != AF_INET6)
        return onion->recv_1_function(onion->callback_object, send_to, packet + (1 + RETURN_1), data_len);

    if ((uint32_t)sendpacket(onion->net, send_to, packet + (1 + RETURN_1), data_len) != data_len)
        return 1;

    return 0;
}