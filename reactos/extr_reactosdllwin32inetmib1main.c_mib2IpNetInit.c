#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  MIB_IPNETTABLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_INSUFFICIENT_BUFFER ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetIpNetTable (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ipNetTable ; 

__attribute__((used)) static void mib2IpNetInit(void)
{
    DWORD size = 0, ret = GetIpNetTable(NULL, &size, FALSE);

    if (ret == ERROR_INSUFFICIENT_BUFFER)
    {
        MIB_IPNETTABLE *table = HeapAlloc(GetProcessHeap(), 0, size);
        if (table)
        {
            if (!GetIpNetTable(table, &size, FALSE)) ipNetTable = table;
            else HeapFree(GetProcessHeap(), 0, table );
        }
    }
}