#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  nexthops_foreign; int /*<<< orphan*/  nexthops; } ;
typedef  TYPE_1__ NextHop ;
typedef  TYPE_1__ Link ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 TYPE_1__* set_get (int /*<<< orphan*/ ,TYPE_1__*) ; 

int nexthop_get(Link *link, NextHop *in, NextHop **ret) {
        NextHop *existing;

        assert(link);
        assert(in);

        existing = set_get(link->nexthops, in);
        if (existing) {
                if (ret)
                        *ret = existing;
                return 1;
        }

        existing = set_get(link->nexthops_foreign, in);
        if (existing) {
                if (ret)
                        *ret = existing;
                return 0;
        }

        return -ENOENT;
}