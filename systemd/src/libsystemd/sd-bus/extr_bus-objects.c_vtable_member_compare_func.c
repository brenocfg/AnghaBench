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
struct vtable_member {int /*<<< orphan*/  member; int /*<<< orphan*/  interface; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct vtable_member const*) ; 
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vtable_member_compare_func(const struct vtable_member *x, const struct vtable_member *y) {
        int r;

        assert(x);
        assert(y);

        r = strcmp(x->path, y->path);
        if (r != 0)
                return r;

        r = strcmp(x->interface, y->interface);
        if (r != 0)
                return r;

        return strcmp(x->member, y->member);
}