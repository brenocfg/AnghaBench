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
struct TYPE_4__ {int log_target_overridden; int /*<<< orphan*/  original_log_target; } ;
typedef  TYPE_1__ Manager ;
typedef  int /*<<< orphan*/  LogTarget ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  log_get_target () ; 
 int /*<<< orphan*/  log_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_set_target (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_target_to_string (int /*<<< orphan*/ ) ; 

void manager_override_log_target(Manager *m, LogTarget target) {
        assert(m);

        if (!m->log_target_overridden) {
                m->original_log_target = log_get_target();
                m->log_target_overridden = true;
        }

        log_info("Setting log target to %s.", log_target_to_string(target));
        log_set_target(target);
}