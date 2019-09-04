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
struct write_buffer {scalar_t__ sz; } ;
struct socket_server {int dummy; } ;
struct socket {int /*<<< orphan*/  wb_size; int /*<<< orphan*/  low; } ;
struct request_send {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIZEOF_TCPBUFFER ; 
 struct write_buffer* append_sendbuffer_ (struct socket_server*,int /*<<< orphan*/ *,struct request_send*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
append_sendbuffer_low(struct socket_server *ss,struct socket *s, struct request_send * request) {
	struct write_buffer *buf = append_sendbuffer_(ss, &s->low, request, SIZEOF_TCPBUFFER);
	s->wb_size += buf->sz;
}