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
typedef  int /*<<< orphan*/  ITfInputProcessorProfileMgr ;
typedef  int /*<<< orphan*/  IEnumTfInputProcessorProfiles ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  IEnumTfInputProcessorProfiles_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_ITfInputProcessorProfileMgr ; 
 scalar_t__ ITfInputProcessorProfileMgr_EnumProfiles (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ITfInputProcessorProfileMgr_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ ITfInputProcessorProfiles_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  g_ipp ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_profile_mgr(void)
{
    IEnumTfInputProcessorProfiles *enum_profiles;
    ITfInputProcessorProfileMgr *ipp_mgr;
    HRESULT hres;

    hres = ITfInputProcessorProfiles_QueryInterface(g_ipp, &IID_ITfInputProcessorProfileMgr, (void**)&ipp_mgr);
    if (hres != S_OK)
    {
        win_skip("ITfInputProcessorProfileMgr is not supported.\n");
        return;
    }
    ok(hres == S_OK, "Could not get ITfInputProcessorProfileMgr iface: %08x\n", hres);

    hres = ITfInputProcessorProfileMgr_EnumProfiles(ipp_mgr, 0, &enum_profiles);
    ok(hres == S_OK, "EnumProfiles failed: %08x\n", hres);

    IEnumTfInputProcessorProfiles_Release(enum_profiles);

    ITfInputProcessorProfileMgr_Release(ipp_mgr);
}