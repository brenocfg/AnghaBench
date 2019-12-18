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
typedef  int /*<<< orphan*/  params ;
struct TYPE_3__ {int dwSize; int /*<<< orphan*/ * pReserved; int /*<<< orphan*/  bAllowWHQLChecks; int /*<<< orphan*/  dwDxDiagHeaderVersion; } ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ DXDIAG_INIT_PARAMS ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_DxDiagProvider ; 
 int /*<<< orphan*/  CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DXDIAG_DX9_SDK_VERSION ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IDxDiagProvider_GetRootContainer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDxDiagProvider_Initialize (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  IDxDiagProvider_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IDxDiagProvider ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  pddc ; 
 int /*<<< orphan*/  pddp ; 

__attribute__((used)) static BOOL create_root_IDxDiagContainer(void)
{
    HRESULT hr;
    DXDIAG_INIT_PARAMS params;

    hr = CoCreateInstance(&CLSID_DxDiagProvider, NULL, CLSCTX_INPROC_SERVER,
                          &IID_IDxDiagProvider, (LPVOID*)&pddp);
    if (SUCCEEDED(hr))
    {
        params.dwSize = sizeof(params);
        params.dwDxDiagHeaderVersion = DXDIAG_DX9_SDK_VERSION;
        params.bAllowWHQLChecks = FALSE;
        params.pReserved = NULL;
        hr = IDxDiagProvider_Initialize(pddp, &params);
        if (SUCCEEDED(hr))
        {
            hr = IDxDiagProvider_GetRootContainer(pddp, &pddc);
            if (SUCCEEDED(hr))
                return TRUE;
        }
        IDxDiagProvider_Release(pddp);
    }
    return FALSE;
}