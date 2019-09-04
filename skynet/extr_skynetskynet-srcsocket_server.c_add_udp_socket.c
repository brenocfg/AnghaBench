#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct socket_server {TYPE_1__* slot; } ;
struct TYPE_4__ {int /*<<< orphan*/  udp_address; } ;
struct socket {TYPE_2__ p; int /*<<< orphan*/  type; } ;
struct request_udp {int id; scalar_t__ family; int /*<<< orphan*/  fd; int /*<<< orphan*/  opaque; } ;
struct TYPE_3__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 size_t HASH_ID (int) ; 
 int PROTOCOL_UDP ; 
 int PROTOCOL_UDPv6 ; 
 int /*<<< orphan*/  SOCKET_TYPE_CONNECTED ; 
 int /*<<< orphan*/  SOCKET_TYPE_INVALID ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct socket* new_fd (struct socket_server*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
add_udp_socket(struct socket_server *ss, struct request_udp *udp) {
	int id = udp->id;
	int protocol;
	if (udp->family == AF_INET6) {
		protocol = PROTOCOL_UDPv6;
	} else {
		protocol = PROTOCOL_UDP;
	}
	struct socket *ns = new_fd(ss, id, udp->fd, protocol, udp->opaque, true);
	if (ns == NULL) {
		close(udp->fd);
		ss->slot[HASH_ID(id)].type = SOCKET_TYPE_INVALID;
		return;
	}
	ns->type = SOCKET_TYPE_CONNECTED;
	memset(ns->p.udp_address, 0, sizeof(ns->p.udp_address));
}