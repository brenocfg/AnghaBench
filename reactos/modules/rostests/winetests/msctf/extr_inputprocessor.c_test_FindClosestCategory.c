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
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  GUID ;

/* Variables and functions */
 int /*<<< orphan*/  CLSID_FakeService ; 
 int /*<<< orphan*/  const GUID_NULL ; 
 int /*<<< orphan*/  const GUID_TFCAT_DISPLAYATTRIBUTEPROVIDER ; 
 int /*<<< orphan*/  const GUID_TFCAT_TIP_HANDWRITING ; 
 int /*<<< orphan*/  const GUID_TFCAT_TIP_KEYBOARD ; 
 int /*<<< orphan*/  const GUID_TFCAT_TIP_SPEECH ; 
 int /*<<< orphan*/  ITfCategoryMgr_FindClosestCategory (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int) ; 
 int /*<<< orphan*/  IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_cm ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void test_FindClosestCategory(void)
{
    GUID output;
    HRESULT hr;
    const GUID *list[3] = {&GUID_TFCAT_TIP_SPEECH, &GUID_TFCAT_TIP_KEYBOARD, &GUID_TFCAT_TIP_HANDWRITING};

    hr = ITfCategoryMgr_FindClosestCategory(g_cm, &CLSID_FakeService, &output, NULL, 0);
    ok(SUCCEEDED(hr),"ITfCategoryMgr_FindClosestCategory failed (%x)\n",hr);
    ok(IsEqualGUID(&output,&GUID_TFCAT_DISPLAYATTRIBUTEPROVIDER),"Wrong GUID\n");

    hr = ITfCategoryMgr_FindClosestCategory(g_cm, &CLSID_FakeService, &output, list, 1);
    ok(SUCCEEDED(hr),"ITfCategoryMgr_FindClosestCategory failed (%x)\n",hr);
    ok(IsEqualGUID(&output,&GUID_NULL),"Wrong GUID\n");

    hr = ITfCategoryMgr_FindClosestCategory(g_cm, &CLSID_FakeService, &output, list, 3);
    ok(SUCCEEDED(hr),"ITfCategoryMgr_FindClosestCategory failed (%x)\n",hr);
    ok(IsEqualGUID(&output,&GUID_TFCAT_TIP_KEYBOARD),"Wrong GUID\n");
}