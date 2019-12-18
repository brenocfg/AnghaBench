#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Scope ;

/* Variables and functions */
 int /*<<< orphan*/  UNIT (int /*<<< orphan*/ *) ; 
 int scope_add_default_dependencies (int /*<<< orphan*/ *) ; 
 int unit_patch_contexts (int /*<<< orphan*/ ) ; 
 int unit_set_default_slice (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int scope_add_extras(Scope *s) {
        int r;

        r = unit_patch_contexts(UNIT(s));
        if (r < 0)
                return r;

        r = unit_set_default_slice(UNIT(s));
        if (r < 0)
                return r;

        return scope_add_default_dependencies(s);
}