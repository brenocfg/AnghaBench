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
struct TYPE_4__ {int exported_invocation_id; int exported_log_level_max; int exported_log_extra_fields; int exported_log_ratelimit_interval; int exported_log_ratelimit_burst; int /*<<< orphan*/  id; int /*<<< orphan*/  manager; } ;
typedef  TYPE_1__ Unit ;

/* Variables and functions */
 int /*<<< orphan*/  MANAGER_IS_SYSTEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 char* strjoina (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (char const*) ; 

void unit_unlink_state_files(Unit *u) {
        const char *p;

        assert(u);

        if (!u->id)
                return;

        if (!MANAGER_IS_SYSTEM(u->manager))
                return;

        /* Undoes the effect of unit_export_state() */

        if (u->exported_invocation_id) {
                p = strjoina("/run/systemd/units/invocation:", u->id);
                (void) unlink(p);

                u->exported_invocation_id = false;
        }

        if (u->exported_log_level_max) {
                p = strjoina("/run/systemd/units/log-level-max:", u->id);
                (void) unlink(p);

                u->exported_log_level_max = false;
        }

        if (u->exported_log_extra_fields) {
                p = strjoina("/run/systemd/units/extra-fields:", u->id);
                (void) unlink(p);

                u->exported_log_extra_fields = false;
        }

        if (u->exported_log_ratelimit_interval) {
                p = strjoina("/run/systemd/units/log-rate-limit-interval:", u->id);
                (void) unlink(p);

                u->exported_log_ratelimit_interval = false;
        }

        if (u->exported_log_ratelimit_burst) {
                p = strjoina("/run/systemd/units/log-rate-limit-burst:", u->id);
                (void) unlink(p);

                u->exported_log_ratelimit_burst = false;
        }
}