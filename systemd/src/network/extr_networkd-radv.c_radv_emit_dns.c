#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  manager; } ;
typedef  TYPE_1__ Link ;

/* Variables and functions */
 int /*<<< orphan*/  log_link_warning_errno (TYPE_1__*,int,char*) ; 
 TYPE_1__* manager_find_uplink (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int radv_set_dns (TYPE_1__*,TYPE_1__*) ; 
 int radv_set_domains (TYPE_1__*,TYPE_1__*) ; 

int radv_emit_dns(Link *link) {
        Link *uplink;
        int r;

        uplink = manager_find_uplink(link->manager, link);

        r = radv_set_dns(link, uplink);
        if (r < 0)
                log_link_warning_errno(link, r, "Could not set RA DNS: %m");

        r = radv_set_domains(link, uplink);
        if (r < 0)
                log_link_warning_errno(link, r, "Could not set RA Domains: %m");

        return 0;
}