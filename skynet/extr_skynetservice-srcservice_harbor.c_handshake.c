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
typedef  scalar_t__ uint8_t ;
struct slave {int /*<<< orphan*/  fd; } ;
struct harbor {int /*<<< orphan*/  ctx; scalar_t__ id; struct slave* s; } ;

/* Variables and functions */
 scalar_t__* skynet_malloc (int) ; 
 int /*<<< orphan*/  skynet_socket_send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 

__attribute__((used)) static void
handshake(struct harbor *h, int id) {
	struct slave *s = &h->s[id];
	uint8_t * handshake = skynet_malloc(1);
	handshake[0] = (uint8_t)h->id;
	skynet_socket_send(h->ctx, s->fd, handshake, 1);
}