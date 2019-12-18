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
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  IQueryAssociations ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ CLASS_E_CLASSNOTAVAILABLE ; 
 int /*<<< orphan*/  CLSID_QueryAssociations ; 
 scalar_t__ E_INVALIDARG ; 
 scalar_t__ E_NOINTERFACE ; 
 scalar_t__ E_NOTIMPL ; 
 int /*<<< orphan*/  IID_IQueryAssociations ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 int /*<<< orphan*/  IID_NULL ; 
 int /*<<< orphan*/  IQueryAssociations_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ pAssocCreate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_assoc_create(void)
{
    HRESULT hr;
    IQueryAssociations *pqa;

    if (!pAssocCreate)
    {
        win_skip("AssocCreate() is missing\n");
        return;
    }

    hr = pAssocCreate(IID_NULL, &IID_NULL, NULL);
    ok(hr == E_INVALIDARG, "Unexpected result : %08x\n", hr);

    hr = pAssocCreate(CLSID_QueryAssociations, &IID_NULL, (LPVOID*)&pqa);
    ok(hr == CLASS_E_CLASSNOTAVAILABLE || hr == E_NOTIMPL || hr == E_NOINTERFACE
        , "Unexpected result : %08x\n", hr);

    hr = pAssocCreate(IID_NULL, &IID_IQueryAssociations, (LPVOID*)&pqa);
    ok(hr == CLASS_E_CLASSNOTAVAILABLE || hr == E_NOTIMPL || hr == E_INVALIDARG
        , "Unexpected result : %08x\n", hr);

    hr = pAssocCreate(CLSID_QueryAssociations, &IID_IQueryAssociations, (LPVOID*)&pqa);
    ok(hr == S_OK  || hr == E_NOTIMPL /* win98 */
        , "Unexpected result : %08x\n", hr);
    if(hr == S_OK)
    {
        IQueryAssociations_Release(pqa);
    }

    hr = pAssocCreate(CLSID_QueryAssociations, &IID_IUnknown, (LPVOID*)&pqa);
    ok(hr == S_OK  || hr == E_NOTIMPL /* win98 */
        , "Unexpected result : %08x\n", hr);
    if(hr == S_OK)
    {
        IQueryAssociations_Release(pqa);
    }
}