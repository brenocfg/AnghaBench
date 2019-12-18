#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int umask; int syslog_priority; int syslog_level_prefix; int ignore_sigpipe; int log_level_max; int /*<<< orphan*/  numa_policy; scalar_t__ restrict_namespaces; int /*<<< orphan*/  capability_bounding_set; int /*<<< orphan*/  timeout_clean_usec; TYPE_1__* directories; int /*<<< orphan*/  personality; int /*<<< orphan*/  timer_slack_nsec; int /*<<< orphan*/  cpu_sched_policy; int /*<<< orphan*/  ioprio; } ;
struct TYPE_5__ {int mode; } ;
typedef  size_t ExecDirectoryType ;
typedef  TYPE_2__ ExecContext ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_ALL ; 
 int /*<<< orphan*/  IOPRIO_CLASS_BE ; 
 int /*<<< orphan*/  IOPRIO_PRIO_VALUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int LOG_DAEMON ; 
 int LOG_INFO ; 
 scalar_t__ NAMESPACE_FLAGS_ALL ; 
 scalar_t__ NAMESPACE_FLAGS_INITIAL ; 
 int /*<<< orphan*/  NSEC_INFINITY ; 
 int /*<<< orphan*/  PERSONALITY_INVALID ; 
 int /*<<< orphan*/  SCHED_OTHER ; 
 int /*<<< orphan*/  USEC_INFINITY ; 
 size_t _EXEC_DIRECTORY_TYPE_MAX ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  assert_cc (int) ; 
 int /*<<< orphan*/  numa_policy_reset (int /*<<< orphan*/ *) ; 

void exec_context_init(ExecContext *c) {
        ExecDirectoryType i;

        assert(c);

        c->umask = 0022;
        c->ioprio = IOPRIO_PRIO_VALUE(IOPRIO_CLASS_BE, 0);
        c->cpu_sched_policy = SCHED_OTHER;
        c->syslog_priority = LOG_DAEMON|LOG_INFO;
        c->syslog_level_prefix = true;
        c->ignore_sigpipe = true;
        c->timer_slack_nsec = NSEC_INFINITY;
        c->personality = PERSONALITY_INVALID;
        for (i = 0; i < _EXEC_DIRECTORY_TYPE_MAX; i++)
                c->directories[i].mode = 0755;
        c->timeout_clean_usec = USEC_INFINITY;
        c->capability_bounding_set = CAP_ALL;
        assert_cc(NAMESPACE_FLAGS_INITIAL != NAMESPACE_FLAGS_ALL);
        c->restrict_namespaces = NAMESPACE_FLAGS_INITIAL;
        c->log_level_max = -1;
        numa_policy_reset(&c->numa_policy);
}