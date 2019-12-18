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
struct TYPE_4__ {int /*<<< orphan*/  routes_foreign; } ;
typedef  int /*<<< orphan*/  Route ;
typedef  TYPE_1__ Link ;

/* Variables and functions */
 int route_add_internal (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

int route_add_foreign(Link *link, Route *in, Route **ret) {
        return route_add_internal(link, &link->routes_foreign, in, ret);
}