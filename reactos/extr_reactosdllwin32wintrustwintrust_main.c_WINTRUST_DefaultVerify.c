#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct wintrust_step {int dummy; } ;
struct TYPE_11__ {TYPE_3__* hWVTStateData; } ;
typedef  TYPE_2__ WINTRUST_DATA ;
struct TYPE_10__ {TYPE_3__* pPDSip; } ;
struct TYPE_12__ {struct TYPE_12__* psPfns; TYPE_1__ u; struct TYPE_12__* padwTrustStepErrors; int /*<<< orphan*/  dwRegPolicySettings; int /*<<< orphan*/ * pgActionID; scalar_t__ hWndParent; TYPE_2__* pWintrustData; } ;
typedef  int /*<<< orphan*/  LONG ;
typedef  scalar_t__ HWND ;
typedef  int /*<<< orphan*/  GUID ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_3__ CRYPT_PROVIDER_DATA ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_OUTOFMEMORY ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 scalar_t__ GetDesktopWindow () ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  WINTRUST_AddTrustStepsFromFunctions (struct wintrust_step*,TYPE_3__*) ; 
 TYPE_3__* WINTRUST_AllocateProviderData () ; 
 int /*<<< orphan*/  WINTRUST_ExecuteSteps (struct wintrust_step*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  WINTRUST_Free (TYPE_3__*) ; 
 int /*<<< orphan*/  WintrustGetRegPolicyFlags (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WintrustLoadFunctionPointers (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  debugstr_guid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static LONG WINTRUST_DefaultVerify(HWND hwnd, GUID *actionID,
 WINTRUST_DATA *data)
{
    DWORD err = ERROR_SUCCESS, numSteps = 0;
    CRYPT_PROVIDER_DATA *provData;
    BOOL ret;
    struct wintrust_step verifySteps[5];

    TRACE("(%p, %s, %p)\n", hwnd, debugstr_guid(actionID), data);

    provData = WINTRUST_AllocateProviderData();
    if (!provData)
        return ERROR_OUTOFMEMORY;

    ret = WintrustLoadFunctionPointers(actionID, provData->psPfns);
    if (!ret)
    {
        err = GetLastError();
        goto error;
    }

    data->hWVTStateData = provData;
    provData->pWintrustData = data;
    if (hwnd == INVALID_HANDLE_VALUE)
        provData->hWndParent = GetDesktopWindow();
    else
        provData->hWndParent = hwnd;
    provData->pgActionID = actionID;
    WintrustGetRegPolicyFlags(&provData->dwRegPolicySettings);

    numSteps = WINTRUST_AddTrustStepsFromFunctions(verifySteps,
     provData->psPfns);
    err = WINTRUST_ExecuteSteps(verifySteps, numSteps, provData);
    goto done;

error:
    if (provData)
    {
        WINTRUST_Free(provData->padwTrustStepErrors);
        WINTRUST_Free(provData->u.pPDSip);
        WINTRUST_Free(provData->psPfns);
        WINTRUST_Free(provData);
    }
done:
    TRACE("returning %08x\n", err);
    return err;
}