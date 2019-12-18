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
typedef  int /*<<< orphan*/  uint8_t ;
struct socket_sendbuffer {int sz; int /*<<< orphan*/ * buffer; int /*<<< orphan*/  type; int /*<<< orphan*/  id; } ;
struct slave {int /*<<< orphan*/  fd; } ;
struct harbor {int /*<<< orphan*/  ctx; int /*<<< orphan*/  id; struct slave* s; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOCKET_BUFFER_RAWPOINTER ; 
 int /*<<< orphan*/  skynet_socket_sendbuffer (int /*<<< orphan*/ ,struct socket_sendbuffer*) ; 

__attribute__((used)) static void
handshake(struct harbor *h, int id) {
	struct slave *s = &h->s[id];
	uint8_t handshake[1] = { (uint8_t)h->id };
	struct socket_sendbuffer tmp;
	tmp.id = s->fd;
	tmp.type = SOCKET_BUFFER_RAWPOINTER;
	tmp.buffer = handshake;
	tmp.sz = 1;
	skynet_socket_sendbuffer(h->ctx, &tmp);
}