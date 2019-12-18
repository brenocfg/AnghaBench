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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  sd_event_source ;
struct TYPE_5__ {int /*<<< orphan*/  link; } ;
typedef  TYPE_1__ Route ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  log_warning_errno (int,char*) ; 
 int /*<<< orphan*/  route_free (TYPE_1__*) ; 
 int route_remove (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int route_expire_handler(sd_event_source *s, uint64_t usec, void *userdata) {
        Route *route = userdata;
        int r;

        assert(route);

        r = route_remove(route, route->link, NULL);
        if (r < 0)
                log_warning_errno(r, "Could not remove route: %m");
        else
                route_free(route);

        return 1;
}