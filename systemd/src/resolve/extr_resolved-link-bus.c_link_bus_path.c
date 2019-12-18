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
struct TYPE_4__ {int /*<<< orphan*/  ifindex; } ;
typedef  TYPE_1__ Link ;

/* Variables and functions */
 int DECIMAL_STR_MAX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_1__ const*) ; 
 int sd_bus_path_encode (char*,char*,char**) ; 
 int /*<<< orphan*/  xsprintf (char*,char*,int /*<<< orphan*/ ) ; 

char *link_bus_path(const Link *link) {
        char *p, ifindex[DECIMAL_STR_MAX(link->ifindex)];
        int r;

        assert(link);

        xsprintf(ifindex, "%i", link->ifindex);

        r = sd_bus_path_encode("/org/freedesktop/resolve1/link", ifindex, &p);
        if (r < 0)
                return NULL;

        return p;
}