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
struct TYPE_4__ {int /*<<< orphan*/  transient_environment; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int log_oom () ; 
 int /*<<< orphan*/  sanitize_environment (char**) ; 
 char** strv_env_merge (int,int /*<<< orphan*/ ,char**) ; 
 int strv_free_and_replace (int /*<<< orphan*/ ,char**) ; 
 scalar_t__ strv_isempty (char**) ; 

int manager_transient_environment_add(Manager *m, char **plus) {
        char **a;

        assert(m);

        if (strv_isempty(plus))
                return 0;

        a = strv_env_merge(2, m->transient_environment, plus);
        if (!a)
                return log_oom();

        sanitize_environment(a);

        return strv_free_and_replace(m->transient_environment, a);
}