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
struct harbor_msg_queue {size_t head; size_t tail; int size; struct harbor_msg* data; } ;
struct harbor_msg {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct harbor_msg *
pop_queue(struct harbor_msg_queue * queue) {
	if (queue->head == queue->tail) {
		return NULL;
	}
	struct harbor_msg * slot = &queue->data[queue->head];
	queue->head = (queue->head + 1) % queue->size;
	return slot;
}