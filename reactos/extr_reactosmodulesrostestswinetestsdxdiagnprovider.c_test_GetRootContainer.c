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
typedef  int /*<<< orphan*/  IDxDiagProvider ;
typedef  int /*<<< orphan*/  IDxDiagContainer ;
typedef  scalar_t__ HRESULT ;
typedef  TYPE_1__ DXDIAG_INIT_PARAMS ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_DxDiagProvider ; 
 scalar_t__ CO_E_NOTINITIALIZED ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DXDIAG_DX9_SDK_VERSION ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IDxDiagContainer_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IDxDiagProvider_GetRootContainer (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ IDxDiagProvider_Initialize (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  IDxDiagProvider_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IDxDiagProvider ; 
 scalar_t__ REGDB_E_CLASSNOTREG ; 
 scalar_t__ S_OK ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  trace (char*,scalar_t__) ; 

__attribute__((used)) static void test_GetRootContainer(void)
{
    HRESULT hr;
    IDxDiagProvider *pddp;
    IDxDiagContainer *pddc, *pddc2;
    DXDIAG_INIT_PARAMS params;

    hr = CoCreateInstance(&CLSID_DxDiagProvider, NULL, CLSCTX_INPROC_SERVER,
                          &IID_IDxDiagProvider, (LPVOID*)&pddp);
    ok(hr == S_OK ||
       broken(hr == REGDB_E_CLASSNOTREG), /* Clean W2K3 */
       "Creating a IDxDiagProvider instance failed with %x\n", hr);
    if (FAILED(hr))
    {
        skip("Failed to create a IDxDiagProvider instance\n");
        return;
    }

    /* Test calling IDxDiagProvider::GetRootContainer before initialization. */
    hr = IDxDiagProvider_GetRootContainer(pddp, NULL);
    ok(hr == CO_E_NOTINITIALIZED,
       "Expected IDxDiagProvider::GetRootContainer to return CO_E_NOTINITIALIZED, got %x\n", hr);

    hr = IDxDiagProvider_GetRootContainer(pddp, &pddc);
    ok(hr == CO_E_NOTINITIALIZED,
       "Expected IDxDiagProvider::GetRootContainer to return CO_E_NOTINITIALIZED, got %x\n", hr);

    params.dwSize = sizeof(params);
    params.dwDxDiagHeaderVersion = DXDIAG_DX9_SDK_VERSION;
    params.bAllowWHQLChecks = FALSE;
    params.pReserved = NULL;
    hr = IDxDiagProvider_Initialize(pddp, &params);
    ok(hr == S_OK, "Expected IDxDiagProvider::Initialize to return S_OK, got %x\n", hr);
    if (FAILED(hr))
    {
        skip("IDxDiagProvider::Initialize failed\n");
        IDxDiagProvider_Release(pddp);
        return;
    }

    /* Passing NULL causes a crash on Windows. */
    if (0)
    {
        hr = IDxDiagProvider_GetRootContainer(pddp, NULL);
        trace("IDxDiagProvider::GetRootContainer returned %x\n", hr);
    }

    hr = IDxDiagProvider_GetRootContainer(pddp, &pddc);
    ok(hr == S_OK, "Expected IDxDiagProvider::GetRootContainer to return S_OK, got %x\n", hr);

    /* IDxDiagProvider::GetRootContainer creates new instances of the root
     * container rather than maintain a static root container. */
    hr = IDxDiagProvider_GetRootContainer(pddp, &pddc2);
    ok(hr == S_OK, "Expected IDxDiagProvider::GetRootContainer to return S_OK, got %x\n", hr);
    ok(pddc != pddc2, "Expected the two pointers (%p vs. %p) to be unequal\n", pddc, pddc2);

    IDxDiagContainer_Release(pddc2);
    IDxDiagContainer_Release(pddc);
    IDxDiagProvider_Release(pddp);
}