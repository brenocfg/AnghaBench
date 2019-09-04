#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct skynet_socket_message {void* buffer; int ud; int /*<<< orphan*/  id; int /*<<< orphan*/  type; } ;
struct skynet_context {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  handle; int /*<<< orphan*/  name; } ;
struct remote_message {scalar_t__ message; int /*<<< orphan*/  sz; int /*<<< orphan*/  type; TYPE_1__ destination; } ;
struct harbor {int dummy; } ;

/* Variables and functions */
 int PTYPE_ERROR ; 
#define  PTYPE_HARBOR 135 
#define  PTYPE_SOCKET 134 
#define  PTYPE_SYSTEM 133 
#define  SKYNET_SOCKET_TYPE_CLOSE 132 
#define  SKYNET_SOCKET_TYPE_CONNECT 131 
#define  SKYNET_SOCKET_TYPE_DATA 130 
#define  SKYNET_SOCKET_TYPE_ERROR 129 
#define  SKYNET_SOCKET_TYPE_WARNING 128 
 int /*<<< orphan*/  harbor_command (struct harbor*,void const*,size_t,int,int) ; 
 int harbor_id (struct harbor*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_socket_data (struct harbor*,struct skynet_socket_message const*) ; 
 int /*<<< orphan*/  remote_send_handle (struct harbor*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remote_send_name (struct harbor*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  report_harbor_down (struct harbor*,int) ; 
 int /*<<< orphan*/  skynet_error (struct skynet_context*,char*,int,...) ; 
 int /*<<< orphan*/  skynet_free (void*) ; 
 int /*<<< orphan*/  skynet_send (struct skynet_context*,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mainloop(struct skynet_context * context, void * ud, int type, int session, uint32_t source, const void * msg, size_t sz) {
	struct harbor * h = ud;
	switch (type) {
	case PTYPE_SOCKET: {
		const struct skynet_socket_message * message = msg;
		switch(message->type) {
		case SKYNET_SOCKET_TYPE_DATA:
			push_socket_data(h, message);
			skynet_free(message->buffer);
			break;
		case SKYNET_SOCKET_TYPE_ERROR:
		case SKYNET_SOCKET_TYPE_CLOSE: {
			int id = harbor_id(h, message->id);
			if (id) {
				report_harbor_down(h,id);
			} else {
				skynet_error(context, "Unkown fd (%d) closed", message->id);
			}
			break;
		}
		case SKYNET_SOCKET_TYPE_CONNECT:
			// fd forward to this service
			break;
		case SKYNET_SOCKET_TYPE_WARNING: {
			int id = harbor_id(h, message->id);
			if (id) {
				skynet_error(context, "message havn't send to Harbor (%d) reach %d K", id, message->ud);
			}
			break;
		}
		default:
			skynet_error(context, "recv invalid socket message type %d", type);
			break;
		}
		return 0;
	}
	case PTYPE_HARBOR: {
		harbor_command(h, msg,sz,session,source);
		return 0;
	}
	case PTYPE_SYSTEM : {
		// remote message out
		const struct remote_message *rmsg = msg;
		if (rmsg->destination.handle == 0) {
			if (remote_send_name(h, source , rmsg->destination.name, rmsg->type, session, rmsg->message, rmsg->sz)) {
				return 0;
			}
		} else {
			if (remote_send_handle(h, source , rmsg->destination.handle, rmsg->type, session, rmsg->message, rmsg->sz)) {
				return 0;
			}
		}
		skynet_free((void *)rmsg->message);
		return 0;
	}
	default:
		skynet_error(context, "recv invalid message from %x,  type = %d", source, type);
		if (session != 0 && type != PTYPE_ERROR) {
			skynet_send(context,0,source,PTYPE_ERROR, session, NULL, 0);
		}
		return 0;
	}
}