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
typedef  int /*<<< orphan*/  kill_packet ;
struct TYPE_6__ {int /*<<< orphan*/  buffer_end; } ;
struct TYPE_5__ {int /*<<< orphan*/  buffer_start; } ;
struct TYPE_7__ {TYPE_2__ send_array; TYPE_1__ recv_array; } ;
typedef  int /*<<< orphan*/  Net_Crypto ;
typedef  TYPE_3__ Crypto_Connection ;

/* Variables and functions */
 int /*<<< orphan*/  PACKET_ID_KILL ; 
 TYPE_3__* get_crypto_connection (int /*<<< orphan*/ *,int) ; 
 int send_data_packet_helper (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int send_kill_packet(Net_Crypto *c, int crypt_connection_id)
{
    Crypto_Connection *conn = get_crypto_connection(c, crypt_connection_id);

    if (conn == 0)
        return -1;

    uint8_t kill_packet = PACKET_ID_KILL;
    return send_data_packet_helper(c, crypt_connection_id, conn->recv_array.buffer_start, conn->send_array.buffer_end,
                                   &kill_packet, sizeof(kill_packet));
}