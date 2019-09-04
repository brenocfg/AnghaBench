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
struct TYPE_3__ {uintptr_t opaque; int id; int port; char* host; } ;
struct TYPE_4__ {TYPE_1__ open; } ;
struct request_package {TYPE_2__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int reserve_id (struct socket_server*) ; 
 int /*<<< orphan*/  stderr ; 
 int strlen (char const*) ; 

__attribute__((used)) static int
open_request(struct socket_server *ss, struct request_package *req, uintptr_t opaque, const char *addr, int port) {
	int len = strlen(addr);
	if (len + sizeof(req->u.open) >= 256) {
		fprintf(stderr, "socket-server : Invalid addr %s.\n",addr);
		return -1;
	}
	int id = reserve_id(ss);
	if (id < 0)
		return -1;
	req->u.open.opaque = opaque;
	req->u.open.id = id;
	req->u.open.port = port;
	memcpy(req->u.open.host, addr, len);
	req->u.open.host[len] = '\0';

	return len;
}