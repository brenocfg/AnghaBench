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
typedef  int /*<<< orphan*/  IQueryAssociations ;
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ASSOCF_NONE ; 
 int /*<<< orphan*/  ASSOCSTR_EXECUTABLE ; 
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_QueryAssociations ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  ERROR_NO_ASSOCIATION ; 
 scalar_t__ E_FAIL ; 
 scalar_t__ E_INVALIDARG ; 
 scalar_t__ HRESULT_FROM_WIN32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IQueryAssociations ; 
 scalar_t__ IQueryAssociations_GetString (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ IQueryAssociations_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IQueryAssociations_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_FALSE ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/ * badW ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/ * httpW ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void test_IQueryAssociations_Init(void)
{
    IQueryAssociations *assoc;
    HRESULT hr;
    DWORD len;

    hr = CoCreateInstance(&CLSID_QueryAssociations, NULL, CLSCTX_INPROC_SERVER, &IID_IQueryAssociations, (void*)&assoc);
    ok(hr == S_OK, "failed to create object, 0x%x\n", hr);

    hr = IQueryAssociations_Init(assoc, ASSOCF_NONE, NULL, NULL, NULL);
    ok(hr == E_INVALIDARG, "Init failed, 0x%08x\n", hr);

    hr = IQueryAssociations_Init(assoc, ASSOCF_NONE, httpW, NULL, NULL);
    ok(hr == S_OK, "Init failed, 0x%08x\n", hr);

    hr = IQueryAssociations_Init(assoc, ASSOCF_NONE, badW, NULL, NULL);
    ok(hr == S_OK || broken(hr == S_FALSE) /* pre-vista */, "Init failed, 0x%08x\n", hr);

    len = 0;
    hr = IQueryAssociations_GetString(assoc, ASSOCF_NONE, ASSOCSTR_EXECUTABLE, NULL, NULL, &len);
    ok(hr == HRESULT_FROM_WIN32(ERROR_NO_ASSOCIATION) || broken(hr == E_FAIL) /* pre-vista */, "got 0x%08x\n", hr);

    IQueryAssociations_Release(assoc);
}