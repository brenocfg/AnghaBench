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
struct skynet_socket_message {int type; int id; int ud; int /*<<< orphan*/  buffer; } ;
struct skynet_context {int dummy; } ;
struct gate {int listen_id; int /*<<< orphan*/  hash; struct connection* conn; int /*<<< orphan*/  mp; struct skynet_context* ctx; } ;
struct connection {int id; char* remote_name; int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
#define  SKYNET_SOCKET_TYPE_ACCEPT 133 
#define  SKYNET_SOCKET_TYPE_CLOSE 132 
#define  SKYNET_SOCKET_TYPE_CONNECT 131 
#define  SKYNET_SOCKET_TYPE_DATA 130 
#define  SKYNET_SOCKET_TYPE_ERROR 129 
#define  SKYNET_SOCKET_TYPE_WARNING 128 
 int /*<<< orphan*/  _report (struct gate*,char*,int,...) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  databuffer_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dispatch_message (struct gate*,struct connection*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hashid_full (int /*<<< orphan*/ *) ; 
 size_t hashid_insert (int /*<<< orphan*/ *,int) ; 
 int hashid_lookup (int /*<<< orphan*/ *,int) ; 
 int hashid_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (char*,struct skynet_socket_message const*,int) ; 
 int /*<<< orphan*/  memset (struct connection*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skynet_error (struct skynet_context*,char*,int,...) ; 
 int /*<<< orphan*/  skynet_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skynet_socket_close (struct skynet_context*,int) ; 

__attribute__((used)) static void
dispatch_socket_message(struct gate *g, const struct skynet_socket_message * message, int sz) {
	struct skynet_context * ctx = g->ctx;
	switch(message->type) {
	case SKYNET_SOCKET_TYPE_DATA: {
		int id = hashid_lookup(&g->hash, message->id);
		if (id>=0) {
			struct connection *c = &g->conn[id];
			dispatch_message(g, c, message->id, message->buffer, message->ud);
		} else {
			skynet_error(ctx, "Drop unknown connection %d message", message->id);
			skynet_socket_close(ctx, message->id);
			skynet_free(message->buffer);
		}
		break;
	}
	case SKYNET_SOCKET_TYPE_CONNECT: {
		if (message->id == g->listen_id) {
			// start listening
			break;
		}
		int id = hashid_lookup(&g->hash, message->id);
		if (id<0) {
			skynet_error(ctx, "Close unknown connection %d", message->id);
			skynet_socket_close(ctx, message->id);
		}
		break;
	}
	case SKYNET_SOCKET_TYPE_CLOSE:
	case SKYNET_SOCKET_TYPE_ERROR: {
		int id = hashid_remove(&g->hash, message->id);
		if (id>=0) {
			struct connection *c = &g->conn[id];
			databuffer_clear(&c->buffer,&g->mp);
			memset(c, 0, sizeof(*c));
			c->id = -1;
			_report(g, "%d close", message->id);
		}
		break;
	}
	case SKYNET_SOCKET_TYPE_ACCEPT:
		// report accept, then it will be get a SKYNET_SOCKET_TYPE_CONNECT message
		assert(g->listen_id == message->id);
		if (hashid_full(&g->hash)) {
			skynet_socket_close(ctx, message->ud);
		} else {
			struct connection *c = &g->conn[hashid_insert(&g->hash, message->ud)];
			if (sz >= sizeof(c->remote_name)) {
				sz = sizeof(c->remote_name) - 1;
			}
			c->id = message->ud;
			memcpy(c->remote_name, message+1, sz);
			c->remote_name[sz] = '\0';
			_report(g, "%d open %d %s:0",c->id, c->id, c->remote_name);
			skynet_error(ctx, "socket open: %x", c->id);
		}
		break;
	case SKYNET_SOCKET_TYPE_WARNING:
		skynet_error(ctx, "fd (%d) send buffer (%d)K", message->id, message->ud);
		break;
	}
}