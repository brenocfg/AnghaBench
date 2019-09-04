#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {struct TYPE_3__* Next; int /*<<< orphan*/ * DeviceInstanceData; int /*<<< orphan*/  Name; void* CardIndex; void* DeviceType; } ;
typedef  TYPE_1__* PDEVICE_LIST ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  void* DWORD ;
typedef  int /*<<< orphan*/  DEVICE_LIST ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*) ; 
 int /*<<< orphan*/  ERROR_NOT_ENOUGH_MEMORY ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  Heap ; 
 scalar_t__ HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  lstrcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lstrlen (int /*<<< orphan*/ ) ; 

BOOL AddDeviceToList(PDEVICE_LIST* pList, DWORD DeviceType, DWORD CardIndex,
                     LPWSTR Name)
{
    PDEVICE_LIST pNewDevice;

    DPRINT("AddDeviceToList()\n");

    pNewDevice = (PDEVICE_LIST) HeapAlloc(Heap, 0,
        sizeof(DEVICE_LIST) + lstrlen(Name) * sizeof(WCHAR));

    if ( !pNewDevice )
    {
        SetLastError(ERROR_NOT_ENOUGH_MEMORY);
        return FALSE;
    }
    
    pNewDevice->DeviceType = DeviceType;
    pNewDevice->CardIndex = CardIndex;
    lstrcpy(pNewDevice->Name, Name);
    pNewDevice->DeviceInstanceData = NULL;
    pNewDevice->Next = *pList;
    *pList = pNewDevice;
    
    DPRINT("Success!\n");

    return TRUE;
}