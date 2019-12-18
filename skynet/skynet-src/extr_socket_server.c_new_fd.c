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
struct socket_server {int /*<<< orphan*/  event_fd; struct socket* slot; } ;
struct TYPE_2__ {int /*<<< orphan*/  size; } ;
struct socket {scalar_t__ type; int id; int fd; int sending; int protocol; uintptr_t opaque; int /*<<< orphan*/  stat; scalar_t__ dw_size; int /*<<< orphan*/ * dw_buffer; int /*<<< orphan*/  low; int /*<<< orphan*/  high; scalar_t__ warn_size; scalar_t__ wb_size; TYPE_1__ p; } ;

/* Variables and functions */
 size_t HASH_ID (int) ; 
 int ID_TAG16 (int) ; 
 int /*<<< orphan*/  MIN_READ_BUFFER ; 
 scalar_t__ SOCKET_TYPE_INVALID ; 
 scalar_t__ SOCKET_TYPE_RESERVE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  check_wb_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sp_add (int /*<<< orphan*/ ,int,struct socket*) ; 

__attribute__((used)) static struct socket *
new_fd(struct socket_server *ss, int id, int fd, int protocol, uintptr_t opaque, bool add) {
	struct socket * s = &ss->slot[HASH_ID(id)];
	assert(s->type == SOCKET_TYPE_RESERVE);

	if (add) {
		if (sp_add(ss->event_fd, fd, s)) {
			s->type = SOCKET_TYPE_INVALID;
			return NULL;
		}
	}

	s->id = id;
	s->fd = fd;
	s->sending = ID_TAG16(id) << 16 | 0;
	s->protocol = protocol;
	s->p.size = MIN_READ_BUFFER;
	s->opaque = opaque;
	s->wb_size = 0;
	s->warn_size = 0;
	check_wb_list(&s->high);
	check_wb_list(&s->low);
	s->dw_buffer = NULL;
	s->dw_size = 0;
	memset(&s->stat, 0, sizeof(s->stat));
	return s;
}