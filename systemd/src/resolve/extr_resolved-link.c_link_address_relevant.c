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
struct TYPE_4__ {int flags; scalar_t__ scope; } ;
typedef  TYPE_1__ LinkAddress ;

/* Variables and functions */
 int IFA_F_DEPRECATED ; 
 int IFA_F_TENTATIVE ; 
 scalar_t__ RT_SCOPE_HOST ; 
 scalar_t__ RT_SCOPE_LINK ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

bool link_address_relevant(LinkAddress *a, bool local_multicast) {
        assert(a);

        if (a->flags & (IFA_F_DEPRECATED|IFA_F_TENTATIVE))
                return false;

        if (a->scope >= (local_multicast ? RT_SCOPE_HOST : RT_SCOPE_LINK))
                return false;

        return true;
}