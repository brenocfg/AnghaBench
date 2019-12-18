#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  job_path; int /*<<< orphan*/  job_type; int /*<<< orphan*/  job_id; int /*<<< orphan*/  unit_path; int /*<<< orphan*/  following; int /*<<< orphan*/  sub_state; int /*<<< orphan*/  active_state; int /*<<< orphan*/  load_state; int /*<<< orphan*/  description; int /*<<< orphan*/  id; int /*<<< orphan*/ * machine; } ;
typedef  TYPE_1__ sd_bus_message ;
typedef  TYPE_1__ UnitInfo ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int sd_bus_message_read (TYPE_1__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int bus_parse_unit_info(sd_bus_message *message, UnitInfo *u) {
        assert(message);
        assert(u);

        u->machine = NULL;

        return sd_bus_message_read(
                        message,
                        "(ssssssouso)",
                        &u->id,
                        &u->description,
                        &u->load_state,
                        &u->active_state,
                        &u->sub_state,
                        &u->following,
                        &u->unit_path,
                        &u->job_id,
                        &u->job_type,
                        &u->job_path);
}