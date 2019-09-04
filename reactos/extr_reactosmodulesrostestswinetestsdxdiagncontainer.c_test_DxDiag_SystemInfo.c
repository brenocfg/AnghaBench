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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  IDxDiagContainer ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 char const* DxDiag_SystemInfo ; 
 scalar_t__ E_INVALIDARG ; 
 scalar_t__ IDxDiagContainer_GetChildContainer (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IDxDiagContainer_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDxDiagProvider_Release (int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 
#define  VT_BOOL 130 
#define  VT_BSTR 129 
#define  VT_UI4 128 
 int /*<<< orphan*/  create_root_IDxDiagContainer () ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/ * pddc ; 
 int /*<<< orphan*/  pddp ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  test_container_properties (int /*<<< orphan*/ *,struct property_test const*,int) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void test_DxDiag_SystemInfo(void)
{
    static const WCHAR dwOSMajorVersion[] = {'d','w','O','S','M','a','j','o','r','V','e','r','s','i','o','n',0};
    static const WCHAR dwOSMinorVersion[] = {'d','w','O','S','M','i','n','o','r','V','e','r','s','i','o','n',0};
    static const WCHAR dwOSBuildNumber[] = {'d','w','O','S','B','u','i','l','d','N','u','m','b','e','r',0};
    static const WCHAR dwOSPlatformID[] = {'d','w','O','S','P','l','a','t','f','o','r','m','I','D',0};
    static const WCHAR dwDirectXVersionMajor[] = {'d','w','D','i','r','e','c','t','X','V','e','r','s','i','o','n','M','a','j','o','r',0};
    static const WCHAR dwDirectXVersionMinor[] = {'d','w','D','i','r','e','c','t','X','V','e','r','s','i','o','n','M','i','n','o','r',0};
    static const WCHAR szDirectXVersionLetter[] = {'s','z','D','i','r','e','c','t','X','V','e','r','s','i','o','n','L','e','t','t','e','r',0};
    static const WCHAR bDebug[] = {'b','D','e','b','u','g',0};
    static const WCHAR bNECPC98[] = {'b','N','E','C','P','C','9','8',0};
    static const WCHAR ullPhysicalMemory[] = {'u','l','l','P','h','y','s','i','c','a','l','M','e','m','o','r','y',0};
    static const WCHAR ullUsedPageFile[] = {'u','l','l','U','s','e','d','P','a','g','e','F','i','l','e',0};
    static const WCHAR ullAvailPageFile[] = {'u','l','l','A','v','a','i','l','P','a','g','e','F','i','l','e',0};
    static const WCHAR szWindowsDir[] = {'s','z','W','i','n','d','o','w','s','D','i','r',0};
    static const WCHAR szCSDVersion[] = {'s','z','C','S','D','V','e','r','s','i','o','n',0};
    static const WCHAR szDirectXVersionEnglish[] = {'s','z','D','i','r','e','c','t','X','V','e','r','s','i','o','n','E','n','g','l','i','s','h',0};
    static const WCHAR szDirectXVersionLongEnglish[] = {'s','z','D','i','r','e','c','t','X','V','e','r','s','i','o','n','L','o','n','g','E','n','g','l','i','s','h',0};
    static const WCHAR bNetMeetingRunning[] = {'b','N','e','t','M','e','e','t','i','n','g','R','u','n','n','i','n','g',0};
    static const WCHAR szMachineNameLocalized[] = {'s','z','M','a','c','h','i','n','e','N','a','m','e','L','o','c','a','l','i','z','e','d',0};
    static const WCHAR szMachineNameEnglish[] = {'s','z','M','a','c','h','i','n','e','N','a','m','e','E','n','g','l','i','s','h',0};
    static const WCHAR szLanguagesLocalized[] = {'s','z','L','a','n','g','u','a','g','e','s','L','o','c','a','l','i','z','e','d',0};
    static const WCHAR szLanguagesEnglish[] = {'s','z','L','a','n','g','u','a','g','e','s','E','n','g','l','i','s','h',0};
    static const WCHAR szTimeLocalized[] = {'s','z','T','i','m','e','L','o','c','a','l','i','z','e','d',0};
    static const WCHAR szTimeEnglish[] = {'s','z','T','i','m','e','E','n','g','l','i','s','h',0};
    static const WCHAR szPhysicalMemoryEnglish[] = {'s','z','P','h','y','s','i','c','a','l','M','e','m','o','r','y','E','n','g','l','i','s','h',0};
    static const WCHAR szPageFileLocalized[] = {'s','z','P','a','g','e','F','i','l','e','L','o','c','a','l','i','z','e','d',0};
    static const WCHAR szPageFileEnglish[] = {'s','z','P','a','g','e','F','i','l','e','E','n','g','l','i','s','h',0};
    static const WCHAR szOSLocalized[] = {'s','z','O','S','L','o','c','a','l','i','z','e','d',0};
    static const WCHAR szOSExLocalized[] = {'s','z','O','S','E','x','L','o','c','a','l','i','z','e','d',0};
    static const WCHAR szOSExLongLocalized[] = {'s','z','O','S','E','x','L','o','n','g','L','o','c','a','l','i','z','e','d',0};
    static const WCHAR szOSEnglish[] = {'s','z','O','S','E','n','g','l','i','s','h',0};
    static const WCHAR szOSExEnglish[] = {'s','z','O','S','E','x','E','n','g','l','i','s','h',0};
    static const WCHAR szOSExLongEnglish[] = {'s','z','O','S','E','x','L','o','n','g','E','n','g','l','i','s','h',0};
    static const WCHAR szProcessorEnglish[] = {'s','z','P','r','o','c','e','s','s','o','r','E','n','g','l','i','s','h',0};

    static const struct property_test property_tests[] =
    {
        {dwOSMajorVersion, VT_UI4},
        {dwOSMinorVersion, VT_UI4},
        {dwOSBuildNumber, VT_UI4},
        {dwOSPlatformID, VT_UI4},
        {dwDirectXVersionMajor, VT_UI4},
        {dwDirectXVersionMinor, VT_UI4},
        {szDirectXVersionLetter, VT_BSTR},
        {bDebug, VT_BOOL},
        {bNECPC98, VT_BOOL},
        {ullPhysicalMemory, VT_BSTR},
        {ullUsedPageFile, VT_BSTR},
        {ullAvailPageFile, VT_BSTR},
        {szWindowsDir, VT_BSTR},
        {szCSDVersion, VT_BSTR},
        {szDirectXVersionEnglish, VT_BSTR},
        {szDirectXVersionLongEnglish, VT_BSTR},
        {bNetMeetingRunning, VT_BOOL},
        {szMachineNameLocalized, VT_BSTR},
        {szMachineNameEnglish, VT_BSTR},
        {szLanguagesLocalized, VT_BSTR},
        {szLanguagesEnglish, VT_BSTR},
        {szTimeLocalized, VT_BSTR},
        {szTimeEnglish, VT_BSTR},
        {szPhysicalMemoryEnglish, VT_BSTR},
        {szPageFileLocalized, VT_BSTR},
        {szPageFileEnglish, VT_BSTR},
        {szOSLocalized, VT_BSTR},
        {szOSExLocalized, VT_BSTR},
        {szOSExLongLocalized, VT_BSTR},
        {szOSEnglish, VT_BSTR},
        {szOSExEnglish, VT_BSTR},
        {szOSExLongEnglish, VT_BSTR},
        {szProcessorEnglish, VT_BSTR},
    };

    IDxDiagContainer *container, *container2;
    static const WCHAR empty[] = {0};
    HRESULT hr;

    if (!create_root_IDxDiagContainer())
    {
        skip("Unable to create the root IDxDiagContainer\n");
        return;
    }

    hr = IDxDiagContainer_GetChildContainer(pddc, empty, &container2);
    ok(hr == E_INVALIDARG, "Expected IDxDiagContainer::GetChildContainer to return E_INVALIDARG, got 0x%08x\n", hr);

    hr = IDxDiagContainer_GetChildContainer(pddc, DxDiag_SystemInfo, &container);
    ok(hr == S_OK, "Expected IDxDiagContainer::GetChildContainer to return S_OK, got 0x%08x\n", hr);

    if (hr == S_OK)
    {
        trace("Testing container DxDiag_SystemInfo\n");
        test_container_properties(container, property_tests, sizeof(property_tests)/sizeof(property_tests[0]));

        container2 = NULL;
        hr = IDxDiagContainer_GetChildContainer(container, empty, &container2);
        ok(hr == S_OK, "Expected IDxDiagContainer::GetChildContainer to return S_OK, got 0x%08x\n", hr);
        ok(container2 != NULL, "Expected container2 != NULL\n");
        ok(container2 != container, "Expected container != container2\n");
        if (hr == S_OK) IDxDiagContainer_Release(container2);

        IDxDiagContainer_Release(container);
    }

    IDxDiagContainer_Release(pddc);
    IDxDiagProvider_Release(pddp);
}