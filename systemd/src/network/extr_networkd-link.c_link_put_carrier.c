#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  ifindex; } ;
typedef  TYPE_1__ Link ;
typedef  int /*<<< orphan*/  Hashmap ;

/* Variables and functions */
 int /*<<< orphan*/  INT_TO_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int hashmap_ensure_allocated (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ hashmap_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int hashmap_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int link_put_carrier(Link *link, Link *carrier, Hashmap **h) {
        int r;

        assert(link);
        assert(carrier);

        if (link == carrier)
                return 0;

        if (hashmap_get(*h, INT_TO_PTR(carrier->ifindex)))
                return 0;

        r = hashmap_ensure_allocated(h, NULL);
        if (r < 0)
                return r;

        r = hashmap_put(*h, INT_TO_PTR(carrier->ifindex), carrier);
        if (r < 0)
                return r;

        return 0;
}