#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_7__ {int /*<<< orphan*/  buffer_start; } ;
struct TYPE_5__ {int /*<<< orphan*/  buffer_end; } ;
struct TYPE_6__ {TYPE_1__ send_array; TYPE_4__ recv_array; } ;
typedef  int /*<<< orphan*/  Net_Crypto ;
typedef  TYPE_2__ Crypto_Connection ;

/* Variables and functions */
 int MAX_CRYPTO_DATA_SIZE ; 
 int generate_request_packet (int /*<<< orphan*/ *,int,TYPE_4__*) ; 
 TYPE_2__* get_crypto_connection (int /*<<< orphan*/ *,int) ; 
 int send_data_packet_helper (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int send_request_packet(Net_Crypto *c, int crypt_connection_id)
{
    Crypto_Connection *conn = get_crypto_connection(c, crypt_connection_id);

    if (conn == 0)
        return -1;

    uint8_t data[MAX_CRYPTO_DATA_SIZE];
    int len = generate_request_packet(data, sizeof(data), &conn->recv_array);

    if (len == -1)
        return -1;

    return send_data_packet_helper(c, crypt_connection_id, conn->recv_array.buffer_start, conn->send_array.buffer_end, data,
                                   len);
}