#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
union sockaddr_all {int /*<<< orphan*/  s; } ;
struct socket_server {int /*<<< orphan*/  event_fd; struct socket* slot; } ;
struct socket_sendbuffer {int id; scalar_t__ buffer; } ;
struct socket_lock {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  udp_address; } ;
struct socket {int id; scalar_t__ type; scalar_t__ protocol; int /*<<< orphan*/  fd; scalar_t__ dw_offset; int /*<<< orphan*/  dw_size; void* dw_buffer; TYPE_1__ p; } ;
struct send_object {scalar_t__ sz; int /*<<< orphan*/  (* free_func ) (void*) ;int /*<<< orphan*/  buffer; } ;
struct TYPE_5__ {int id; int /*<<< orphan*/  sz; void* buffer; } ;
struct TYPE_6__ {TYPE_2__ send; } ;
struct request_package {TYPE_3__ u; } ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ socklen_t ;

/* Variables and functions */
 size_t HASH_ID (int) ; 
 scalar_t__ PROTOCOL_TCP ; 
 scalar_t__ SOCKET_TYPE_INVALID ; 
 scalar_t__ can_direct_write (struct socket*,int) ; 
 void* clone_buffer (struct socket_sendbuffer*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  free_buffer (struct socket_server*,struct socket_sendbuffer*) ; 
 int /*<<< orphan*/  inc_sending_ref (struct socket*,int) ; 
 int /*<<< orphan*/  send_object_init_from_sendbuffer (struct socket_server*,struct send_object*,struct socket_sendbuffer*) ; 
 int /*<<< orphan*/  send_request (struct socket_server*,struct request_package*,char,int) ; 
 scalar_t__ sendto (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  socket_lock_init (struct socket*,struct socket_lock*) ; 
 scalar_t__ socket_trylock (struct socket_lock*) ; 
 int /*<<< orphan*/  socket_unlock (struct socket_lock*) ; 
 int /*<<< orphan*/  sp_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct socket*,int) ; 
 int /*<<< orphan*/  stat_write (struct socket_server*,struct socket*,scalar_t__) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stub1 (void*) ; 
 int /*<<< orphan*/  stub2 (void*) ; 
 scalar_t__ udp_socket_address (struct socket*,int /*<<< orphan*/ ,union sockaddr_all*) ; 
 scalar_t__ write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

int 
socket_server_send(struct socket_server *ss, struct socket_sendbuffer *buf) {
	int id = buf->id;
	struct socket * s = &ss->slot[HASH_ID(id)];
	if (s->id != id || s->type == SOCKET_TYPE_INVALID) {
		free_buffer(ss, buf);
		return -1;
	}

	struct socket_lock l;
	socket_lock_init(s, &l);

	if (can_direct_write(s,id) && socket_trylock(&l)) {
		// may be we can send directly, double check
		if (can_direct_write(s,id)) {
			// send directly
			struct send_object so;
			send_object_init_from_sendbuffer(ss, &so, buf);
			ssize_t n;
			if (s->protocol == PROTOCOL_TCP) {
				n = write(s->fd, so.buffer, so.sz);
			} else {
				union sockaddr_all sa;
				socklen_t sasz = udp_socket_address(s, s->p.udp_address, &sa);
				if (sasz == 0) {
					fprintf(stderr, "socket-server : set udp (%d) address first.\n", id);
					socket_unlock(&l);
					so.free_func((void *)buf->buffer);
					return -1;
				}
				n = sendto(s->fd, so.buffer, so.sz, 0, &sa.s, sasz);
			}
			if (n<0) {
				// ignore error, let socket thread try again
				n = 0;
			}
			stat_write(ss,s,n);
			if (n == so.sz) {
				// write done
				socket_unlock(&l);
				so.free_func((void *)buf->buffer);
				return 0;
			}
			// write failed, put buffer into s->dw_* , and let socket thread send it. see send_buffer()
			s->dw_buffer = clone_buffer(buf, &s->dw_size);
			s->dw_offset = n;

			sp_write(ss->event_fd, s->fd, s, true);

			socket_unlock(&l);
			return 0;
		}
		socket_unlock(&l);
	}

	inc_sending_ref(s, id);

	struct request_package request;
	request.u.send.id = id;
	request.u.send.buffer = clone_buffer(buf, &request.u.send.sz);

	send_request(ss, &request, 'D', sizeof(request.u.send));
	return 0;
}