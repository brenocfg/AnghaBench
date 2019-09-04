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
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CLSID_FakeService ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  ITfInputProcessorProfiles_EnableLanguageProfile (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ITfInputProcessorProfiles_IsEnabledLanguageProfile (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 int SUCCEEDED (int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  gLangid ; 
 int /*<<< orphan*/  g_ipp ; 
 int /*<<< orphan*/  ok (int,char*) ; 

__attribute__((used)) static void test_Enable(void)
{
    HRESULT hr;
    BOOL enabled = FALSE;

    hr = ITfInputProcessorProfiles_EnableLanguageProfile(g_ipp,&CLSID_FakeService, gLangid, &CLSID_FakeService, TRUE);
    ok(SUCCEEDED(hr),"Failed to enable text service\n");
    hr = ITfInputProcessorProfiles_IsEnabledLanguageProfile(g_ipp,&CLSID_FakeService, gLangid, &CLSID_FakeService, &enabled);
    ok(SUCCEEDED(hr),"Failed to get enabled state\n");
    ok(enabled == TRUE,"enabled state incorrect\n");
}