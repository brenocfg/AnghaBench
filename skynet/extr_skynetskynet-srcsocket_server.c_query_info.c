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
union sockaddr_all {int /*<<< orphan*/  s; } ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  u ;
struct socket_info {char* name; int /*<<< orphan*/  wbuffer; int /*<<< orphan*/  wtime; int /*<<< orphan*/  rtime; int /*<<< orphan*/  write; int /*<<< orphan*/  read; scalar_t__ opaque; int /*<<< orphan*/  id; int /*<<< orphan*/  type; } ;
struct TYPE_4__ {int /*<<< orphan*/  wtime; int /*<<< orphan*/  rtime; int /*<<< orphan*/  write; int /*<<< orphan*/  read; } ;
struct TYPE_3__ {int /*<<< orphan*/  udp_address; } ;
struct socket {int type; int /*<<< orphan*/  wb_size; TYPE_2__ stat; scalar_t__ opaque; int /*<<< orphan*/  id; TYPE_1__ p; int /*<<< orphan*/  fd; int /*<<< orphan*/  protocol; } ;
typedef  int socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  PROTOCOL_TCP ; 
 int /*<<< orphan*/  SOCKET_INFO_BIND ; 
 int /*<<< orphan*/  SOCKET_INFO_LISTEN ; 
 int /*<<< orphan*/  SOCKET_INFO_TCP ; 
 int /*<<< orphan*/  SOCKET_INFO_UDP ; 
#define  SOCKET_TYPE_BIND 130 
#define  SOCKET_TYPE_CONNECTED 129 
#define  SOCKET_TYPE_LISTEN 128 
 int /*<<< orphan*/  getname (union sockaddr_all*,char*,int) ; 
 int /*<<< orphan*/  getpeername (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  getsockname (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  udp_socket_address (struct socket*,int /*<<< orphan*/ ,union sockaddr_all*) ; 

__attribute__((used)) static int
query_info(struct socket *s, struct socket_info *si) {
	union sockaddr_all u;
	socklen_t slen = sizeof(u);
	switch (s->type) {
	case SOCKET_TYPE_BIND:
		si->type = SOCKET_INFO_BIND;
		si->name[0] = '\0';
		break;
	case SOCKET_TYPE_LISTEN:
		si->type = SOCKET_INFO_LISTEN;
		if (getsockname(s->fd, &u.s, &slen) == 0) {
			getname(&u, si->name, sizeof(si->name));
		}
		break;
	case SOCKET_TYPE_CONNECTED:
		if (s->protocol == PROTOCOL_TCP) {
			si->type = SOCKET_INFO_TCP;
			if (getpeername(s->fd, &u.s, &slen) == 0) {
				getname(&u, si->name, sizeof(si->name));
			}
		} else {
			si->type = SOCKET_INFO_UDP;
			if (udp_socket_address(s, s->p.udp_address, &u)) {
				getname(&u, si->name, sizeof(si->name));
			}
		}
		break;
	default:
		return 0;
	}
	si->id = s->id;
	si->opaque = (uint64_t)s->opaque;
	si->read = s->stat.read;
	si->write = s->stat.write;
	si->rtime = s->stat.rtime;
	si->wtime = s->stat.wtime;
	si->wbuffer = s->wb_size;

	return 1;
}