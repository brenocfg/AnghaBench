#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct write_queue_item {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  rfkill_fd; struct write_queue_item* write_queue; } ;
typedef  TYPE_1__ Context ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (int /*<<< orphan*/ ,struct write_queue_item*,struct write_queue_item*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  queue ; 
 int /*<<< orphan*/  safe_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  save_state_write_one (struct write_queue_item*) ; 
 int /*<<< orphan*/  write_queue_item_free (struct write_queue_item*) ; 

__attribute__((used)) static void context_save_and_clear(Context *c) {
        struct write_queue_item *i;

        assert(c);

        while ((i = c->write_queue)) {
                LIST_REMOVE(queue, c->write_queue, i);
                (void) save_state_write_one(i);
                write_queue_item_free(i);
        }

        safe_close(c->rfkill_fd);
}