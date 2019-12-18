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

/* Variables and functions */
 int /*<<< orphan*/  CLSID_FakeService ; 
 int /*<<< orphan*/  GUID_TFCAT_DISPLAYATTRIBUTEPROVIDER ; 
 int /*<<< orphan*/  GUID_TFCAT_TIP_KEYBOARD ; 
 int /*<<< orphan*/  ITfCategoryMgr_UnregisterCategory (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_cm ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void test_UnregisterCategory(void)
{
    HRESULT hr;
    hr = ITfCategoryMgr_UnregisterCategory(g_cm, &CLSID_FakeService, &GUID_TFCAT_TIP_KEYBOARD, &CLSID_FakeService);
    ok(SUCCEEDED(hr),"ITfCategoryMgr_UnregisterCategory failed\n");
    hr = ITfCategoryMgr_UnregisterCategory(g_cm, &CLSID_FakeService, &GUID_TFCAT_DISPLAYATTRIBUTEPROVIDER, &CLSID_FakeService);
    ok(SUCCEEDED(hr),"ITfCategoryMgr_UnregisterCategory failed\n");
}