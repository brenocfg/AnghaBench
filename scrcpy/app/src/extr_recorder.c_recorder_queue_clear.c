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
struct recorder_queue {int dummy; } ;
struct record_packet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  queue_is_empty (struct recorder_queue*) ; 
 int /*<<< orphan*/  queue_take (struct recorder_queue*,int /*<<< orphan*/ ,struct record_packet**) ; 
 int /*<<< orphan*/  record_packet_delete (struct record_packet*) ; 

__attribute__((used)) static void
recorder_queue_clear(struct recorder_queue *queue) {
    while (!queue_is_empty(queue)) {
        struct record_packet *rec;
        queue_take(queue, next, &rec);
        record_packet_delete(rec);
    }
}