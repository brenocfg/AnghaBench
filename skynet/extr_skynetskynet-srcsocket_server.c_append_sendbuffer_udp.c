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
struct write_buffer {scalar_t__ sz; int /*<<< orphan*/  udp_address; } ;
struct wb_list {int dummy; } ;
struct socket_server {int dummy; } ;
struct socket {int /*<<< orphan*/  wb_size; struct wb_list low; struct wb_list high; } ;
struct request_send {int dummy; } ;

/* Variables and functions */
 int PRIORITY_HIGH ; 
 int /*<<< orphan*/  SIZEOF_UDPBUFFER ; 
 int /*<<< orphan*/  UDP_ADDRESS_SIZE ; 
 struct write_buffer* append_sendbuffer_ (struct socket_server*,struct wb_list*,struct request_send*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
append_sendbuffer_udp(struct socket_server *ss, struct socket *s, int priority, struct request_send * request, const uint8_t udp_address[UDP_ADDRESS_SIZE]) {
	struct wb_list *wl = (priority == PRIORITY_HIGH) ? &s->high : &s->low;
	struct write_buffer *buf = append_sendbuffer_(ss, wl, request, SIZEOF_UDPBUFFER);
	memcpy(buf->udp_address, udp_address, UDP_ADDRESS_SIZE);
	s->wb_size += buf->sz;
}