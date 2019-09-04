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
struct harbor_msg_queue {struct harbor_msg_queue* data; } ;
struct harbor_msg {struct harbor_msg_queue* buffer; } ;

/* Variables and functions */
 struct harbor_msg* pop_queue (struct harbor_msg_queue*) ; 
 int /*<<< orphan*/  skynet_free (struct harbor_msg_queue*) ; 

__attribute__((used)) static void
release_queue(struct harbor_msg_queue *queue) {
	if (queue == NULL)
		return;
	struct harbor_msg * m;
	while ((m=pop_queue(queue)) != NULL) {
		skynet_free(m->buffer);
	}
	skynet_free(queue->data);
	skynet_free(queue);
}