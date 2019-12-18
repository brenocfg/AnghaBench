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
struct socket_server {int dummy; } ;
struct TYPE_3__ {uintptr_t opaque; int id; int fd; } ;
struct TYPE_4__ {TYPE_1__ listen; } ;
struct request_package {TYPE_2__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 
 int do_listen (char const*,int,int) ; 
 int reserve_id (struct socket_server*) ; 
 int /*<<< orphan*/  send_request (struct socket_server*,struct request_package*,char,int) ; 

int 
socket_server_listen(struct socket_server *ss, uintptr_t opaque, const char * addr, int port, int backlog) {
	int fd = do_listen(addr, port, backlog);
	if (fd < 0) {
		return -1;
	}
	struct request_package request;
	int id = reserve_id(ss);
	if (id < 0) {
		close(fd);
		return id;
	}
	request.u.listen.opaque = opaque;
	request.u.listen.id = id;
	request.u.listen.fd = fd;
	send_request(ss, &request, 'L', sizeof(request.u.listen));
	return id;
}