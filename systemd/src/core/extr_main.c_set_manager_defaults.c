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
struct TYPE_7__ {int /*<<< orphan*/  default_oom_policy; int /*<<< orphan*/  default_tasks_max; int /*<<< orphan*/  default_tasks_accounting; int /*<<< orphan*/  default_memory_accounting; int /*<<< orphan*/  default_blockio_accounting; int /*<<< orphan*/  default_ip_accounting; int /*<<< orphan*/  default_io_accounting; scalar_t__ default_cpu_accounting; int /*<<< orphan*/  default_start_limit_burst; int /*<<< orphan*/  default_start_limit_interval; int /*<<< orphan*/  default_restart_usec; int /*<<< orphan*/  default_timeout_abort_set; int /*<<< orphan*/  default_timeout_abort_usec; int /*<<< orphan*/  default_timeout_stop_usec; int /*<<< orphan*/  default_timeout_start_usec; int /*<<< orphan*/  default_std_error; int /*<<< orphan*/  default_std_output; int /*<<< orphan*/  default_timer_accuracy_usec; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  arg_default_blockio_accounting ; 
 scalar_t__ arg_default_cpu_accounting ; 
 int /*<<< orphan*/  arg_default_environment ; 
 int /*<<< orphan*/  arg_default_io_accounting ; 
 int /*<<< orphan*/  arg_default_ip_accounting ; 
 int /*<<< orphan*/  arg_default_memory_accounting ; 
 int /*<<< orphan*/  arg_default_oom_policy ; 
 int /*<<< orphan*/  arg_default_restart_usec ; 
 int /*<<< orphan*/  arg_default_rlimit ; 
 int /*<<< orphan*/  arg_default_start_limit_burst ; 
 int /*<<< orphan*/  arg_default_start_limit_interval ; 
 int /*<<< orphan*/  arg_default_std_error ; 
 int /*<<< orphan*/  arg_default_std_output ; 
 int /*<<< orphan*/  arg_default_tasks_accounting ; 
 int /*<<< orphan*/  arg_default_tasks_max ; 
 int /*<<< orphan*/  arg_default_timeout_abort_set ; 
 int /*<<< orphan*/  arg_default_timeout_abort_usec ; 
 int /*<<< orphan*/  arg_default_timeout_start_usec ; 
 int /*<<< orphan*/  arg_default_timeout_stop_usec ; 
 int /*<<< orphan*/  arg_default_timer_accuracy_usec ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 scalar_t__ cpu_accounting_is_cheap () ; 
 int /*<<< orphan*/  manager_default_environment (TYPE_1__*) ; 
 int /*<<< orphan*/  manager_set_default_rlimits (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  manager_transient_environment_add (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_manager_defaults(Manager *m) {

        assert(m);

        /* Propagates the various default unit property settings into the manager object, i.e. properties that do not
         * affect the manager itself, but are just what newly allocated units will have set if they haven't set
         * anything else. (Also see set_manager_settings() for the settings that affect the manager's own behaviour) */

        m->default_timer_accuracy_usec = arg_default_timer_accuracy_usec;
        m->default_std_output = arg_default_std_output;
        m->default_std_error = arg_default_std_error;
        m->default_timeout_start_usec = arg_default_timeout_start_usec;
        m->default_timeout_stop_usec = arg_default_timeout_stop_usec;
        m->default_timeout_abort_usec = arg_default_timeout_abort_usec;
        m->default_timeout_abort_set = arg_default_timeout_abort_set;
        m->default_restart_usec = arg_default_restart_usec;
        m->default_start_limit_interval = arg_default_start_limit_interval;
        m->default_start_limit_burst = arg_default_start_limit_burst;

        /* On 4.15+ with unified hierarchy, CPU accounting is essentially free as it doesn't require the CPU
         * controller to be enabled, so the default is to enable it unless we got told otherwise. */
        if (arg_default_cpu_accounting >= 0)
                m->default_cpu_accounting = arg_default_cpu_accounting;
        else
                m->default_cpu_accounting = cpu_accounting_is_cheap();

        m->default_io_accounting = arg_default_io_accounting;
        m->default_ip_accounting = arg_default_ip_accounting;
        m->default_blockio_accounting = arg_default_blockio_accounting;
        m->default_memory_accounting = arg_default_memory_accounting;
        m->default_tasks_accounting = arg_default_tasks_accounting;
        m->default_tasks_max = arg_default_tasks_max;
        m->default_oom_policy = arg_default_oom_policy;

        (void) manager_set_default_rlimits(m, arg_default_rlimit);

        (void) manager_default_environment(m);
        (void) manager_transient_environment_add(m, arg_default_environment);
}