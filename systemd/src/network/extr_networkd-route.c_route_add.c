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
struct TYPE_5__ {int /*<<< orphan*/  routes_foreign; int /*<<< orphan*/  routes; } ;
typedef  int /*<<< orphan*/  Route ;
typedef  TYPE_1__ Link ;

/* Variables and functions */
 int ENOENT ; 
 int route_add_internal (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int route_get (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  route_hash_ops ; 
 int set_ensure_allocated (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int set_put (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int route_add(Link *link, Route *in, Route **ret) {

        Route *route;
        int r;

        r = route_get(link, in, &route);
        if (r == -ENOENT) {
                /* Route does not exist, create a new one */
                r = route_add_internal(link, &link->routes, in, &route);
                if (r < 0)
                        return r;
        } else if (r == 0) {
                /* Take over a foreign route */
                r = set_ensure_allocated(&link->routes, &route_hash_ops);
                if (r < 0)
                        return r;

                r = set_put(link->routes, route);
                if (r < 0)
                        return r;

                set_remove(link->routes_foreign, route);
        } else if (r == 1) {
                /* Route exists, do nothing */
                ;
        } else
                return r;

        if (ret)
                *ret = route;

        return 0;
}