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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  plain ;
struct TYPE_3__ {int /*<<< orphan*/  net; int /*<<< orphan*/  secret_symmetric_key; } ;
typedef  TYPE_1__ Onion ;
typedef  int /*<<< orphan*/  IP_Port ;

/* Variables and functions */
 scalar_t__ const NET_PACKET_ANNOUNCE_RESPONSE ; 
 scalar_t__ const NET_PACKET_ONION_DATA_RESPONSE ; 
 scalar_t__ NET_PACKET_ONION_RECV_1 ; 
 int ONION_MAX_PACKET_SIZE ; 
 int RETURN_1 ; 
 int RETURN_2 ; 
 int SIZE_IPPORT ; 
 int /*<<< orphan*/  change_symmetric_key (TYPE_1__*) ; 
 int crypto_box_MACBYTES ; 
 int crypto_box_NONCEBYTES ; 
 int decrypt_data_symmetric (int /*<<< orphan*/ ,scalar_t__ const*,scalar_t__ const*,int,scalar_t__*) ; 
 int ipport_unpack (int /*<<< orphan*/ *,scalar_t__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__ const*,int) ; 
 scalar_t__ sendpacket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 

__attribute__((used)) static int handle_recv_2(void *object, IP_Port source, const uint8_t *packet, uint16_t length)
{
    Onion *onion = object;

    if (length > ONION_MAX_PACKET_SIZE)
        return 1;

    if (length <= 1 + RETURN_2)
        return 1;

    if (packet[1 + RETURN_2] != NET_PACKET_ANNOUNCE_RESPONSE &&
            packet[1 + RETURN_2] != NET_PACKET_ONION_DATA_RESPONSE) {
        return 1;
    }

    change_symmetric_key(onion);

    uint8_t plain[SIZE_IPPORT + RETURN_1];
    int len = decrypt_data_symmetric(onion->secret_symmetric_key, packet + 1, packet + 1 + crypto_box_NONCEBYTES,
                                     SIZE_IPPORT + RETURN_1 + crypto_box_MACBYTES, plain);

    if ((uint32_t)len != sizeof(plain))
        return 1;

    IP_Port send_to;

    if (ipport_unpack(&send_to, plain, len, 0) == -1)
        return 1;

    uint8_t data[ONION_MAX_PACKET_SIZE];
    data[0] = NET_PACKET_ONION_RECV_1;
    memcpy(data + 1, plain + SIZE_IPPORT, RETURN_1);
    memcpy(data + 1 + RETURN_1, packet + 1 + RETURN_2, length - (1 + RETURN_2));
    uint16_t data_len = 1 + RETURN_1 + (length - (1 + RETURN_2));

    if ((uint32_t)sendpacket(onion->net, send_to, data, data_len) != data_len)
        return 1;

    return 0;
}