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
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  packet ;
struct TYPE_3__ {int sent_nonce; int /*<<< orphan*/  mutex; int /*<<< orphan*/  shared_key; } ;
typedef  int /*<<< orphan*/  Net_Crypto ;
typedef  TYPE_1__ Crypto_Connection ;

/* Variables and functions */
 scalar_t__ MAX_CRYPTO_PACKET_SIZE ; 
 int /*<<< orphan*/  NET_PACKET_CRYPTO_DATA ; 
 scalar_t__ crypto_box_MACBYTES ; 
 int crypto_box_NONCEBYTES ; 
 int encrypt_data_symmetric (int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*,scalar_t__,int /*<<< orphan*/ *) ; 
 TYPE_1__* get_crypto_connection (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  increment_nonce (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int send_packet_to (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int send_data_packet(Net_Crypto *c, int crypt_connection_id, const uint8_t *data, uint16_t length)
{
    if (length == 0 || length + (1 + sizeof(uint16_t) + crypto_box_MACBYTES) > MAX_CRYPTO_PACKET_SIZE)
        return -1;

    Crypto_Connection *conn = get_crypto_connection(c, crypt_connection_id);

    if (conn == 0)
        return -1;

    pthread_mutex_lock(&conn->mutex);
    uint8_t packet[1 + sizeof(uint16_t) + length + crypto_box_MACBYTES];
    packet[0] = NET_PACKET_CRYPTO_DATA;
    memcpy(packet + 1, conn->sent_nonce + (crypto_box_NONCEBYTES - sizeof(uint16_t)), sizeof(uint16_t));
    int len = encrypt_data_symmetric(conn->shared_key, conn->sent_nonce, data, length, packet + 1 + sizeof(uint16_t));

    if (len + 1 + sizeof(uint16_t) != sizeof(packet)) {
        pthread_mutex_unlock(&conn->mutex);
        return -1;
    }

    increment_nonce(conn->sent_nonce);
    pthread_mutex_unlock(&conn->mutex);

    return send_packet_to(c, crypt_connection_id, packet, sizeof(packet));
}