#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  state_file; int /*<<< orphan*/  positions; int /*<<< orphan*/  id; TYPE_1__* manager; scalar_t__ devices; int /*<<< orphan*/  active; scalar_t__ sessions; scalar_t__ in_gc_queue; } ;
struct TYPE_8__ {int /*<<< orphan*/  seats; int /*<<< orphan*/  seat_gc_queue; } ;
typedef  TYPE_2__ Seat ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  device_free (scalar_t__) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gc_queue ; 
 int /*<<< orphan*/  hashmap_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* mfree (TYPE_2__*) ; 
 int /*<<< orphan*/  session_free (scalar_t__) ; 

Seat* seat_free(Seat *s) {
        if (!s)
                return NULL;

        if (s->in_gc_queue)
                LIST_REMOVE(gc_queue, s->manager->seat_gc_queue, s);

        while (s->sessions)
                session_free(s->sessions);

        assert(!s->active);

        while (s->devices)
                device_free(s->devices);

        hashmap_remove(s->manager->seats, s->id);

        free(s->positions);
        free(s->state_file);

        return mfree(s);
}