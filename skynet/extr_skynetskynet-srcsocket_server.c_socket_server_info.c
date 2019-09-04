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
struct socket_server {struct socket* slot; } ;
struct socket_info {int /*<<< orphan*/  next; } ;
struct socket {int id; } ;

/* Variables and functions */
 int MAX_SOCKET ; 
 scalar_t__ query_info (struct socket*,struct socket_info*) ; 
 struct socket_info* socket_info_create (struct socket_info*) ; 

struct socket_info *
socket_server_info(struct socket_server *ss) {
	int i;
	struct socket_info * si = NULL;
	for (i=0;i<MAX_SOCKET;i++) {
		struct socket * s = &ss->slot[i];
		int id = s->id;
		struct socket_info temp;
		if (query_info(s, &temp) && s->id == id) {
			// socket_server_info may call in different thread, so check socket id again
			si = socket_info_create(si);
			temp.next = si->next;
			*si = temp;
		}
	}
	return si;
}