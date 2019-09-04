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
struct skynet_message {int session; size_t sz; void* data; scalar_t__ source; } ;
struct skynet_context {scalar_t__ handle; } ;
struct TYPE_2__ {scalar_t__ handle; } ;
struct remote_message {size_t sz; size_t type; void* message; TYPE_1__ destination; } ;

/* Variables and functions */
 size_t MESSAGE_TYPE_MASK ; 
 size_t MESSAGE_TYPE_SHIFT ; 
 int PTYPE_TAG_DONTCOPY ; 
 int /*<<< orphan*/  _filter_args (struct skynet_context*,int,int*,void**,size_t*) ; 
 scalar_t__ skynet_context_push (scalar_t__,struct skynet_message*) ; 
 int /*<<< orphan*/  skynet_error (struct skynet_context*,char*,...) ; 
 int /*<<< orphan*/  skynet_free (void*) ; 
 scalar_t__ skynet_harbor_message_isremote (scalar_t__) ; 
 int /*<<< orphan*/  skynet_harbor_send (struct remote_message*,scalar_t__,int) ; 
 struct remote_message* skynet_malloc (int) ; 

int
skynet_send(struct skynet_context * context, uint32_t source, uint32_t destination , int type, int session, void * data, size_t sz) {
	if ((sz & MESSAGE_TYPE_MASK) != sz) {
		skynet_error(context, "The message to %x is too large", destination);
		if (type & PTYPE_TAG_DONTCOPY) {
			skynet_free(data);
		}
		return -2;
	}
	_filter_args(context, type, &session, (void **)&data, &sz);

	if (source == 0) {
		source = context->handle;
	}

	if (destination == 0) {
		if (data) {
			skynet_error(context, "Destination address can't be 0");
			skynet_free(data);
			return -1;
		}

		return session;
	}
	if (skynet_harbor_message_isremote(destination)) {
		struct remote_message * rmsg = skynet_malloc(sizeof(*rmsg));
		rmsg->destination.handle = destination;
		rmsg->message = data;
		rmsg->sz = sz & MESSAGE_TYPE_MASK;
		rmsg->type = sz >> MESSAGE_TYPE_SHIFT;
		skynet_harbor_send(rmsg, source, session);
	} else {
		struct skynet_message smsg;
		smsg.source = source;
		smsg.session = session;
		smsg.data = data;
		smsg.sz = sz;

		if (skynet_context_push(destination, &smsg)) {
			skynet_free(data);
			return -1;
		}
	}
	return session;
}