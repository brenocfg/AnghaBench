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
struct messagepool_list {struct messagepool_list* next; struct message* pool; } ;
struct messagepool {struct message* freelist; struct messagepool_list* pool; } ;
struct message {int size; struct message* next; int /*<<< orphan*/ * buffer; } ;
struct databuffer {int size; struct message* tail; struct message* head; } ;

/* Variables and functions */
 int MESSAGEPOOL ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 struct messagepool_list* skynet_malloc (int) ; 

__attribute__((used)) static void
databuffer_push(struct databuffer *db, struct messagepool *mp, void *data, int sz) {
	struct message * m;
	if (mp->freelist) {
		m = mp->freelist;
		mp->freelist = m->next;
	} else {
		struct messagepool_list * mpl = skynet_malloc(sizeof(*mpl));
		struct message * temp = mpl->pool;
		int i;
		for (i=1;i<MESSAGEPOOL;i++) {
			temp[i].buffer = NULL;
			temp[i].size = 0;
			temp[i].next = &temp[i+1];
		}
		temp[MESSAGEPOOL-1].next = NULL;
		mpl->next = mp->pool;
		mp->pool = mpl;
		m = &temp[0];
		mp->freelist = &temp[1];
	}
	m->buffer = data;
	m->size = sz;
	m->next = NULL;
	db->size += sz;
	if (db->head == NULL) {
		assert(db->tail == NULL);
		db->head = db->tail = m;
	} else {
		db->tail->next = m;
		db->tail = m;
	}
}