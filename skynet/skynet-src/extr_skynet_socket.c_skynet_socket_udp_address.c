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
struct socket_message {int /*<<< orphan*/  data; int /*<<< orphan*/  ud; scalar_t__ opaque; int /*<<< orphan*/  id; } ;
struct skynet_socket_message {scalar_t__ type; int /*<<< orphan*/  buffer; int /*<<< orphan*/  ud; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 scalar_t__ SKYNET_SOCKET_TYPE_UDP ; 
 int /*<<< orphan*/  SOCKET_SERVER ; 
 scalar_t__ socket_server_udp_address (int /*<<< orphan*/ ,struct socket_message*,int*) ; 

const char *
skynet_socket_udp_address(struct skynet_socket_message *msg, int *addrsz) {
	if (msg->type != SKYNET_SOCKET_TYPE_UDP) {
		return NULL;
	}
	struct socket_message sm;
	sm.id = msg->id;
	sm.opaque = 0;
	sm.ud = msg->ud;
	sm.data = msg->buffer;
	return (const char *)socket_server_udp_address(SOCKET_SERVER, &sm, addrsz);
}