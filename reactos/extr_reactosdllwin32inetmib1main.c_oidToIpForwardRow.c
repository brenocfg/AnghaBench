#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  dwForwardDest; } ;
typedef  TYPE_1__ MIB_IPFORWARDROW ;
typedef  int /*<<< orphan*/  AsnObjectIdentifier ;

/* Variables and functions */
 int /*<<< orphan*/  oidToIpAddr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void oidToIpForwardRow(AsnObjectIdentifier *oid, void *dst)
{
    MIB_IPFORWARDROW *row = dst;

    row->dwForwardDest = oidToIpAddr(oid);
}