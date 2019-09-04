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
 char* DxDiag_SoundCaptureDevices ; 
 scalar_t__ IDxDiagContainer_EnumChildContainerNames (int /*<<< orphan*/ *,scalar_t__,char*,int) ; 
 scalar_t__ IDxDiagContainer_GetChildContainer (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 
 scalar_t__ IDxDiagContainer_GetNumberOfChildContainers (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ IDxDiagContainer_GetNumberOfProps (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  IDxDiagContainer_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDxDiagProvider_Release (int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 
#define  VT_BSTR 128 
 int /*<<< orphan*/  create_root_IDxDiagContainer () ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/ * pddc ; 
 int /*<<< orphan*/  pddp ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  test_container_properties (int /*<<< orphan*/ *,struct property_test const*,int) ; 
 int /*<<< orphan*/  trace (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wine_dbgstr_w (char*) ; 

__attribute__((used)) static void test_DxDiag_SoundCaptureDevices(void)
{
    static const WCHAR szDescription[] = {'s','z','D','e','s','c','r','i','p','t','i','o','n',0};
    static const WCHAR szGuidDeviceID[] = {'s','z','G','u','i','d','D','e','v','i','c','e','I','D',0};
    static const WCHAR szDriverPath[] = {'s','z','D','r','i','v','e','r','P','a','t','h',0};
    static const WCHAR szDriverName[] = {'s','z','D','r','i','v','e','r','N','a','m','e',0};

    static const struct property_test property_tests[] =
    {
        {szDescription, VT_BSTR},
        {szGuidDeviceID, VT_BSTR},
        {szDriverName, VT_BSTR},
        {szDriverPath, VT_BSTR},
    };

    IDxDiagContainer *sound_cont = NULL;
    DWORD count, i;
    HRESULT hr;

    if (!create_root_IDxDiagContainer())
    {
        skip("Unable to create the root IDxDiagContainer\n");
        return;
    }

    hr = IDxDiagContainer_GetChildContainer(pddc, DxDiag_SoundCaptureDevices, &sound_cont);
    ok(hr == S_OK, "Expected IDxDiagContainer::GetChildContainer to return S_OK, got 0x%08x\n", hr);

    if (hr != S_OK)
        goto cleanup;

    hr = IDxDiagContainer_GetNumberOfProps(sound_cont, &count);
    ok(hr == S_OK, "Expected IDxDiagContainer::GetNumberOfProps to return S_OK, got 0x%08x\n", hr);
    if (hr == S_OK)
        ok(count == 0, "Expected count to be 0, got %u\n", count);

    hr = IDxDiagContainer_GetNumberOfChildContainers(sound_cont, &count);
    ok(hr == S_OK, "Expected IDxDiagContainer::GetNumberOfChildContainers to return S_OK, got 0x%08x\n", hr);

    if (hr != S_OK)
        goto cleanup;

    for (i = 0; i < count; i++)
    {
        WCHAR child_container[256];
        IDxDiagContainer *child;

        hr = IDxDiagContainer_EnumChildContainerNames(sound_cont, i, child_container, sizeof(child_container)/sizeof(WCHAR));
        ok(hr == S_OK, "Expected IDxDiagContainer::EnumChildContainerNames to return S_OK, got 0x%08x\n", hr);

        hr = IDxDiagContainer_GetChildContainer(sound_cont, child_container, &child);
        ok(hr == S_OK, "Expected IDxDiagContainer::GetChildContainer to return S_OK, got 0x%08x\n", hr);

        if (hr == S_OK)
        {
            trace("Testing container %s\n", wine_dbgstr_w(child_container));
            test_container_properties(child, property_tests, sizeof(property_tests)/sizeof(property_tests[0]));
        }
        IDxDiagContainer_Release(child);
    }

cleanup:
    if (sound_cont) IDxDiagContainer_Release(sound_cont);
    IDxDiagContainer_Release(pddc);
    IDxDiagProvider_Release(pddp);
}