#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {scalar_t__ buffer_end; scalar_t__ buffer_start; } ;
struct TYPE_5__ {TYPE_1__ send_array; } ;
typedef  int /*<<< orphan*/  Net_Crypto ;
typedef  TYPE_2__ Crypto_Connection ;

/* Variables and functions */
 TYPE_2__* get_crypto_connection (int /*<<< orphan*/ *,int) ; 

int cryptpacket_received(Net_Crypto *c, int crypt_connection_id, uint32_t packet_number)
{
    Crypto_Connection *conn = get_crypto_connection(c, crypt_connection_id);

    if (conn == 0)
        return -1;

    uint32_t num = conn->send_array.buffer_end - conn->send_array.buffer_start;
    uint32_t num1 = packet_number - conn->send_array.buffer_start;

    if (num < num1) {
        return 0;
    } else {
        return -1;
    }
}