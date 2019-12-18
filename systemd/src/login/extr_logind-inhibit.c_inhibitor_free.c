#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  fifo_path; int /*<<< orphan*/  state_file; int /*<<< orphan*/  id; TYPE_1__* manager; int /*<<< orphan*/  fifo_fd; int /*<<< orphan*/  event_source; int /*<<< orphan*/  why; int /*<<< orphan*/  who; } ;
struct TYPE_7__ {int /*<<< orphan*/  inhibitors; } ;
typedef  TYPE_2__ Inhibitor ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashmap_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* mfree (TYPE_2__*) ; 
 int /*<<< orphan*/  safe_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ ) ; 

Inhibitor* inhibitor_free(Inhibitor *i) {

        if (!i)
                return NULL;

        free(i->who);
        free(i->why);

        sd_event_source_unref(i->event_source);
        safe_close(i->fifo_fd);

        hashmap_remove(i->manager->inhibitors, i->id);

        /* Note that we don't remove neither the state file nor the fifo path here, since we want both to
         * survive daemon restarts */
        free(i->state_file);
        free(i->fifo_path);

        return mfree(i);
}