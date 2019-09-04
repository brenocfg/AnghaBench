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
struct request_queue {int tail; int head; int /*<<< orphan*/ * reqs; } ;

/* Variables and functions */
 int REQUEST_QUEUE_SIZE ; 
 int /*<<< orphan*/  request_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
request_queue_destroy(struct request_queue *queue) {
    int i = queue->tail;
    while (i != queue->head) {
        request_free(queue->reqs[i]);
        i = (i + 1) % REQUEST_QUEUE_SIZE;
    }
}