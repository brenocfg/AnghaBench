#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {struct TYPE_10__* Flink; } ;
struct TYPE_9__ {TYPE_3__ RegistryPorts; } ;
struct TYPE_8__ {int /*<<< orphan*/  pwszPortName; } ;
typedef  TYPE_1__* PLOCALMON_PORT ;
typedef  TYPE_2__* PLOCALMON_HANDLE ;
typedef  TYPE_3__* PLIST_ENTRY ;
typedef  int /*<<< orphan*/  PCWSTR ;

/* Variables and functions */
 TYPE_1__* CONTAINING_RECORD (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Entry ; 
 int /*<<< orphan*/  LOCALMON_PORT ; 
 scalar_t__ wcscmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static PLOCALMON_PORT
_FindPort(PLOCALMON_HANDLE pLocalmon, PCWSTR pwszPortName)
{
    PLIST_ENTRY pEntry;
    PLOCALMON_PORT pPort;

    for (pEntry = pLocalmon->RegistryPorts.Flink; pEntry != &pLocalmon->RegistryPorts; pEntry = pEntry->Flink)
    {
        pPort = CONTAINING_RECORD(pEntry, LOCALMON_PORT, Entry);

        if (wcscmp(pPort->pwszPortName, pwszPortName) == 0)
            return pPort;
    }

    return NULL;
}