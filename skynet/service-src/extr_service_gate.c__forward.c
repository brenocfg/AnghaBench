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
struct gate {int client_tag; int /*<<< orphan*/  watchdog; int /*<<< orphan*/  mp; int /*<<< orphan*/  broker; struct skynet_context* ctx; } ;
struct connection {int id; int /*<<< orphan*/  buffer; int /*<<< orphan*/  agent; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int PTYPE_TAG_DONTCOPY ; 
 int PTYPE_TEXT ; 
 int /*<<< orphan*/  databuffer_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int) ; 
 void* skynet_malloc (int) ; 
 int /*<<< orphan*/  skynet_send (struct skynet_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,char*,int) ; 
 int snprintf (char*,int,char*,int) ; 

__attribute__((used)) static void
_forward(struct gate *g, struct connection * c, int size) {
	struct skynet_context * ctx = g->ctx;
	int fd = c->id;
	if (fd <= 0) {
		// socket error
		return;
	}
	if (g->broker) {
		void * temp = skynet_malloc(size);
		databuffer_read(&c->buffer,&g->mp,temp, size);
		skynet_send(ctx, 0, g->broker, g->client_tag | PTYPE_TAG_DONTCOPY, fd, temp, size);
		return;
	}
	if (c->agent) {
		void * temp = skynet_malloc(size);
		databuffer_read(&c->buffer,&g->mp,temp, size);
		skynet_send(ctx, c->client, c->agent, g->client_tag | PTYPE_TAG_DONTCOPY, fd , temp, size);
	} else if (g->watchdog) {
		char * tmp = skynet_malloc(size + 32);
		int n = snprintf(tmp,32,"%d data ",c->id);
		databuffer_read(&c->buffer,&g->mp,tmp+n,size);
		skynet_send(ctx, 0, g->watchdog, PTYPE_TEXT | PTYPE_TAG_DONTCOPY, fd, tmp, size + n);
	}
}