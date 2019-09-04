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
struct frame_meta {struct frame_meta* next; int /*<<< orphan*/  pts; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_assert (struct frame_meta*) ; 
 int /*<<< orphan*/  frame_meta_delete (struct frame_meta*) ; 

__attribute__((used)) static uint64_t
receiver_state_take_meta(struct receiver_state *state) {
    struct frame_meta *frame_meta = state->frame_meta_queue; // first item
    SDL_assert(frame_meta); // must not be empty
    uint64_t pts = frame_meta->pts;
    state->frame_meta_queue = frame_meta->next; // remove the item
    frame_meta_delete(frame_meta);
    return pts;
}