#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_3__* hWVTStateData; } ;
typedef  TYPE_2__ WINTRUST_DATA ;
struct TYPE_7__ {TYPE_3__* pPDSip; } ;
struct TYPE_9__ {struct TYPE_9__* psPfns; TYPE_1__ u; struct TYPE_9__* padwTrustStepErrors; int /*<<< orphan*/  (* pfnCleanupPolicy ) (TYPE_3__*) ;} ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  GUID ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_3__ CRYPT_PROVIDER_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  WINTRUST_Free (TYPE_3__*) ; 
 int /*<<< orphan*/  debugstr_guid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

__attribute__((used)) static LONG WINTRUST_DefaultClose(HWND hwnd, GUID *actionID,
 WINTRUST_DATA *data)
{
    DWORD err = ERROR_SUCCESS;
    CRYPT_PROVIDER_DATA *provData = data->hWVTStateData;

    TRACE("(%p, %s, %p)\n", hwnd, debugstr_guid(actionID), data);

    if (provData)
    {
        if (provData->psPfns->pfnCleanupPolicy)
            err = provData->psPfns->pfnCleanupPolicy(provData);

        WINTRUST_Free(provData->padwTrustStepErrors);
        WINTRUST_Free(provData->u.pPDSip);
        WINTRUST_Free(provData->psPfns);
        WINTRUST_Free(provData);
        data->hWVTStateData = NULL;
    }
    TRACE("returning %08x\n", err);
    return err;
}