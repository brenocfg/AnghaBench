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
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_6__ {int /*<<< orphan*/  wDeviceID; int /*<<< orphan*/  lpstrAlias; int /*<<< orphan*/  lpstrElementName; } ;
struct TYPE_5__ {int /*<<< orphan*/  wDeviceID; void* lpstrAlias; void* lpstrElementName; } ;
typedef  TYPE_1__* LPWINE_MCIDRIVER ;
typedef  TYPE_2__* LPMCI_OPEN_PARMSW ;
typedef  int /*<<< orphan*/  DWORD_PTR ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int MCI_OPEN_ALIAS ; 
 int /*<<< orphan*/  MCI_OPEN_DRIVER ; 
 int MCI_OPEN_ELEMENT ; 
 int MCI_SendCommandFrom32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpyW (void*,int /*<<< orphan*/ ) ; 
 int strlenW (int /*<<< orphan*/ ) ; 

__attribute__((used)) static	DWORD	MCI_FinishOpen(LPWINE_MCIDRIVER wmd, LPMCI_OPEN_PARMSW lpParms,
			       DWORD dwParam)
{
    if (dwParam & MCI_OPEN_ELEMENT)
    {
        wmd->lpstrElementName = HeapAlloc(GetProcessHeap(),0,(strlenW(lpParms->lpstrElementName)+1) * sizeof(WCHAR));
        strcpyW( wmd->lpstrElementName, lpParms->lpstrElementName );
    }
    if (dwParam & MCI_OPEN_ALIAS)
    {
        wmd->lpstrAlias = HeapAlloc(GetProcessHeap(), 0, (strlenW(lpParms->lpstrAlias)+1) * sizeof(WCHAR));
        strcpyW( wmd->lpstrAlias, lpParms->lpstrAlias);
    }
    lpParms->wDeviceID = wmd->wDeviceID;

    return MCI_SendCommandFrom32(wmd->wDeviceID, MCI_OPEN_DRIVER, dwParam,
				 (DWORD_PTR)lpParms);
}