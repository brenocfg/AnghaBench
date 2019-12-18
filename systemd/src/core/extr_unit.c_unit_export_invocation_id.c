#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int exported_invocation_id; int /*<<< orphan*/  invocation_id_string; int /*<<< orphan*/  id; int /*<<< orphan*/  invocation_id; } ;
typedef  TYPE_1__ Unit ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int log_unit_debug_errno (TYPE_1__*,int,char*,char const*) ; 
 scalar_t__ sd_id128_is_null (int /*<<< orphan*/ ) ; 
 char* strjoina (char*,int /*<<< orphan*/ ) ; 
 int symlink_atomic (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int unit_export_invocation_id(Unit *u) {
        const char *p;
        int r;

        assert(u);

        if (u->exported_invocation_id)
                return 0;

        if (sd_id128_is_null(u->invocation_id))
                return 0;

        p = strjoina("/run/systemd/units/invocation:", u->id);
        r = symlink_atomic(u->invocation_id_string, p);
        if (r < 0)
                return log_unit_debug_errno(u, r, "Failed to create invocation ID symlink %s: %m", p);

        u->exported_invocation_id = true;
        return 0;
}