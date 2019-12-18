#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_10__ {int /*<<< orphan*/  buffer_end; } ;
struct TYPE_9__ {int /*<<< orphan*/  buffer_start; } ;
struct TYPE_12__ {int /*<<< orphan*/  mutex; TYPE_2__ send_array; TYPE_1__ recv_array; } ;
struct TYPE_11__ {int /*<<< orphan*/  connections_mutex; int /*<<< orphan*/  connection_use_counter; } ;
typedef  TYPE_3__ Net_Crypto ;
typedef  TYPE_4__ Crypto_Connection ;

/* Variables and functions */
 scalar_t__ MAX_CRYPTO_DATA_SIZE ; 
 scalar_t__ const PACKET_ID_LOSSY_RANGE_SIZE ; 
 scalar_t__ const PACKET_ID_LOSSY_RANGE_START ; 
 TYPE_4__* get_crypto_connection (TYPE_3__*,int) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int send_data_packet_helper (TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__ const*,scalar_t__) ; 

int send_lossy_cryptpacket(Net_Crypto *c, int crypt_connection_id, const uint8_t *data, uint16_t length)
{
    if (length == 0 || length > MAX_CRYPTO_DATA_SIZE)
        return -1;

    if (data[0] < PACKET_ID_LOSSY_RANGE_START)
        return -1;

    if (data[0] >= (PACKET_ID_LOSSY_RANGE_START + PACKET_ID_LOSSY_RANGE_SIZE))
        return -1;

    pthread_mutex_lock(&c->connections_mutex);
    ++c->connection_use_counter;
    pthread_mutex_unlock(&c->connections_mutex);

    Crypto_Connection *conn = get_crypto_connection(c, crypt_connection_id);

    int ret = -1;

    if (conn) {
        pthread_mutex_lock(&conn->mutex);
        uint32_t buffer_start = conn->recv_array.buffer_start;
        uint32_t buffer_end = conn->send_array.buffer_end;
        pthread_mutex_unlock(&conn->mutex);
        ret = send_data_packet_helper(c, crypt_connection_id, buffer_start, buffer_end, data, length);
    }

    pthread_mutex_lock(&c->connections_mutex);
    --c->connection_use_counter;
    pthread_mutex_unlock(&c->connections_mutex);

    return ret;
}