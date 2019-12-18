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
typedef  int UINT ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IDispatchEx ;
typedef  int /*<<< orphan*/ * HRESULT ;
typedef  int /*<<< orphan*/ * DWORD ;
typedef  int /*<<< orphan*/  DISPID ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  DISPID_XMLDOM_NODELIST_RESET ; 
 int /*<<< orphan*/ * DISP_E_UNKNOWNNAME ; 
 int /*<<< orphan*/  EXPECT_HR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_NOTIMPL ; 
 scalar_t__ FAILED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * IDispatchEx_DeleteMemberByDispID (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * IDispatchEx_DeleteMemberByName (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * IDispatchEx_GetDispID (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * IDispatchEx_GetMemberName (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * IDispatchEx_GetMemberProperties (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * IDispatchEx_GetNameSpaceParent (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * IDispatchEx_GetNextDispID (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * IDispatchEx_GetTypeInfoCount (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  IDispatchEx_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IDispatchEx ; 
 int /*<<< orphan*/ * IUnknown_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  SysAllocString (char const*) ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdexEnumDefault ; 
 int /*<<< orphan*/  fdexNameCaseSensitive ; 
 int /*<<< orphan*/  fdexNameEnsure ; 
 int /*<<< orphan*/  grfdexPropCanAll ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 char const* szstar ; 

__attribute__((used)) static void test_domobj_dispex(IUnknown *obj)
{
    static const WCHAR testW[] = {'t','e','s','t','p','r','o','p',0};
    DISPID dispid = DISPID_XMLDOM_NODELIST_RESET;
    IDispatchEx *dispex;
    IUnknown *unk;
    DWORD props;
    UINT ticnt;
    HRESULT hr;
    BSTR name;

    hr = IUnknown_QueryInterface(obj, &IID_IDispatchEx, (void**)&dispex);
    EXPECT_HR(hr, S_OK);
    if (FAILED(hr)) return;

    ticnt = 0;
    hr = IDispatchEx_GetTypeInfoCount(dispex, &ticnt);
    EXPECT_HR(hr, S_OK);
    ok(ticnt == 1, "ticnt=%u\n", ticnt);

    name = SysAllocString(szstar);
    hr = IDispatchEx_DeleteMemberByName(dispex, name, fdexNameCaseSensitive);
    EXPECT_HR(hr, E_NOTIMPL);
    SysFreeString(name);

    hr = IDispatchEx_DeleteMemberByDispID(dispex, dispid);
    EXPECT_HR(hr, E_NOTIMPL);

    props = 0;
    hr = IDispatchEx_GetMemberProperties(dispex, dispid, grfdexPropCanAll, &props);
    EXPECT_HR(hr, E_NOTIMPL);
    ok(props == 0, "expected 0 got %d\n", props);

    hr = IDispatchEx_GetMemberName(dispex, dispid, &name);
    EXPECT_HR(hr, E_NOTIMPL);
    if (SUCCEEDED(hr)) SysFreeString(name);

    hr = IDispatchEx_GetNextDispID(dispex, fdexEnumDefault, DISPID_XMLDOM_NODELIST_RESET, &dispid);
    EXPECT_HR(hr, E_NOTIMPL);

    unk = (IUnknown*)0xdeadbeef;
    hr = IDispatchEx_GetNameSpaceParent(dispex, &unk);
    EXPECT_HR(hr, E_NOTIMPL);
    ok(unk == (IUnknown*)0xdeadbeef, "got %p\n", unk);

    name = SysAllocString(testW);
    hr = IDispatchEx_GetDispID(dispex, name, fdexNameEnsure, &dispid);
    ok(hr == DISP_E_UNKNOWNNAME, "got 0x%08x\n", hr);
    SysFreeString(name);

    IDispatchEx_Release(dispex);
}