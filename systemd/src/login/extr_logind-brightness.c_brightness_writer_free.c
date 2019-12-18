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
struct TYPE_8__ {int /*<<< orphan*/  child_event_source; int /*<<< orphan*/  pending_messages; int /*<<< orphan*/  current_messages; struct TYPE_8__* path; int /*<<< orphan*/  device; TYPE_1__* manager; } ;
struct TYPE_7__ {int /*<<< orphan*/  brightness_writers; } ;
typedef  TYPE_2__ BrightnessWriter ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  hashmap_remove_value (int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  sd_device_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void brightness_writer_free(BrightnessWriter *w) {
        if (!w)
                return;

        if (w->manager && w->path)
                (void) hashmap_remove_value(w->manager->brightness_writers, w->path, w);

        sd_device_unref(w->device);
        free(w->path);

        set_free(w->current_messages);
        set_free(w->pending_messages);

        w->child_event_source = sd_event_source_unref(w->child_event_source);

        free(w);
}