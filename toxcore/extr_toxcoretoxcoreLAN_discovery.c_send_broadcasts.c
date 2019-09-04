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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  Networking_Core ;

/* Variables and functions */
 int broadcast_count ; 
 int /*<<< orphan*/ * broadcast_ip_port ; 
 int /*<<< orphan*/  fetch_broadcast_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sendpacket (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t send_broadcasts(Networking_Core *net, uint16_t port, const uint8_t *data, uint16_t length)
{
    /* fetch only once? on every packet? every X seconds?
     * old: every packet, new: once */
    if (broadcast_count < 0)
        fetch_broadcast_info(port);

    if (!broadcast_count)
        return 0;

    int i;

    for (i = 0; i < broadcast_count; i++)
        sendpacket(net, broadcast_ip_port[i], data, length);

    return 1;
}