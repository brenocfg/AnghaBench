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
struct control_event_queue {int tail; int head; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int CONTROL_EVENT_QUEUE_SIZE ; 
 int /*<<< orphan*/  control_event_destroy (int /*<<< orphan*/ *) ; 

void
control_event_queue_destroy(struct control_event_queue *queue) {
    int i = queue->tail;
    while (i != queue->head) {
        control_event_destroy(&queue->data[i]);
        i = (i + 1) % CONTROL_EVENT_QUEUE_SIZE;
    }
}