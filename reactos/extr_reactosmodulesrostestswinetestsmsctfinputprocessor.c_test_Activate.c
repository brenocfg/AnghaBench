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
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  ITfInputProcessorProfiles_ActivateLanguageProfile (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  gLangid ; 
 int /*<<< orphan*/  g_ipp ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  test_ShouldActivate ; 

__attribute__((used)) static void test_Activate(void)
{
    HRESULT hr;

    test_ShouldActivate = TRUE; /* Win7 */
    hr = ITfInputProcessorProfiles_ActivateLanguageProfile(g_ipp,&CLSID_FakeService,gLangid,&CLSID_FakeService);
    ok(SUCCEEDED(hr),"Failed to Activate text service\n");
    test_ShouldActivate = FALSE;
}