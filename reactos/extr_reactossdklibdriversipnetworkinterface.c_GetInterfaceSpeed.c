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
struct TYPE_5__ {int /*<<< orphan*/  Context; } ;
struct TYPE_4__ {int /*<<< orphan*/  Speed; } ;
typedef  int /*<<< orphan*/ * PUINT ;
typedef  TYPE_1__* PLAN_ADAPTER ;
typedef  TYPE_2__* PIP_INTERFACE ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  STATUS_SUCCESS ; 

NTSTATUS GetInterfaceSpeed( PIP_INTERFACE Interface, PUINT Speed ) {
    PLAN_ADAPTER IF = (PLAN_ADAPTER)Interface->Context;

    *Speed = IF->Speed;

    return STATUS_SUCCESS;
}