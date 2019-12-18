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
struct TYPE_3__ {int id; int value; int /*<<< orphan*/  what; } ;
struct TYPE_4__ {TYPE_1__ setopt; } ;
struct request_package {TYPE_2__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCP_NODELAY ; 
 int /*<<< orphan*/  send_request (struct socket_server*,struct request_package*,char,int) ; 

void
socket_server_nodelay(struct socket_server *ss, int id) {
	struct request_package request;
	request.u.setopt.id = id;
	request.u.setopt.what = TCP_NODELAY;
	request.u.setopt.value = 1;
	send_request(ss, &request, 'T', sizeof(request.u.setopt));
}