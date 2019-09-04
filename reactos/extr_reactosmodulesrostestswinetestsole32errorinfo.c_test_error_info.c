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
typedef  float WCHAR ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IErrorInfo ;
typedef  int /*<<< orphan*/  ICreateErrorInfo ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLSID_WineTest ; 
 scalar_t__ CreateErrorInfo (int /*<<< orphan*/ **) ; 
 scalar_t__ E_INVALIDARG ; 
 scalar_t__ GetErrorInfo (int,int /*<<< orphan*/ **) ; 
 scalar_t__ ICreateErrorInfo_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  ICreateErrorInfo_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ ICreateErrorInfo_SetDescription (int /*<<< orphan*/ *,float*) ; 
 scalar_t__ ICreateErrorInfo_SetGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ICreateErrorInfo_SetHelpContext (int /*<<< orphan*/ *,int) ; 
 scalar_t__ ICreateErrorInfo_SetHelpFile (int /*<<< orphan*/ *,float*) ; 
 scalar_t__ ICreateErrorInfo_SetSource (int /*<<< orphan*/ *,float*) ; 
 scalar_t__ IErrorInfo_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IErrorInfo_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IErrorInfo ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_FALSE ; 
 scalar_t__ SetErrorInfo (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  ok_ole_success (scalar_t__,char*) ; 

__attribute__((used)) static void test_error_info(void)
{
    HRESULT hr;
    ICreateErrorInfo *pCreateErrorInfo;
    IErrorInfo *pErrorInfo;
    static WCHAR wszDescription[] = {'F','a','i','l','e','d',' ','S','p','r','o','c','k','e','t',0};
    static WCHAR wszHelpFile[] = {'s','p','r','o','c','k','e','t','.','h','l','p',0};
    static WCHAR wszSource[] = {'s','p','r','o','c','k','e','t',0};
    IUnknown *unk;

    hr = CreateErrorInfo(&pCreateErrorInfo);
    ok_ole_success(hr, "CreateErrorInfo");

    hr = ICreateErrorInfo_QueryInterface(pCreateErrorInfo, &IID_IUnknown, (void**)&unk);
    ok_ole_success(hr, "QI");
    IUnknown_Release(unk);

    hr = ICreateErrorInfo_SetDescription(pCreateErrorInfo, NULL);
    ok_ole_success(hr, "ICreateErrorInfo_SetDescription");

    hr = ICreateErrorInfo_SetDescription(pCreateErrorInfo, wszDescription);
    ok_ole_success(hr, "ICreateErrorInfo_SetDescription");

    hr = ICreateErrorInfo_SetGUID(pCreateErrorInfo, &CLSID_WineTest);
    ok_ole_success(hr, "ICreateErrorInfo_SetGUID");

    hr = ICreateErrorInfo_SetHelpContext(pCreateErrorInfo, 0xdeadbeef);
    ok_ole_success(hr, "ICreateErrorInfo_SetHelpContext");

    hr = ICreateErrorInfo_SetHelpFile(pCreateErrorInfo, NULL);
    ok_ole_success(hr, "ICreateErrorInfo_SetHelpFile");

    hr = ICreateErrorInfo_SetHelpFile(pCreateErrorInfo, wszHelpFile);
    ok_ole_success(hr, "ICreateErrorInfo_SetHelpFile");

    hr = ICreateErrorInfo_SetSource(pCreateErrorInfo, NULL);
    ok_ole_success(hr, "ICreateErrorInfo_SetSource");

    hr = ICreateErrorInfo_SetSource(pCreateErrorInfo, wszSource);
    ok_ole_success(hr, "ICreateErrorInfo_SetSource");

    hr = ICreateErrorInfo_QueryInterface(pCreateErrorInfo, &IID_IErrorInfo, (void **)&pErrorInfo);
    ok_ole_success(hr, "ICreateErrorInfo_QueryInterface");

    hr = IErrorInfo_QueryInterface(pErrorInfo, &IID_IUnknown, (void**)&unk);
    ok_ole_success(hr, "QI");
    IUnknown_Release(unk);

    ICreateErrorInfo_Release(pCreateErrorInfo);

    hr = SetErrorInfo(0, pErrorInfo);
    ok_ole_success(hr, "SetErrorInfo");

    IErrorInfo_Release(pErrorInfo);
    pErrorInfo = NULL;

    hr = GetErrorInfo(0, &pErrorInfo);
    ok_ole_success(hr, "GetErrorInfo");

    IErrorInfo_Release(pErrorInfo);

    hr = GetErrorInfo(0, &pErrorInfo);
    ok(hr == S_FALSE, "GetErrorInfo should have returned S_FALSE instead of 0x%08x\n", hr);
    ok(!pErrorInfo, "pErrorInfo should be set to NULL\n");

    hr = SetErrorInfo(0, NULL);
    ok_ole_success(hr, "SetErrorInfo");

    hr = GetErrorInfo(0xdeadbeef, &pErrorInfo);
    ok(hr == E_INVALIDARG, "GetErrorInfo should have returned E_INVALIDARG instead of 0x%08x\n", hr);

    hr = SetErrorInfo(0xdeadbeef, NULL);
    ok(hr == E_INVALIDARG, "SetErrorInfo should have returned E_INVALIDARG instead of 0x%08x\n", hr);
}