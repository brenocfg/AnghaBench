#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  data ;
typedef  int /*<<< orphan*/  TCP_Secure_Connection ;

/* Variables and functions */
 int /*<<< orphan*/  TCP_PACKET_ROUTING_RESPONSE ; 
 int /*<<< orphan*/  crypto_box_PUBLICKEYBYTES ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int write_packet_TCP_secure_connection (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int send_routing_response(TCP_Secure_Connection *con, uint8_t rpid, const uint8_t *public_key)
{
    uint8_t data[1 + 1 + crypto_box_PUBLICKEYBYTES];
    data[0] = TCP_PACKET_ROUTING_RESPONSE;
    data[1] = rpid;
    memcpy(data + 2, public_key, crypto_box_PUBLICKEYBYTES);

    return write_packet_TCP_secure_connection(con, data, sizeof(data), 1);
}