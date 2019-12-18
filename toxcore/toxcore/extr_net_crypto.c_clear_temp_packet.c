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
struct TYPE_3__ {scalar_t__ temp_packet_num_sent; scalar_t__ temp_packet_sent_time; scalar_t__ temp_packet_length; scalar_t__ temp_packet; } ;
typedef  int /*<<< orphan*/  Net_Crypto ;
typedef  TYPE_1__ Crypto_Connection ;

/* Variables and functions */
 int /*<<< orphan*/  free (scalar_t__) ; 
 TYPE_1__* get_crypto_connection (int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int clear_temp_packet(const Net_Crypto *c, int crypt_connection_id)
{
    Crypto_Connection *conn = get_crypto_connection(c, crypt_connection_id);

    if (conn == 0)
        return -1;

    if (conn->temp_packet)
        free(conn->temp_packet);

    conn->temp_packet = 0;
    conn->temp_packet_length = 0;
    conn->temp_packet_sent_time = 0;
    conn->temp_packet_num_sent = 0;
    return 0;
}