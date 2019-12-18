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
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  COINIT_APARTMENTTHREADED ; 
 int /*<<< orphan*/  CoUninitialize () ; 
 scalar_t__ OleInitialize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OleUninitialize () ; 
 scalar_t__ S_FALSE ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ pCoInitializeEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_CoInitializeEx(void)
{
    HRESULT hr;

    hr = pCoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
    ok(hr == S_OK, "CoInitializeEx failed with error 0x%08x\n", hr);

    /* Calling OleInitialize for the first time should yield S_OK even with
     * apartment already initialized by previous CoInitialize(Ex) calls. */
    hr = OleInitialize(NULL);
    ok(hr == S_OK, "OleInitialize failed with error 0x%08x\n", hr);

    /* Subsequent calls to OleInitialize should return S_FALSE */
    hr = OleInitialize(NULL);
    ok(hr == S_FALSE, "Expected S_FALSE, hr = 0x%08x\n", hr);

    /* Cleanup */
    CoUninitialize();
    OleUninitialize();
    OleUninitialize();
}