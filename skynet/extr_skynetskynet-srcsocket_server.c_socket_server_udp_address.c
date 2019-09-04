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
typedef  int uint8_t ;
struct socket_udp_address {int dummy; } ;
struct socket_server {int dummy; } ;
struct socket_message {scalar_t__ ud; scalar_t__ data; } ;

/* Variables and functions */
#define  PROTOCOL_UDP 129 
#define  PROTOCOL_UDPv6 128 

const struct socket_udp_address *
socket_server_udp_address(struct socket_server *ss, struct socket_message *msg, int *addrsz) {
	uint8_t * address = (uint8_t *)(msg->data + msg->ud);
	int type = address[0];
	switch(type) {
	case PROTOCOL_UDP:
		*addrsz = 1+2+4;
		break;
	case PROTOCOL_UDPv6:
		*addrsz = 1+2+16;
		break;
	default:
		return NULL;
	}
	return (const struct socket_udp_address *)address;
}