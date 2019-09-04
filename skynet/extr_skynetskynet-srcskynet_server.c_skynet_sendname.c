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
typedef  scalar_t__ uint32_t ;
struct skynet_context {scalar_t__ handle; } ;
struct TYPE_2__ {scalar_t__ handle; int /*<<< orphan*/  name; } ;
struct remote_message {size_t sz; size_t type; void* message; TYPE_1__ destination; } ;

/* Variables and functions */
 size_t MESSAGE_TYPE_MASK ; 
 size_t MESSAGE_TYPE_SHIFT ; 
 int PTYPE_TAG_DONTCOPY ; 
 int /*<<< orphan*/  _filter_args (struct skynet_context*,int,int*,void**,size_t*) ; 
 int /*<<< orphan*/  copy_name (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  skynet_error (struct skynet_context*,char*,char const*) ; 
 int /*<<< orphan*/  skynet_free (void*) ; 
 scalar_t__ skynet_handle_findname (char const*) ; 
 int /*<<< orphan*/  skynet_harbor_send (struct remote_message*,scalar_t__,int) ; 
 struct remote_message* skynet_malloc (int) ; 
 int skynet_send (struct skynet_context*,scalar_t__,scalar_t__,int,int,void*,size_t) ; 
 scalar_t__ strtoul (char const*,int /*<<< orphan*/ *,int) ; 

int
skynet_sendname(struct skynet_context * context, uint32_t source, const char * addr , int type, int session, void * data, size_t sz) {
	if (source == 0) {
		source = context->handle;
	}
	uint32_t des = 0;
	if (addr[0] == ':') {
		des = strtoul(addr+1, NULL, 16);
	} else if (addr[0] == '.') {
		des = skynet_handle_findname(addr + 1);
		if (des == 0) {
			if (type & PTYPE_TAG_DONTCOPY) {
				skynet_free(data);
			}
			return -1;
		}
	} else {
		if ((sz & MESSAGE_TYPE_MASK) != sz) {
			skynet_error(context, "The message to %s is too large", addr);
			if (type & PTYPE_TAG_DONTCOPY) {
				skynet_free(data);
			}
			return -2;
		}
		_filter_args(context, type, &session, (void **)&data, &sz);

		struct remote_message * rmsg = skynet_malloc(sizeof(*rmsg));
		copy_name(rmsg->destination.name, addr);
		rmsg->destination.handle = 0;
		rmsg->message = data;
		rmsg->sz = sz & MESSAGE_TYPE_MASK;
		rmsg->type = sz >> MESSAGE_TYPE_SHIFT;

		skynet_harbor_send(rmsg, source, session);
		return session;
	}

	return skynet_send(context, source, des, type, session, data, sz);
}