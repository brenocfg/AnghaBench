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
struct request_queue {scalar_t__ head; scalar_t__ tail; } ;

/* Variables and functions */

__attribute__((used)) static bool
request_queue_is_empty(const struct request_queue *queue) {
    return queue->head == queue->tail;
}