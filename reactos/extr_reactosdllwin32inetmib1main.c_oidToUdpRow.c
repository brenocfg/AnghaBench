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
struct TYPE_6__ {int idLength; int /*<<< orphan*/ * ids; } ;
struct TYPE_5__ {int /*<<< orphan*/  dwLocalPort; int /*<<< orphan*/  dwLocalAddr; } ;
typedef  TYPE_1__ MIB_UDPROW ;
typedef  TYPE_2__ AsnObjectIdentifier ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oidToIpAddr (TYPE_2__*) ; 

__attribute__((used)) static void oidToUdpRow(AsnObjectIdentifier *oid, void *dst)
{
    MIB_UDPROW *row = dst;

    assert(oid && oid->idLength >= 5);
    row->dwLocalAddr = oidToIpAddr(oid);
    row->dwLocalPort = oid->ids[4];
}