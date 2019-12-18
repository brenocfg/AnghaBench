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
struct TYPE_4__ {scalar_t__ load_state; int /*<<< orphan*/  manager; int /*<<< orphan*/  pids; } ;
typedef  int /*<<< orphan*/  Scope ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  MANAGER_IS_RELOADING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPECIAL_INIT_SCOPE ; 
 TYPE_1__* UNIT (int /*<<< orphan*/ *) ; 
 scalar_t__ UNIT_LOADED ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  log_unit_error (TYPE_1__*,char*) ; 
 scalar_t__ set_isempty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unit_has_name (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int scope_verify(Scope *s) {
        assert(s);
        assert(UNIT(s)->load_state == UNIT_LOADED);

        if (set_isempty(UNIT(s)->pids) &&
            !MANAGER_IS_RELOADING(UNIT(s)->manager) &&
            !unit_has_name(UNIT(s), SPECIAL_INIT_SCOPE)) {
                log_unit_error(UNIT(s), "Scope has no PIDs. Refusing.");
                return -ENOENT;
        }

        return 0;
}