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
struct TYPE_3__ {int /*<<< orphan*/  ddRVal; int /*<<< orphan*/  dwFlags; } ;
typedef  int /*<<< orphan*/ * PDD_WAITFORVERTICALBLANKDATA ;
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  TYPE_1__ DDHAL_WAITFORVERTICALBLANKDATA ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DDHAL_DRIVER_HANDLED ; 
 int /*<<< orphan*/  DDHAL_DRIVER_NOTHANDLED ; 
 int /*<<< orphan*/  DDWAITVB_I_TESTVB ; 
 int /*<<< orphan*/  DD_OK ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  OsThunkDdWaitForVerticalBlank (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlZeroMemory (TYPE_1__*,int) ; 
 int /*<<< orphan*/  show_status (int,char*) ; 
 int /*<<< orphan*/  testing_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  testing_noteq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 

void
test_NtGdiDdWaitForVerticalBlank(HANDLE hDirectDrawLocal)
{
    int fails=0;
    BOOL retValue=FALSE;
    DDHAL_WAITFORVERTICALBLANKDATA pDdWaitForVerticalBlankData;

    RtlZeroMemory(&pDdWaitForVerticalBlankData,sizeof(DDHAL_WAITFORVERTICALBLANKDATA));

    retValue = OsThunkDdWaitForVerticalBlank(NULL,NULL);
    testing_eq(retValue, DDHAL_DRIVER_HANDLED,fails,"1. NtGdiDdWaitForVerticalBlank(NULL,NULL);\0");

    retValue = OsThunkDdWaitForVerticalBlank(hDirectDrawLocal,NULL);
    testing_eq(retValue, DDHAL_DRIVER_HANDLED,fails,"2. NtGdiDdWaitForVerticalBlank(hDirectDrawLocal,NULL);\0");

    retValue = OsThunkDdWaitForVerticalBlank(hDirectDrawLocal,(PDD_WAITFORVERTICALBLANKDATA)&pDdWaitForVerticalBlankData);
    testing_eq(retValue, DDHAL_DRIVER_HANDLED,fails,"3. NtGdiDdWaitForVerticalBlank(hDirectDrawLocal,NULL);\0");
    testing_eq(pDdWaitForVerticalBlankData.ddRVal, DD_OK,fails,"4. NtGdiDdWaitForVerticalBlank(hDirectDrawLocal,NULL);\0");

    RtlZeroMemory(&pDdWaitForVerticalBlankData,sizeof(DDHAL_WAITFORVERTICALBLANKDATA));
    pDdWaitForVerticalBlankData.dwFlags = DDWAITVB_I_TESTVB;
    retValue = OsThunkDdWaitForVerticalBlank(hDirectDrawLocal,(PDD_WAITFORVERTICALBLANKDATA)&pDdWaitForVerticalBlankData);

    testing_eq(retValue, DDHAL_DRIVER_NOTHANDLED,fails,"5. NtGdiDdWaitForVerticalBlank(hDirectDrawLocal,NULL);\0");
    testing_noteq(pDdWaitForVerticalBlankData.ddRVal, DD_OK,fails,"6. NtGdiDdWaitForVerticalBlank(hDirectDrawLocal,NULL);\0");

    retValue = OsThunkDdWaitForVerticalBlank(hDirectDrawLocal,(PDD_WAITFORVERTICALBLANKDATA)&pDdWaitForVerticalBlankData);

    show_status(fails, "NtGdiDdWaitForVerticalBlank\0");
}