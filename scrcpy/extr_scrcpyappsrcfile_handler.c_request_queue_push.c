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
struct request_queue {size_t head; struct request** reqs; } ;
struct request {int dummy; } ;

/* Variables and functions */
 int REQUEST_QUEUE_SIZE ; 
 scalar_t__ request_queue_is_full (struct request_queue*) ; 

__attribute__((used)) static bool
request_queue_push(struct request_queue *queue, struct request *req) {
    if (request_queue_is_full(queue)) {
        return false;
    }
    queue->reqs[queue->head] = req;
    queue->head = (queue->head + 1) % REQUEST_QUEUE_SIZE;
    return true;
}