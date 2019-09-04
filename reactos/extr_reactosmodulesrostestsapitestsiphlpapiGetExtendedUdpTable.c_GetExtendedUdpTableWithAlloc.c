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
typedef  int /*<<< orphan*/  UDP_TABLE_CLASS ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_INSUFFICIENT_BUFFER ; 
 scalar_t__ ERROR_OUTOFMEMORY ; 
 scalar_t__ GetExtendedUdpTable (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ NO_ERROR ; 

__attribute__((used)) static DWORD GetExtendedUdpTableWithAlloc(PVOID *UdpTable, BOOL Order, DWORD Family, UDP_TABLE_CLASS Class)
{
    DWORD ret;
    DWORD Size = 0;

    *UdpTable = NULL;

    ret = GetExtendedUdpTable(*UdpTable, &Size, Order, Family, Class, 0);
    if (ret == ERROR_INSUFFICIENT_BUFFER)
    {
        *UdpTable = HeapAlloc(GetProcessHeap(), 0, Size);
        if (*UdpTable == NULL)
        {
            return ERROR_OUTOFMEMORY;
        }

        ret = GetExtendedUdpTable(*UdpTable, &Size, Order, Family, Class, 0);
        if (ret != NO_ERROR)
        {
            HeapFree(GetProcessHeap(), 0, *UdpTable);
            *UdpTable = NULL;
        }
    }

    return ret;
}