#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_10__ {scalar_t__ buffer_end; } ;
struct TYPE_7__ {int /*<<< orphan*/  buffer_start; } ;
struct TYPE_9__ {scalar_t__ maximum_speed_reached; TYPE_1__ recv_array; TYPE_4__ send_array; } ;
struct TYPE_8__ {scalar_t__ sent_time; int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ Packet_Data ;
typedef  int /*<<< orphan*/  Net_Crypto ;
typedef  TYPE_3__ Crypto_Connection ;

/* Variables and functions */
 scalar_t__ current_time_monotonic () ; 
 TYPE_3__* get_crypto_connection (int /*<<< orphan*/ *,int) ; 
 int get_data_pointer (TYPE_4__*,TYPE_2__**,scalar_t__) ; 
 scalar_t__ send_data_packet_helper (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int reset_max_speed_reached(Net_Crypto *c, int crypt_connection_id)
{
    Crypto_Connection *conn = get_crypto_connection(c, crypt_connection_id);

    if (conn == 0)
        return -1;

    /* If last packet send failed, try to send packet again.
       If sending it fails we won't be able to send the new packet. */
    if (conn->maximum_speed_reached) {
        Packet_Data *dt = NULL;
        uint32_t packet_num = conn->send_array.buffer_end - 1;
        int ret = get_data_pointer(&conn->send_array, &dt, packet_num);

        uint8_t send_failed = 0;

        if (ret == 1) {
            if (!dt->sent_time) {
                if (send_data_packet_helper(c, crypt_connection_id, conn->recv_array.buffer_start, packet_num, dt->data,
                                            dt->length) != 0) {
                    send_failed = 1;
                } else {
                    dt->sent_time = current_time_monotonic();
                }
            }
        }

        if (!send_failed) {
            conn->maximum_speed_reached = 0;
        } else {
            return -1;
        }
    }

    return 0;
}