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
struct socket_server {struct socket* slot; } ;
struct socket {int id; scalar_t__ type; } ;
struct TYPE_3__ {int id; int sz; char* buffer; } ;
struct TYPE_4__ {TYPE_1__ send; } ;
struct request_package {TYPE_2__ u; } ;

/* Variables and functions */
 size_t HASH_ID (int) ; 
 scalar_t__ SOCKET_TYPE_INVALID ; 
 int /*<<< orphan*/  free_buffer (struct socket_server*,void const*,int) ; 
 int /*<<< orphan*/  inc_sending_ref (struct socket*,int) ; 
 int /*<<< orphan*/  send_request (struct socket_server*,struct request_package*,char,int) ; 

int 
socket_server_send_lowpriority(struct socket_server *ss, int id, const void * buffer, int sz) {
	struct socket * s = &ss->slot[HASH_ID(id)];
	if (s->id != id || s->type == SOCKET_TYPE_INVALID) {
		free_buffer(ss, buffer, sz);
		return -1;
	}

	inc_sending_ref(s, id);

	struct request_package request;
	request.u.send.id = id;
	request.u.send.sz = sz;
	request.u.send.buffer = (char *)buffer;

	send_request(ss, &request, 'P', sizeof(request.u.send));
	return 0;
}