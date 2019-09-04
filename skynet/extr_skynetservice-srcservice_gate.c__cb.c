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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct skynet_socket_message {int dummy; } ;
struct skynet_context {int dummy; } ;
struct gate {int /*<<< orphan*/  hash; } ;

/* Variables and functions */
#define  PTYPE_CLIENT 130 
#define  PTYPE_SOCKET 129 
#define  PTYPE_TEXT 128 
 int /*<<< orphan*/  _ctrl (struct gate*,void const*,int) ; 
 int /*<<< orphan*/  dispatch_socket_message (struct gate*,void const*,int) ; 
 int hashid_lookup (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skynet_error (struct skynet_context*,char*,int,...) ; 
 int /*<<< orphan*/  skynet_socket_send (struct skynet_context*,int,void*,size_t) ; 

__attribute__((used)) static int
_cb(struct skynet_context * ctx, void * ud, int type, int session, uint32_t source, const void * msg, size_t sz) {
	struct gate *g = ud;
	switch(type) {
	case PTYPE_TEXT:
		_ctrl(g , msg , (int)sz);
		break;
	case PTYPE_CLIENT: {
		if (sz <=4 ) {
			skynet_error(ctx, "Invalid client message from %x",source);
			break;
		}
		// The last 4 bytes in msg are the id of socket, write following bytes to it
		const uint8_t * idbuf = msg + sz - 4;
		uint32_t uid = idbuf[0] | idbuf[1] << 8 | idbuf[2] << 16 | idbuf[3] << 24;
		int id = hashid_lookup(&g->hash, uid);
		if (id>=0) {
			// don't send id (last 4 bytes)
			skynet_socket_send(ctx, uid, (void*)msg, sz-4);
			// return 1 means don't free msg
			return 1;
		} else {
			skynet_error(ctx, "Invalid client id %d from %x",(int)uid,source);
			break;
		}
	}
	case PTYPE_SOCKET:
		// recv socket message from skynet_socket
		dispatch_socket_message(g, msg, (int)(sz-sizeof(struct skynet_socket_message)));
		break;
	}
	return 0;
}