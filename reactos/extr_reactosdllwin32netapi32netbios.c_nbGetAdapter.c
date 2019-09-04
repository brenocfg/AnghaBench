#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UCHAR ;
struct TYPE_5__ {size_t tableSize; TYPE_1__* table; } ;
struct TYPE_4__ {scalar_t__ transport_id; scalar_t__ transport; } ;
typedef  TYPE_1__ NetBIOSAdapter ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,...) ; 
 TYPE_3__ gNBTable ; 

__attribute__((used)) static NetBIOSAdapter *nbGetAdapter(UCHAR lana)
{
    NetBIOSAdapter *ret = NULL;

    TRACE(": lana %d, num allocated adapters %d\n", lana, gNBTable.tableSize);
    if (lana < gNBTable.tableSize && gNBTable.table[lana].transport_id != 0
     && gNBTable.table[lana].transport)
        ret = &gNBTable.table[lana];
    TRACE("returning %p\n", ret);
    return ret;
}