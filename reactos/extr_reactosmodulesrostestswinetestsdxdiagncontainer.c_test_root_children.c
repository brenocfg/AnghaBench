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
typedef  int /*<<< orphan*/  root_children ;
typedef  int /*<<< orphan*/  container ;
typedef  char WCHAR ;
typedef  int HRESULT ;
typedef  int DWORD ;

/* Variables and functions */
#define  DxDiag_DisplayDevices 129 
#define  DxDiag_SystemInfo 128 
 int E_INVALIDARG ; 
 scalar_t__ FAILED (int) ; 
 int IDxDiagContainer_EnumChildContainerNames (int /*<<< orphan*/ ,int,char*,int) ; 
 int IDxDiagContainer_GetNumberOfChildContainers (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  IDxDiagContainer_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDxDiagProvider_Release (int /*<<< orphan*/ ) ; 
 int S_OK ; 
 int /*<<< orphan*/  create_root_IDxDiagContainer () ; 
 int /*<<< orphan*/  lstrcmpW (char*,char const*) ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int /*<<< orphan*/  pddc ; 
 int /*<<< orphan*/  pddp ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  wine_dbgstr_w (char const*) ; 

__attribute__((used)) static void test_root_children(void)
{
    static const WCHAR DxDiag_DirectSound[] = {'D','x','D','i','a','g','_','D','i','r','e','c','t','S','o','u','n','d',0};
    static const WCHAR DxDiag_DirectMusic[] = {'D','x','D','i','a','g','_','D','i','r','e','c','t','M','u','s','i','c',0};
    static const WCHAR DxDiag_DirectInput[] = {'D','x','D','i','a','g','_','D','i','r','e','c','t','I','n','p','u','t',0};
    static const WCHAR DxDiag_DirectPlay[] = {'D','x','D','i','a','g','_','D','i','r','e','c','t','P','l','a','y',0};
    static const WCHAR DxDiag_SystemDevices[] = {'D','x','D','i','a','g','_','S','y','s','t','e','m','D','e','v','i','c','e','s',0};
    static const WCHAR DxDiag_DirectXFiles[] = {'D','x','D','i','a','g','_','D','i','r','e','c','t','X','F','i','l','e','s',0};
    static const WCHAR DxDiag_DirectShowFilters[] = {'D','x','D','i','a','g','_','D','i','r','e','c','t','S','h','o','w','F','i','l','t','e','r','s',0};
    static const WCHAR DxDiag_LogicalDisks[] = {'D','x','D','i','a','g','_','L','o','g','i','c','a','l','D','i','s','k','s',0};

    HRESULT hr;
    DWORD count, index;

    static const WCHAR *root_children[] = {
        DxDiag_SystemInfo, DxDiag_DisplayDevices, DxDiag_DirectSound,
        DxDiag_DirectMusic, DxDiag_DirectInput, DxDiag_DirectPlay,
        DxDiag_SystemDevices, DxDiag_DirectXFiles, DxDiag_DirectShowFilters,
        DxDiag_LogicalDisks
    };

    if (!create_root_IDxDiagContainer())
    {
        skip("Unable to create the root IDxDiagContainer\n");
        return;
    }

    /* Verify the identity and ordering of the root container's children. */
    hr = IDxDiagContainer_GetNumberOfChildContainers(pddc, &count);
    ok(hr == S_OK, "Expected IDxDiagContainer::GetNumberOfChildContainers to return S_OK, got 0x%08x\n", hr);
    if (FAILED(hr))
    {
        skip("IDxDiagContainer::GetNumberOfChildContainers failed\n");
        goto cleanup;
    }

    ok(count == sizeof(root_children)/sizeof(root_children[0]),
       "Got unexpected count %u for the number of child containers\n", count);

    if (count != sizeof(root_children)/sizeof(root_children[0]))
    {
        skip("Received unexpected number of child containers\n");
        goto cleanup;
    }

    for (index = 0; index <= count; index++)
    {
        WCHAR container[256];

        hr = IDxDiagContainer_EnumChildContainerNames(pddc, index, container, sizeof(container)/sizeof(WCHAR));
        if (hr == E_INVALIDARG)
        {
            ok(index == count,
               "Expected IDxDiagContainer::EnumChildContainerNames to return "
               "E_INVALIDARG on the last index %u\n", count);
            break;
        }
        else if (hr == S_OK)
        {
            ok(!lstrcmpW(container, root_children[index]),
               "Expected container %s for index %u, got %s\n",
               wine_dbgstr_w(root_children[index]), index, wine_dbgstr_w(container));
        }
        else
        {
            ok(0, "IDxDiagContainer::EnumChildContainerNames unexpectedly returned 0x%08x\n", hr);
            break;
        }
    }

cleanup:
    IDxDiagContainer_Release(pddc);
    IDxDiagProvider_Release(pddp);
}