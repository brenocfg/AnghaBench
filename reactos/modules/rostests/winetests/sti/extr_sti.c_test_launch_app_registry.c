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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  IStillImageW ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_ACCESSDENIED ; 
 int /*<<< orphan*/  GetModuleHandleA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStillImage_RegisterLaunchApplication (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  IStillImage_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStillImage_UnregisterLaunchApplication (int /*<<< orphan*/ *,char*) ; 
 int STI_VERSION_FLAG_UNICODE ; 
 int STI_VERSION_REAL ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (scalar_t__,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pStiCreateInstance (int /*<<< orphan*/ ,int,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pStiCreateInstanceW ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_launch_app_registry(void)
{
    static WCHAR appName[] = {'w','i','n','e','s','t','i','t','e','s','t','a','p','p',0};
    IStillImageW *pStiW = NULL;
    HRESULT hr;

    if (pStiCreateInstanceW == NULL)
    {
        win_skip("No StiCreateInstanceW function\n");
        return;
    }

    hr = pStiCreateInstance(GetModuleHandleA(NULL), STI_VERSION_REAL | STI_VERSION_FLAG_UNICODE, &pStiW, NULL);
    if (SUCCEEDED(hr))
    {
        hr = IStillImage_RegisterLaunchApplication(pStiW, appName, appName);
        if (hr == E_ACCESSDENIED)
            skip("Not authorized to register a launch application\n");
        else if (SUCCEEDED(hr))
        {
            hr = IStillImage_UnregisterLaunchApplication(pStiW, appName);
            ok(SUCCEEDED(hr), "could not unregister launch application, error 0x%X\n", hr);
        }
        else
            ok(0, "could not register launch application, error 0x%X\n", hr);
        IStillImage_Release(pStiW);
    }
    else
        ok(0, "could not create StillImageW, hr = 0x%X\n", hr);
}