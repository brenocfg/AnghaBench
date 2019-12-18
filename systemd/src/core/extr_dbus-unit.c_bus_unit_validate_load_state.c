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
typedef  int /*<<< orphan*/  sd_bus_error ;
struct TYPE_4__ {int load_state; int /*<<< orphan*/  id; int /*<<< orphan*/  load_error; } ;
typedef  TYPE_1__ Unit ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_ERROR_BAD_UNIT_SETTING ; 
 int /*<<< orphan*/  BUS_ERROR_NO_SUCH_UNIT ; 
 int /*<<< orphan*/  BUS_ERROR_UNIT_MASKED ; 
#define  UNIT_BAD_SETTING 134 
#define  UNIT_ERROR 133 
#define  UNIT_LOADED 132 
#define  UNIT_MASKED 131 
#define  UNIT_MERGED 130 
#define  UNIT_NOT_FOUND 129 
#define  UNIT_STUB 128 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int sd_bus_error_set_errnof (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int sd_bus_error_setf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int bus_unit_validate_load_state(Unit *u, sd_bus_error *error) {
        assert(u);

        /* Generates a pretty error if a unit isn't properly loaded. */

        switch (u->load_state) {

        case UNIT_LOADED:
                return 0;

        case UNIT_NOT_FOUND:
                return sd_bus_error_setf(error, BUS_ERROR_NO_SUCH_UNIT, "Unit %s not found.", u->id);

        case UNIT_BAD_SETTING:
                return sd_bus_error_setf(error, BUS_ERROR_BAD_UNIT_SETTING, "Unit %s has a bad unit file setting.", u->id);

        case UNIT_ERROR: /* Only show .load_error in UNIT_ERROR state */
                return sd_bus_error_set_errnof(error, u->load_error, "Unit %s failed to load properly: %m.", u->id);

        case UNIT_MASKED:
                return sd_bus_error_setf(error, BUS_ERROR_UNIT_MASKED, "Unit %s is masked.", u->id);

        case UNIT_STUB:
        case UNIT_MERGED:
        default:
                return sd_bus_error_setf(error, BUS_ERROR_NO_SUCH_UNIT, "Unexpected load state of unit %s", u->id);
        }
}