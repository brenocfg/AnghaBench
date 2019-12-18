#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_5__ {int /*<<< orphan*/  family; } ;
struct TYPE_6__ {TYPE_1__ ip; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ IP_Port ;

/* Variables and functions */
 scalar_t__ const NET_PACKET_ANNOUNCE_RESPONSE ; 
 scalar_t__ const NET_PACKET_ONION_DATA_RESPONSE ; 
 int /*<<< orphan*/  TCP_FAMILY ; 
 int handle_announce_response (void*,TYPE_2__,scalar_t__ const*,int /*<<< orphan*/ ) ; 
 int handle_data_response (void*,TYPE_2__,scalar_t__ const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_tcp_onion(void *object, const uint8_t *data, uint16_t length)
{
    if (length == 0)
        return 1;

    IP_Port ip_port = {0};
    ip_port.ip.family = TCP_FAMILY;

    if (data[0] == NET_PACKET_ANNOUNCE_RESPONSE) {
        return handle_announce_response(object, ip_port, data, length);
    } else if (data[0] == NET_PACKET_ONION_DATA_RESPONSE) {
        return handle_data_response(object, ip_port, data, length);
    }

    return 1;
}