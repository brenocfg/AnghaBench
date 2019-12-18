#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ first_boot; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int EEXIST ; 
 int /*<<< orphan*/  LOG_NOTICE ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  MANAGER_IS_SYSTEM (TYPE_1__*) ; 
 scalar_t__ MANAGER_IS_TEST_RUN (TYPE_1__*) ; 
 int /*<<< orphan*/  UNIT_FILE_PRESET_ENABLE_ONLY ; 
 int /*<<< orphan*/  UNIT_FILE_SYSTEM ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  log_full_errno (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  log_info (char*) ; 
 int unit_file_preset_all (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void manager_preset_all(Manager *m) {
        int r;

        assert(m);

        if (m->first_boot <= 0)
                return;

        if (!MANAGER_IS_SYSTEM(m))
                return;

        if (MANAGER_IS_TEST_RUN(m))
                return;

        /* If this is the first boot, and we are in the host system, then preset everything */
        r = unit_file_preset_all(UNIT_FILE_SYSTEM, 0, NULL, UNIT_FILE_PRESET_ENABLE_ONLY, NULL, 0);
        if (r < 0)
                log_full_errno(r == -EEXIST ? LOG_NOTICE : LOG_WARNING, r,
                               "Failed to populate /etc with preset unit settings, ignoring: %m");
        else
                log_info("Populated /etc with preset unit settings.");
}