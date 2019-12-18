#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {struct TYPE_12__* home; struct TYPE_12__* name; struct TYPE_12__* state_file; struct TYPE_12__* runtime_path; struct TYPE_12__* slice; struct TYPE_12__* runtime_dir_service; struct TYPE_12__* service; struct TYPE_12__* service_job; int /*<<< orphan*/  timer_event_source; int /*<<< orphan*/  uid; TYPE_1__* manager; scalar_t__ sessions; scalar_t__ in_gc_queue; } ;
typedef  TYPE_2__ User ;
struct TYPE_11__ {int /*<<< orphan*/  users; int /*<<< orphan*/  user_units; int /*<<< orphan*/  user_gc_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_2__* UID_TO_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gc_queue ; 
 int /*<<< orphan*/  hashmap_remove_value (int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*) ; 
 TYPE_2__* mfree (TYPE_2__*) ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  session_free (scalar_t__) ; 

User *user_free(User *u) {
        if (!u)
                return NULL;

        if (u->in_gc_queue)
                LIST_REMOVE(gc_queue, u->manager->user_gc_queue, u);

        while (u->sessions)
                session_free(u->sessions);

        if (u->service)
                hashmap_remove_value(u->manager->user_units, u->service, u);

        if (u->runtime_dir_service)
                hashmap_remove_value(u->manager->user_units, u->runtime_dir_service, u);

        if (u->slice)
                hashmap_remove_value(u->manager->user_units, u->slice, u);

        hashmap_remove_value(u->manager->users, UID_TO_PTR(u->uid), u);

        (void) sd_event_source_unref(u->timer_event_source);

        u->service_job = mfree(u->service_job);

        u->service = mfree(u->service);
        u->runtime_dir_service = mfree(u->runtime_dir_service);
        u->slice = mfree(u->slice);
        u->runtime_path = mfree(u->runtime_path);
        u->state_file = mfree(u->state_file);
        u->name = mfree(u->name);
        u->home = mfree(u->home);

        return mfree(u);
}