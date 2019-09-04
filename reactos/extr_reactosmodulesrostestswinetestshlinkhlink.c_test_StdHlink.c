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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  IHlink ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int CLSCTX_INPROC_HANDLER ; 
 int CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_StdHlink ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  CoTaskMemFree (char*) ; 
 scalar_t__ IHlink_GetTargetFrameName (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  IHlink_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IHlink_SetTargetFrameName (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  IID_IHlink ; 
 scalar_t__ S_FALSE ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  lstrcmpW (char*,char const*) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ wine_dbgstr_w (char*) ; 

__attribute__((used)) static void test_StdHlink(void)
{
    IHlink *hlink;
    WCHAR *str;
    HRESULT hres;

    static const WCHAR testW[] = {'t','e','s','t',0};

    hres = CoCreateInstance(&CLSID_StdHlink, NULL, CLSCTX_INPROC_SERVER|CLSCTX_INPROC_HANDLER,
            &IID_IHlink, (void**)&hlink);
    ok(hres == S_OK, "CoCreateInstance failed: %08x\n", hres);

    str = (void*)0xdeadbeef;
    hres = IHlink_GetTargetFrameName(hlink, &str);
    ok(hres == S_FALSE, "GetTargetFrameName failed: %08x\n", hres);
    ok(!str, "str = %s\n", wine_dbgstr_w(str));

    hres = IHlink_SetTargetFrameName(hlink, testW);
    ok(hres == S_OK, "SetTargetFrameName failed: %08x\n", hres);

    str = (void*)0xdeadbeef;
    hres = IHlink_GetTargetFrameName(hlink, &str);
    ok(hres == S_OK, "GetTargetFrameName failed: %08x\n", hres);
    ok(!lstrcmpW(str, testW), "str = %s\n", wine_dbgstr_w(str));
    CoTaskMemFree(str);

    hres = IHlink_SetTargetFrameName(hlink, NULL);
    ok(hres == S_OK, "SetTargetFrameName failed: %08x\n", hres);

    str = (void*)0xdeadbeef;
    hres = IHlink_GetTargetFrameName(hlink, &str);
    ok(hres == S_FALSE, "GetTargetFrameName failed: %08x\n", hres);
    ok(!str, "str = %s\n", wine_dbgstr_w(str));

    IHlink_Release(hlink);
}