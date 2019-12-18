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
struct TYPE_7__ {int /*<<< orphan*/ * link; } ;
typedef  int /*<<< orphan*/  Link ;
typedef  TYPE_1__ Address ;

/* Variables and functions */
 int /*<<< orphan*/  address_free (TYPE_1__*) ; 
 int address_is_ready (TYPE_1__*) ; 
 int address_release (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  link_check_ready (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  link_update_operstate (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  log_link_warning_errno (int /*<<< orphan*/ *,int,char*) ; 

int address_drop(Address *address) {
        Link *link;
        bool ready;
        int r;

        assert(address);

        ready = address_is_ready(address);
        link = address->link;

        r = address_release(address);
        if (r < 0)
                log_link_warning_errno(link, r, "Failed to disable IP masquerading, ignoring: %m");

        address_free(address);

        link_update_operstate(link, true);

        if (link && !ready)
                link_check_ready(link);

        return 0;
}