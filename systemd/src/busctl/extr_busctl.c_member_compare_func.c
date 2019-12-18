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
struct TYPE_7__ {int /*<<< orphan*/  name; struct TYPE_7__ const* type; int /*<<< orphan*/  interface; } ;
typedef  TYPE_1__ Member ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__ const*) ; 
 int strcmp (TYPE_1__ const*,TYPE_1__ const*) ; 
 int strcmp_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int member_compare_func(const Member *x, const Member *y) {
        int d;

        assert(x);
        assert(y);
        assert(x->type);
        assert(y->type);

        d = strcmp_ptr(x->interface, y->interface);
        if (d != 0)
                return d;

        d = strcmp(x->type, y->type);
        if (d != 0)
                return d;

        return strcmp_ptr(x->name, y->name);
}