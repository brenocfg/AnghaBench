#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  links_by_name; } ;
typedef  int /*<<< orphan*/  Link ;
typedef  TYPE_1__ Context ;

/* Variables and functions */
 int /*<<< orphan*/ * hashmap_get (int /*<<< orphan*/ ,char const*) ; 

Link *link_get(Context *context, const char *ifname) {
        return hashmap_get(context->links_by_name, ifname);
}