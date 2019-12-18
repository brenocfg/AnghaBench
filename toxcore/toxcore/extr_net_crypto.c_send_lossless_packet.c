#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int int64_t ;
struct TYPE_7__ {int /*<<< orphan*/  buffer_start; } ;
struct TYPE_9__ {int maximum_speed_reached; int /*<<< orphan*/  send_array; TYPE_1__ recv_array; int /*<<< orphan*/  mutex; } ;
struct TYPE_8__ {scalar_t__ sent_time; int /*<<< orphan*/  data; int /*<<< orphan*/  length; } ;
typedef  TYPE_2__ Packet_Data ;
typedef  int /*<<< orphan*/  Net_Crypto ;
typedef  TYPE_3__ Crypto_Connection ;

/* Variables and functions */
 int /*<<< orphan*/  LOGGER_ERROR (char*) ; 
 int /*<<< orphan*/  MAX_CRYPTO_DATA_SIZE ; 
 int add_data_end_of_buffer (int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ current_time_monotonic () ; 
 TYPE_3__* get_crypto_connection (int /*<<< orphan*/ *,int) ; 
 int get_data_pointer (int /*<<< orphan*/ *,TYPE_2__**,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_max_speed_reached (int /*<<< orphan*/ *,int) ; 
 scalar_t__ send_data_packet_helper (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,scalar_t__ const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int64_t send_lossless_packet(Net_Crypto *c, int crypt_connection_id, const uint8_t *data, uint16_t length,
                                    uint8_t congestion_control)
{
    if (length == 0 || length > MAX_CRYPTO_DATA_SIZE)
        return -1;

    Crypto_Connection *conn = get_crypto_connection(c, crypt_connection_id);

    if (conn == 0)
        return -1;

    /* If last packet send failed, try to send packet again.
       If sending it fails we won't be able to send the new packet. */
    reset_max_speed_reached(c, crypt_connection_id);

    if (conn->maximum_speed_reached && congestion_control) {
        return -1;
    }

    Packet_Data dt;
    dt.sent_time = 0;
    dt.length = length;
    memcpy(dt.data, data, length);
    pthread_mutex_lock(&conn->mutex);
    int64_t packet_num = add_data_end_of_buffer(&conn->send_array, &dt);
    pthread_mutex_unlock(&conn->mutex);

    if (packet_num == -1)
        return -1;

    if (!congestion_control && conn->maximum_speed_reached) {
        return packet_num;
    }

    if (send_data_packet_helper(c, crypt_connection_id, conn->recv_array.buffer_start, packet_num, data, length) == 0) {
        Packet_Data *dt1 = NULL;

        if (get_data_pointer(&conn->send_array, &dt1, packet_num) == 1)
            dt1->sent_time = current_time_monotonic();
    } else {
        conn->maximum_speed_reached = 1;
        LOGGER_ERROR("send_data_packet failed\n");
    }

    return packet_num;
}