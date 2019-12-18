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
struct TYPE_4__ {char* cgroup_path; } ;
typedef  TYPE_1__ Unit ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_LEVEL_CGROUP_WRITE (int) ; 
 int /*<<< orphan*/  NEWLINE ; 
 int cg_set_attribute (char const*,char*,char const*,char const*) ; 
 scalar_t__ isempty (char*) ; 
 int /*<<< orphan*/  log_unit_full (TYPE_1__*,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,char*,int,char const*) ; 
 scalar_t__ strcspn (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strna (char const*) ; 

__attribute__((used)) static int set_attribute_and_warn(Unit *u, const char *controller, const char *attribute, const char *value) {
        int r;

        r = cg_set_attribute(controller, u->cgroup_path, attribute, value);
        if (r < 0)
                log_unit_full(u, LOG_LEVEL_CGROUP_WRITE(r), r, "Failed to set '%s' attribute on '%s' to '%.*s': %m",
                              strna(attribute), isempty(u->cgroup_path) ? "/" : u->cgroup_path, (int) strcspn(value, NEWLINE), value);

        return r;
}