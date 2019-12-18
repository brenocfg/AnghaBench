#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ begin_usec; scalar_t__ begin_running_usec; int /*<<< orphan*/  bus_track; int /*<<< orphan*/  ignore_order; int /*<<< orphan*/  sent_dbus_new_signal; int /*<<< orphan*/  irreversible; int /*<<< orphan*/  state; int /*<<< orphan*/  type; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ Job ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  bus_track_serialize (int /*<<< orphan*/ ,TYPE_1__*,char*) ; 
 int /*<<< orphan*/  fputc (char,TYPE_1__*) ; 
 int /*<<< orphan*/  job_state_to_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  job_type_to_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serialize_bool (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serialize_item (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serialize_item_format (TYPE_1__*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serialize_usec (TYPE_1__*,char*,scalar_t__) ; 

int job_serialize(Job *j, FILE *f) {
        assert(j);
        assert(f);

        (void) serialize_item_format(f, "job-id", "%u", j->id);
        (void) serialize_item(f, "job-type", job_type_to_string(j->type));
        (void) serialize_item(f, "job-state", job_state_to_string(j->state));
        (void) serialize_bool(f, "job-irreversible", j->irreversible);
        (void) serialize_bool(f, "job-sent-dbus-new-signal", j->sent_dbus_new_signal);
        (void) serialize_bool(f, "job-ignore-order", j->ignore_order);

        if (j->begin_usec > 0)
                (void) serialize_usec(f, "job-begin", j->begin_usec);
        if (j->begin_running_usec > 0)
                (void) serialize_usec(f, "job-begin-running", j->begin_running_usec);

        bus_track_serialize(j->bus_track, f, "subscribed");

        /* End marker */
        fputc('\n', f);
        return 0;
}