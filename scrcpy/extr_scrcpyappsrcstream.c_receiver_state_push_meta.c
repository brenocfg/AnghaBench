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
typedef  int /*<<< orphan*/  uint64_t ;
struct receiver_state {struct frame_meta* frame_meta_queue; } ;
struct frame_meta {struct frame_meta* next; } ;

/* Variables and functions */
 struct frame_meta* frame_meta_new (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
receiver_state_push_meta(struct receiver_state *state, uint64_t pts) {
    struct frame_meta *frame_meta = frame_meta_new(pts);
    if (!frame_meta) {
        return false;
    }

    // append to the list
    // (iterate to find the last item, in practice the list should be tiny)
    struct frame_meta **p = &state->frame_meta_queue;
    while (*p) {
        p = &(*p)->next;
    }
    *p = frame_meta;
    return true;
}