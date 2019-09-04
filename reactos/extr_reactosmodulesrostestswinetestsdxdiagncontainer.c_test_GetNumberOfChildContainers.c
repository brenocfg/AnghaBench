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
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ E_INVALIDARG ; 
 scalar_t__ IDxDiagContainer_GetNumberOfChildContainers (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  IDxDiagContainer_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDxDiagProvider_Release (int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  create_root_IDxDiagContainer () ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  pddc ; 
 int /*<<< orphan*/  pddp ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void test_GetNumberOfChildContainers(void)
{
    HRESULT hr;
    DWORD count;

    if (!create_root_IDxDiagContainer())
    {
        skip("Unable to create the root IDxDiagContainer\n");
        return;
    }

    hr = IDxDiagContainer_GetNumberOfChildContainers(pddc, NULL);
    ok(hr == E_INVALIDARG,
       "Expected IDxDiagContainer::GetNumberOfChildContainers to return E_INVALIDARG, got 0x%08x\n", hr);

    hr = IDxDiagContainer_GetNumberOfChildContainers(pddc, &count);
    ok(hr == S_OK,
       "Expected IDxDiagContainer::GetNumberOfChildContainers to return S_OK, got 0x%08x\n", hr);
    if (hr == S_OK)
        ok(count != 0, "Expected the number of child containers for the root container to be non-zero\n");

    IDxDiagContainer_Release(pddc);
    IDxDiagProvider_Release(pddp);
}