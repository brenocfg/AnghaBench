#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ langid; int /*<<< orphan*/  guidProfile; int /*<<< orphan*/  catid; int /*<<< orphan*/  clsid; } ;
typedef  TYPE_1__ TF_LANGUAGEPROFILE ;
typedef  int /*<<< orphan*/  IEnumTfLanguageProfiles ;
typedef  scalar_t__ HRESULT ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CLSID_FakeService ; 
 scalar_t__ E_INVALIDARG ; 
 int FALSE ; 
 int /*<<< orphan*/  GUID_NULL ; 
 int /*<<< orphan*/  GUID_TFCAT_TIP_KEYBOARD ; 
 scalar_t__ IEnumTfLanguageProfiles_Next (int /*<<< orphan*/ *,int,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IEnumTfLanguageProfiles_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ ITfInputProcessorProfiles_EnumLanguageProfiles (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ **) ; 
 int IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 int TRUE ; 
 scalar_t__ broken (int) ; 
 scalar_t__ gLangid ; 
 int /*<<< orphan*/  g_ipp ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_EnumLanguageProfiles(void)
{
    BOOL found = FALSE;
    IEnumTfLanguageProfiles *ppEnum;
    HRESULT hr;

    hr = ITfInputProcessorProfiles_EnumLanguageProfiles(g_ipp, gLangid, NULL);
    ok(hr == E_INVALIDARG, "EnumLanguageProfiles failed: %x\n", hr);

    if (SUCCEEDED(ITfInputProcessorProfiles_EnumLanguageProfiles(g_ipp,gLangid,&ppEnum)))
    {
        TF_LANGUAGEPROFILE profile;
        while (IEnumTfLanguageProfiles_Next(ppEnum,1,&profile,NULL)==S_OK)
        {
            if (IsEqualGUID(&profile.clsid,&CLSID_FakeService))
            {
                found = TRUE;
                ok(profile.langid == gLangid, "LangId Incorrect\n");
                ok(IsEqualGUID(&profile.catid,&GUID_TFCAT_TIP_KEYBOARD) ||
                   broken(IsEqualGUID(&profile.catid,&GUID_NULL) /* Win8 */), "CatId Incorrect\n");
                ok(IsEqualGUID(&profile.guidProfile,&CLSID_FakeService), "guidProfile Incorrect\n");
            }
        }
        IEnumTfLanguageProfiles_Release(ppEnum);
    }
    ok(found,"Registered text service not found\n");
}