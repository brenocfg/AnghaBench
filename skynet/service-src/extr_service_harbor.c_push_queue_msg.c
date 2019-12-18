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
struct harbor_msg_queue {int tail; int size; int head; struct harbor_msg* data; } ;
struct harbor_msg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  skynet_free (struct harbor_msg*) ; 
 struct harbor_msg* skynet_malloc (int) ; 

__attribute__((used)) static void
push_queue_msg(struct harbor_msg_queue * queue, struct harbor_msg * m) {
	// If there is only 1 free slot which is reserved to distinguish full/empty
	// of circular buffer, expand it.
	if (((queue->tail + 1) % queue->size) == queue->head) {
		struct harbor_msg * new_buffer = skynet_malloc(queue->size * 2 * sizeof(struct harbor_msg));
		int i;
		for (i=0;i<queue->size-1;i++) {
			new_buffer[i] = queue->data[(i+queue->head) % queue->size];
		}
		skynet_free(queue->data);
		queue->data = new_buffer;
		queue->head = 0;
		queue->tail = queue->size - 1;
		queue->size *= 2;
	}
	struct harbor_msg * slot = &queue->data[queue->tail];
	*slot = *m;
	queue->tail = (queue->tail + 1) % queue->size;
}