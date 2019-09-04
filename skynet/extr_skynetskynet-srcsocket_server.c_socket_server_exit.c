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
struct socket_server {int dummy; } ;
struct request_package {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  send_request (struct socket_server*,struct request_package*,char,int /*<<< orphan*/ ) ; 

void
socket_server_exit(struct socket_server *ss) {
	struct request_package request;
	send_request(ss, &request, 'X', 0);
}