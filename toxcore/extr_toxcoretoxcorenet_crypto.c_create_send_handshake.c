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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  handshake_packet ;
struct TYPE_3__ {int /*<<< orphan*/  public_key; int /*<<< orphan*/  sessionpublic_key; int /*<<< orphan*/  sent_nonce; } ;
typedef  int /*<<< orphan*/  Net_Crypto ;
typedef  TYPE_1__ Crypto_Connection ;

/* Variables and functions */
 int HANDSHAKE_PACKET_LENGTH ; 
 int create_crypto_handshake (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 TYPE_1__* get_crypto_connection (int /*<<< orphan*/ *,int) ; 
 scalar_t__ new_temp_packet (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  send_temp_packet (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int create_send_handshake(Net_Crypto *c, int crypt_connection_id, const uint8_t *cookie,
                                 const uint8_t *dht_public_key)
{
    Crypto_Connection *conn = get_crypto_connection(c, crypt_connection_id);

    if (conn == 0)
        return -1;

    uint8_t handshake_packet[HANDSHAKE_PACKET_LENGTH];

    if (create_crypto_handshake(c, handshake_packet, cookie, conn->sent_nonce, conn->sessionpublic_key,
                                conn->public_key, dht_public_key) != sizeof(handshake_packet))
        return -1;

    if (new_temp_packet(c, crypt_connection_id, handshake_packet, sizeof(handshake_packet)) != 0)
        return -1;

    send_temp_packet(c, crypt_connection_id);
    return 0;
}