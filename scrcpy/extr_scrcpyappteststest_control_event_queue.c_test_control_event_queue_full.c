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
struct control_event_queue {int dummy; } ;
struct control_event {int dummy; } ;
typedef  int SDL_bool ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  control_event_queue_destroy (struct control_event_queue*) ; 
 int control_event_queue_init (struct control_event_queue*) ; 
 int /*<<< orphan*/  control_event_queue_is_full (struct control_event_queue*) ; 
 scalar_t__ control_event_queue_push (struct control_event_queue*,struct control_event*) ; 
 int control_event_queue_take (struct control_event_queue*,struct control_event*) ; 

__attribute__((used)) static void test_control_event_queue_full(void) {
    struct control_event_queue queue;
    SDL_bool init_ok = control_event_queue_init(&queue);
    assert(init_ok);

    assert(!control_event_queue_is_full(&queue));

    struct control_event dummy_event;
    // fill the queue
    while (control_event_queue_push(&queue, &dummy_event));

    SDL_bool take_ok = control_event_queue_take(&queue, &dummy_event);
    assert(take_ok);
    assert(!control_event_queue_is_full(&queue));

    control_event_queue_destroy(&queue);
}