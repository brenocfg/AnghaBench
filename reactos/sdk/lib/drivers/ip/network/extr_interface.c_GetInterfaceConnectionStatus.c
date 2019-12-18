#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_5__ {TYPE_1__* Context; } ;
struct TYPE_4__ {scalar_t__ State; } ;
typedef  int /*<<< orphan*/ * PULONG ;
typedef  TYPE_1__* PLAN_ADAPTER ;
typedef  TYPE_2__* PIP_INTERFACE ;

/* Variables and functions */
 scalar_t__ LAN_STATE_STARTED ; 
 int /*<<< orphan*/  MIB_IF_OPER_STATUS_DISCONNECTED ; 
 int /*<<< orphan*/  MIB_IF_OPER_STATUS_OPERATIONAL ; 

VOID GetInterfaceConnectionStatus(PIP_INTERFACE Interface, PULONG Result)
{
    PLAN_ADAPTER Adapter = Interface->Context;

    /* Loopback has no adapter context */
    if (Adapter == NULL || Adapter->State == LAN_STATE_STARTED) {
        *Result = MIB_IF_OPER_STATUS_OPERATIONAL;
    }
    else {
        *Result = MIB_IF_OPER_STATUS_DISCONNECTED;
    }
}