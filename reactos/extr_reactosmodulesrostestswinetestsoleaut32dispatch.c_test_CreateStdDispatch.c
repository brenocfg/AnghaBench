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
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  ITypeLib ;
typedef  int /*<<< orphan*/  ITypeInfo ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ CreateStdDispatch (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ E_INVALIDARG ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 int /*<<< orphan*/  ITypeInfo_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ ITypeLib_GetTypeInfoOfGuid (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ITypeLib_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ LoadTypeLib (char const*,int /*<<< orphan*/ **) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  test_unk ; 

__attribute__((used)) static void test_CreateStdDispatch(void)
{
    static const WCHAR stdole2W[] = {'s','t','d','o','l','e','2','.','t','l','b',0};
    ITypeLib *tl;
    ITypeInfo *ti;
    IUnknown *unk;
    HRESULT hr;

    hr = CreateStdDispatch(NULL, NULL, NULL, NULL);
    ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);

    hr = CreateStdDispatch(NULL, NULL, NULL, &unk);
    ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);

    hr = LoadTypeLib(stdole2W, &tl);
    ok(hr == S_OK, "got %08x\n", hr);
    hr = ITypeLib_GetTypeInfoOfGuid(tl, &IID_IUnknown, &ti);
    ok(hr == S_OK, "got %08x\n", hr);
    ITypeLib_Release(tl);

    hr = CreateStdDispatch(NULL, &test_unk, NULL, &unk);
    ok(hr == E_INVALIDARG, "got %08x\n", hr);

    hr = CreateStdDispatch(NULL, NULL, ti, &unk);
    ok(hr == E_INVALIDARG, "got %08x\n", hr);

    hr = CreateStdDispatch(NULL, &test_unk, ti, &unk);
    ok(hr == S_OK, "got %08x\n", hr);
    IUnknown_Release(unk);

    ITypeInfo_Release(ti);
}