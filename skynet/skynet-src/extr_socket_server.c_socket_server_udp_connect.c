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
typedef  union sockaddr_all {int dummy; } sockaddr_all ;
struct socket_server {struct socket* slot; } ;
struct socket_lock {int dummy; } ;
struct socket {int id; scalar_t__ type; int /*<<< orphan*/  udpconnecting; } ;
struct TYPE_3__ {int id; int /*<<< orphan*/  address; } ;
struct TYPE_4__ {TYPE_1__ set_udp; } ;
struct request_package {TYPE_2__ u; } ;
struct addrinfo {scalar_t__ ai_family; scalar_t__ ai_addr; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; } ;
typedef  int /*<<< orphan*/  ai_hints ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 scalar_t__ AF_UNSPEC ; 
 int /*<<< orphan*/  ATOM_INC (int /*<<< orphan*/ *) ; 
 size_t HASH_ID (int) ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int PROTOCOL_UDP ; 
 int PROTOCOL_UDPv6 ; 
 scalar_t__ SOCKET_TYPE_INVALID ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int gen_udp_address (int,union sockaddr_all*,int /*<<< orphan*/ ) ; 
 int getaddrinfo (char const*,char*,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  send_request (struct socket_server*,struct request_package*,char,int) ; 
 int /*<<< orphan*/  socket_lock (struct socket_lock*) ; 
 int /*<<< orphan*/  socket_lock_init (struct socket*,struct socket_lock*) ; 
 int /*<<< orphan*/  socket_unlock (struct socket_lock*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

int
socket_server_udp_connect(struct socket_server *ss, int id, const char * addr, int port) {
	struct socket * s = &ss->slot[HASH_ID(id)];
	if (s->id != id || s->type == SOCKET_TYPE_INVALID) {
		return -1;
	}
	struct socket_lock l;
	socket_lock_init(s, &l);
	socket_lock(&l);
	if (s->id != id || s->type == SOCKET_TYPE_INVALID) {
		socket_unlock(&l);
		return -1;
	}
	ATOM_INC(&s->udpconnecting);
	socket_unlock(&l);

	int status;
	struct addrinfo ai_hints;
	struct addrinfo *ai_list = NULL;
	char portstr[16];
	sprintf(portstr, "%d", port);
	memset( &ai_hints, 0, sizeof( ai_hints ) );
	ai_hints.ai_family = AF_UNSPEC;
	ai_hints.ai_socktype = SOCK_DGRAM;
	ai_hints.ai_protocol = IPPROTO_UDP;

	status = getaddrinfo(addr, portstr, &ai_hints, &ai_list );
	if ( status != 0 ) {
		return -1;
	}
	struct request_package request;
	request.u.set_udp.id = id;
	int protocol;

	if (ai_list->ai_family == AF_INET) {
		protocol = PROTOCOL_UDP;
	} else if (ai_list->ai_family == AF_INET6) {
		protocol = PROTOCOL_UDPv6;
	} else {
		freeaddrinfo( ai_list );
		return -1;
	}

	int addrsz = gen_udp_address(protocol, (union sockaddr_all *)ai_list->ai_addr, request.u.set_udp.address);

	freeaddrinfo( ai_list );

	send_request(ss, &request, 'C', sizeof(request.u.set_udp) - sizeof(request.u.set_udp.address) +addrsz);

	return 0;
}