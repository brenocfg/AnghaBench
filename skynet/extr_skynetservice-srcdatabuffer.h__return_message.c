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
struct messagepool {struct message* freelist; } ;
struct message {struct message* next; scalar_t__ size; int /*<<< orphan*/ * buffer; } ;
struct databuffer {struct message* head; struct message* tail; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  skynet_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
_return_message(struct databuffer *db, struct messagepool *mp) {
	struct message *m = db->head;
	if (m->next == NULL) {
		assert(db->tail == m);
		db->head = db->tail = NULL;
	} else {
		db->head = m->next;
	}
	skynet_free(m->buffer);
	m->buffer = NULL;
	m->size = 0;
	m->next = mp->freelist;
	mp->freelist = m;
}