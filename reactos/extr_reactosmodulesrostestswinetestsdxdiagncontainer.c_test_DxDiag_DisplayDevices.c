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
struct property_test {char const* member_0; int /*<<< orphan*/  const member_1; } ;
typedef  int /*<<< orphan*/  property_tests ;
typedef  int /*<<< orphan*/  child_container ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  IDxDiagContainer ;
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 char* DxDiag_DisplayDevices ; 
 scalar_t__ IDxDiagContainer_EnumChildContainerNames (int /*<<< orphan*/ *,scalar_t__,char*,int) ; 
 scalar_t__ IDxDiagContainer_GetChildContainer (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 
 scalar_t__ IDxDiagContainer_GetNumberOfChildContainers (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ IDxDiagContainer_GetNumberOfProps (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  IDxDiagContainer_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDxDiagProvider_Release (int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 
#define  VT_BOOL 130 
#define  VT_BSTR 129 
#define  VT_UI4 128 
 int /*<<< orphan*/  create_root_IDxDiagContainer () ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/ * pddc ; 
 int /*<<< orphan*/  pddp ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  test_container_properties (int /*<<< orphan*/ *,struct property_test const*,int) ; 
 int /*<<< orphan*/  trace (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wine_dbgstr_w (char*) ; 

__attribute__((used)) static void test_DxDiag_DisplayDevices(void)
{
    static const WCHAR szDescription[] = {'s','z','D','e','s','c','r','i','p','t','i','o','n',0};
    static const WCHAR szDeviceName[] = {'s','z','D','e','v','i','c','e','N','a','m','e',0};
    static const WCHAR szKeyDeviceID[] = {'s','z','K','e','y','D','e','v','i','c','e','I','D',0};
    static const WCHAR szKeyDeviceKey[] = {'s','z','K','e','y','D','e','v','i','c','e','K','e','y',0};
    static const WCHAR szVendorId[] = {'s','z','V','e','n','d','o','r','I','d',0};
    static const WCHAR szDeviceId[] = {'s','z','D','e','v','i','c','e','I','d',0};
    static const WCHAR szDeviceIdentifier[] = {'s','z','D','e','v','i','c','e','I','d','e','n','t','i','f','i','e','r',0};
    static const WCHAR dwWidth[] = {'d','w','W','i','d','t','h',0};
    static const WCHAR dwHeight[] = {'d','w','H','e','i','g','h','t',0};
    static const WCHAR dwBpp[] = {'d','w','B','p','p',0};
    static const WCHAR szDisplayMemoryLocalized[] = {'s','z','D','i','s','p','l','a','y','M','e','m','o','r','y','L','o','c','a','l','i','z','e','d',0};
    static const WCHAR szDisplayMemoryEnglish[] = {'s','z','D','i','s','p','l','a','y','M','e','m','o','r','y','E','n','g','l','i','s','h',0};
    static const WCHAR szDriverName[] = {'s','z','D','r','i','v','e','r','N','a','m','e',0};
    static const WCHAR szDriverVersion[] = {'s','z','D','r','i','v','e','r','V','e','r','s','i','o','n',0};
    static const WCHAR szSubSysId[] = {'s','z','S','u','b','S','y','s','I','d',0};
    static const WCHAR szRevisionId[] = {'s','z','R','e','v','i','s','i','o','n','I','d',0};
    static const WCHAR dwRefreshRate[] = {'d','w','R','e','f','r','e','s','h','R','a','t','e',0};
    static const WCHAR szManufacturer[] = {'s','z','M','a','n','u','f','a','c','t','u','r','e','r',0};
    static const WCHAR b3DAccelerationExists[] = {'b','3','D','A','c','c','e','l','e','r','a','t','i','o','n','E','x','i','s','t','s',0};
    static const WCHAR b3DAccelerationEnabled[] = {'b','3','D','A','c','c','e','l','e','r','a','t','i','o','n','E','n','a','b','l','e','d',0};
    static const WCHAR bDDAccelerationEnabled[] = {'b','D','D','A','c','c','e','l','e','r','a','t','i','o','n','E','n','a','b','l','e','d',0};
    static const WCHAR iAdapter[] = {'i','A','d','a','p','t','e','r',0};

    static const struct property_test property_tests[] =
    {
        {szDescription, VT_BSTR},
        {szDeviceName, VT_BSTR},
        {szKeyDeviceID, VT_BSTR},
        {szKeyDeviceKey, VT_BSTR},
        {szVendorId, VT_BSTR},
        {szDeviceId, VT_BSTR},
        {szDeviceIdentifier, VT_BSTR},
        {dwWidth, VT_UI4},
        {dwHeight, VT_UI4},
        {dwBpp, VT_UI4},
        {szDisplayMemoryLocalized, VT_BSTR},
        {szDisplayMemoryEnglish, VT_BSTR},
        {szDriverName, VT_BSTR},
        {szDriverVersion, VT_BSTR},
        {szSubSysId, VT_BSTR},
        {szRevisionId, VT_BSTR},
        {dwRefreshRate, VT_UI4},
        {szManufacturer, VT_BSTR},
        {b3DAccelerationExists, VT_BOOL},
        {b3DAccelerationEnabled, VT_BOOL},
        {bDDAccelerationEnabled, VT_BOOL},
        {iAdapter, VT_UI4},
    };

    IDxDiagContainer *display_cont = NULL;
    DWORD count, i;
    HRESULT hr;

    if (!create_root_IDxDiagContainer())
    {
        skip("Unable to create the root IDxDiagContainer\n");
        return;
    }

    hr = IDxDiagContainer_GetChildContainer(pddc, DxDiag_DisplayDevices, &display_cont);
    ok(hr == S_OK, "Expected IDxDiagContainer::GetChildContainer to return S_OK, got 0x%08x\n", hr);

    if (hr != S_OK)
        goto cleanup;

    hr = IDxDiagContainer_GetNumberOfProps(display_cont, &count);
    ok(hr == S_OK, "Expected IDxDiagContainer::GetNumberOfProps to return S_OK, got 0x%08x\n", hr);
    if (hr == S_OK)
        ok(count == 0, "Expected count to be 0, got %u\n", count);

    hr = IDxDiagContainer_GetNumberOfChildContainers(display_cont, &count);
    ok(hr == S_OK, "Expected IDxDiagContainer::GetNumberOfChildContainers to return S_OK, got 0x%08x\n", hr);

    if (hr != S_OK)
        goto cleanup;

    for (i = 0; i < count; i++)
    {
        WCHAR child_container[256];
        IDxDiagContainer *child;

        hr = IDxDiagContainer_EnumChildContainerNames(display_cont, i, child_container, sizeof(child_container)/sizeof(WCHAR));
        ok(hr == S_OK, "Expected IDxDiagContainer::EnumChildContainerNames to return S_OK, got 0x%08x\n", hr);

        hr = IDxDiagContainer_GetChildContainer(display_cont, child_container, &child);
        ok(hr == S_OK, "Expected IDxDiagContainer::GetChildContainer to return S_OK, got 0x%08x\n", hr);

        if (hr == S_OK)
        {
            trace("Testing container %s\n", wine_dbgstr_w(child_container));
            test_container_properties(child, property_tests, sizeof(property_tests)/sizeof(property_tests[0]));
        }
        IDxDiagContainer_Release(child);
    }

cleanup:
    if (display_cont) IDxDiagContainer_Release(display_cont);
    IDxDiagContainer_Release(pddc);
    IDxDiagProvider_Release(pddp);
}