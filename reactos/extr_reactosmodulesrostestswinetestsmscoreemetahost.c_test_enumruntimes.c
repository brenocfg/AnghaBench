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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IEnumUnknown ;
typedef  int /*<<< orphan*/  ICLRRuntimeInfo ;
typedef  int HRESULT ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_INSUFFICIENT_BUFFER ; 
 scalar_t__ FAILED (int) ; 
 int HRESULT_FROM_WIN32 (int /*<<< orphan*/ ) ; 
 int ICLRMetaHost_EnumerateInstalledRuntimes (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int ICLRRuntimeInfo_GetVersionString (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  ICLRRuntimeInfo_Release (int /*<<< orphan*/ *) ; 
 int IEnumUnknown_Next (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  IEnumUnknown_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_ICLRRuntimeInfo ; 
 int IUnknown_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int S_FALSE ; 
 int S_OK ; 
 int /*<<< orphan*/  metahost ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/  trace (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wine_dbgstr_w (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_enumruntimes(void)
{
    IEnumUnknown *runtime_enum;
    IUnknown *unk;
    DWORD count;
    ICLRRuntimeInfo *runtime_info;
    HRESULT hr;
    WCHAR buf[MAX_PATH];

    hr = ICLRMetaHost_EnumerateInstalledRuntimes(metahost, &runtime_enum);
    ok(hr == S_OK, "EnumerateInstalledRuntimes returned %x\n", hr);
    if (FAILED(hr)) return;

    while ((hr = IEnumUnknown_Next(runtime_enum, 1, &unk, &count)) == S_OK)
    {
        hr = IUnknown_QueryInterface(unk, &IID_ICLRRuntimeInfo, (void**)&runtime_info);
        ok(hr == S_OK, "QueryInterface returned %x\n", hr);

        count = 1;
        hr = ICLRRuntimeInfo_GetVersionString(runtime_info, buf, &count);
        ok(hr == HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER), "GetVersionString returned %x\n", hr);
        ok(count > 1, "GetVersionString returned count %u\n", count);

        count = 0xdeadbeef;
        hr = ICLRRuntimeInfo_GetVersionString(runtime_info, NULL, &count);
        ok(hr == S_OK, "GetVersionString returned %x\n", hr);
        ok(count > 1 && count != 0xdeadbeef, "GetVersionString returned count %u\n", count);

        count = MAX_PATH;
        hr = ICLRRuntimeInfo_GetVersionString(runtime_info, buf, &count);
        ok(hr == S_OK, "GetVersionString returned %x\n", hr);
        ok(count > 1, "GetVersionString returned count %u\n", count);

        trace("runtime found: %s\n", wine_dbgstr_w(buf));

        ICLRRuntimeInfo_Release(runtime_info);

        IUnknown_Release(unk);
    }

    ok(hr == S_FALSE, "IEnumUnknown_Next returned %x\n", hr);

    IEnumUnknown_Release(runtime_enum);
}