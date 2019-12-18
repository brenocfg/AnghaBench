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
struct skynet_context {int dummy; } ;
struct gate {int /*<<< orphan*/  listen_id; struct skynet_context* ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  BACKLOG ; 
 int /*<<< orphan*/  skynet_error (struct skynet_context*,char*,char*) ; 
 int /*<<< orphan*/  skynet_socket_listen (struct skynet_context*,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skynet_socket_start (struct skynet_context*,int /*<<< orphan*/ ) ; 
 char* strrchr (char*,char) ; 
 int strtol (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
start_listen(struct gate *g, char * listen_addr) {
	struct skynet_context * ctx = g->ctx;
	char * portstr = strrchr(listen_addr,':');
	const char * host = "";
	int port;
	if (portstr == NULL) {
		port = strtol(listen_addr, NULL, 10);
		if (port <= 0) {
			skynet_error(ctx, "Invalid gate address %s",listen_addr);
			return 1;
		}
	} else {
		port = strtol(portstr + 1, NULL, 10);
		if (port <= 0) {
			skynet_error(ctx, "Invalid gate address %s",listen_addr);
			return 1;
		}
		portstr[0] = '\0';
		host = listen_addr;
	}
	g->listen_id = skynet_socket_listen(ctx, host, port, BACKLOG);
	if (g->listen_id < 0) {
		return 1;
	}
	skynet_socket_start(ctx, g->listen_id);
	return 0;
}