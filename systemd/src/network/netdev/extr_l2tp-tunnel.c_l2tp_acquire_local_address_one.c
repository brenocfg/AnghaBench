#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  union in_addr_union {int dummy; } in_addr_union ;
struct TYPE_6__ {scalar_t__ family; union in_addr_union in_addr; int /*<<< orphan*/  flags; int /*<<< orphan*/  in_addr_peer; } ;
struct TYPE_5__ {scalar_t__ family; scalar_t__ local_address_type; } ;
typedef  TYPE_1__ L2tpTunnel ;
typedef  TYPE_2__ Address ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ FLAGS_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFA_F_PERMANENT ; 
 scalar_t__ NETDEV_L2TP_LOCAL_ADDRESS_DYNAMIC ; 
 scalar_t__ NETDEV_L2TP_LOCAL_ADDRESS_STATIC ; 
 scalar_t__ in_addr_is_null (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int l2tp_acquire_local_address_one(L2tpTunnel *t, Address *a, union in_addr_union *ret) {
        if (a->family != t->family)
                return -EINVAL;

        if (in_addr_is_null(a->family, &a->in_addr_peer) <= 0)
                return -EINVAL;

        if (t->local_address_type == NETDEV_L2TP_LOCAL_ADDRESS_STATIC &&
            !FLAGS_SET(a->flags, IFA_F_PERMANENT))
                return -EINVAL;

        if (t->local_address_type == NETDEV_L2TP_LOCAL_ADDRESS_DYNAMIC &&
            FLAGS_SET(a->flags, IFA_F_PERMANENT))
                return -EINVAL;

        *ret = a->in_addr;
        return 0;
}