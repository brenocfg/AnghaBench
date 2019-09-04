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
typedef  scalar_t__ TfGuidAtom ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  GUID ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CLSID_FakeService ; 
 int /*<<< orphan*/  CoCreateGuid (int /*<<< orphan*/ *) ; 
 scalar_t__ E_INVALIDARG ; 
 int /*<<< orphan*/  GUID_NULL ; 
 scalar_t__ ITfCategoryMgr_GetGUID (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ ITfCategoryMgr_IsEqualTfGuidAtom (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ ITfCategoryMgr_RegisterGUID (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 int IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int SUCCEEDED (scalar_t__) ; 
 scalar_t__ TRUE ; 
 scalar_t__ cid ; 
 int /*<<< orphan*/  g_cm ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 scalar_t__ tid ; 

__attribute__((used)) static void test_TfGuidAtom(void)
{
    GUID gtest,g1;
    HRESULT hr;
    TfGuidAtom atom1,atom2;
    BOOL equal;

    CoCreateGuid(&gtest);

    /* msdn reports this should return E_INVALIDARG.  However my test show it crashing (winxp)*/
    /*
    hr = ITfCategoryMgr_RegisterGUID(g_cm,&gtest,NULL);
    ok(hr==E_INVALIDARG,"ITfCategoryMgr_RegisterGUID should have failed\n");
    */
    hr = ITfCategoryMgr_RegisterGUID(g_cm,&gtest,&atom1);
    ok(SUCCEEDED(hr),"ITfCategoryMgr_RegisterGUID failed\n");
    hr = ITfCategoryMgr_RegisterGUID(g_cm,&gtest,&atom2);
    ok(SUCCEEDED(hr),"ITfCategoryMgr_RegisterGUID failed\n");
    ok(atom1 == atom2,"atoms do not match\n");
    hr = ITfCategoryMgr_GetGUID(g_cm,atom2,NULL);
    ok(hr==E_INVALIDARG,"ITfCategoryMgr_GetGUID should have failed\n");
    hr = ITfCategoryMgr_GetGUID(g_cm,atom2,&g1);
    ok(SUCCEEDED(hr),"ITfCategoryMgr_GetGUID failed\n");
    ok(IsEqualGUID(&g1,&gtest),"guids do not match\n");
    hr = ITfCategoryMgr_IsEqualTfGuidAtom(g_cm,atom1,&gtest,NULL);
    ok(hr==E_INVALIDARG,"ITfCategoryMgr_IsEqualTfGuidAtom should have failed\n");
    hr = ITfCategoryMgr_IsEqualTfGuidAtom(g_cm,atom1,&gtest,&equal);
    ok(SUCCEEDED(hr),"ITfCategoryMgr_IsEqualTfGuidAtom failed\n");
    ok(equal == TRUE,"Equal value invalid\n");

    /* show that cid and tid TfClientIds are also TfGuidAtoms */
    hr = ITfCategoryMgr_IsEqualTfGuidAtom(g_cm,tid,&CLSID_FakeService,&equal);
    ok(SUCCEEDED(hr),"ITfCategoryMgr_IsEqualTfGuidAtom failed\n");
    ok(equal == TRUE,"Equal value invalid\n");
    hr = ITfCategoryMgr_GetGUID(g_cm,cid,&g1);
    ok(SUCCEEDED(hr),"ITfCategoryMgr_GetGUID failed\n");
    ok(!IsEqualGUID(&g1,&GUID_NULL),"guid should not be NULL\n");
}