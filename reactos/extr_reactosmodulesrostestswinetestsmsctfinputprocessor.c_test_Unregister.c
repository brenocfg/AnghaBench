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
 int /*<<< orphan*/  ITfInputProcessorProfiles_Unregister (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnregisterTextService () ; 
 int /*<<< orphan*/  g_ipp ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_Unregister(void)
{
    HRESULT hr;
    hr = ITfInputProcessorProfiles_Unregister(g_ipp, &CLSID_FakeService);
    ok(SUCCEEDED(hr),"Unable to unregister text service(%x)\n",hr);
    UnregisterTextService();
}