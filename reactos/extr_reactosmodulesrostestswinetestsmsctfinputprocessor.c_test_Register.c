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
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (float const*) ; 
 int /*<<< orphan*/  CLSID_FakeService ; 
 int /*<<< orphan*/  ITfInputProcessorProfiles_AddLanguageProfile (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,float const*,int /*<<< orphan*/ ,float const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ITfInputProcessorProfiles_GetCurrentLanguage (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITfInputProcessorProfiles_Register (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegisterTextService (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gLangid ; 
 int /*<<< orphan*/  g_ipp ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  trace (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_Register(void)
{
    HRESULT hr;

    static const WCHAR szDesc[] = {'F','a','k','e',' ','W','i','n','e',' ','S','e','r','v','i','c','e',0};
    static const WCHAR szFile[] = {'F','a','k','e',' ','W','i','n','e',' ','S','e','r','v','i','c','e',' ','F','i','l','e',0};

    hr = ITfInputProcessorProfiles_GetCurrentLanguage(g_ipp,&gLangid);
    ok(SUCCEEDED(hr),"Unable to get current language id\n");
    trace("Current Language %x\n",gLangid);

    hr = RegisterTextService(&CLSID_FakeService);
    ok(SUCCEEDED(hr),"Unable to register COM for TextService\n");
    hr = ITfInputProcessorProfiles_Register(g_ipp, &CLSID_FakeService);
    ok(SUCCEEDED(hr),"Unable to register text service(%x)\n",hr);
    hr = ITfInputProcessorProfiles_AddLanguageProfile(g_ipp, &CLSID_FakeService, gLangid,
            &CLSID_FakeService, szDesc, ARRAY_SIZE(szDesc), szFile, ARRAY_SIZE(szFile), 1);
    ok(SUCCEEDED(hr),"Unable to add Language Profile (%x)\n",hr);
}