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
typedef  int /*<<< orphan*/  IMessageFilter ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  COINIT_APARTMENTTHREADED ; 
 int /*<<< orphan*/  COINIT_MULTITHREADED ; 
 scalar_t__ CO_E_NOT_SUPPORTED ; 
 scalar_t__ CoRegisterMessageFilter (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  CoUninitialize () ; 
 int /*<<< orphan*/  MessageFilter ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  ok_ole_success (scalar_t__,char*) ; 
 int /*<<< orphan*/  pCoInitializeEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_CoRegisterMessageFilter(void)
{
    HRESULT hr;
    IMessageFilter *prev_filter;

    hr = CoRegisterMessageFilter(&MessageFilter, &prev_filter);
    ok(hr == CO_E_NOT_SUPPORTED,
        "CoRegisterMessageFilter should have failed with CO_E_NOT_SUPPORTED instead of 0x%08x\n",
        hr);

    pCoInitializeEx(NULL, COINIT_MULTITHREADED);
    prev_filter = (IMessageFilter *)0xdeadbeef;
    hr = CoRegisterMessageFilter(&MessageFilter, &prev_filter);
    ok(hr == CO_E_NOT_SUPPORTED,
        "CoRegisterMessageFilter should have failed with CO_E_NOT_SUPPORTED instead of 0x%08x\n",
        hr);
    ok(prev_filter == (IMessageFilter *)0xdeadbeef,
        "prev_filter should have been set to %p\n", prev_filter);
    CoUninitialize();

    pCoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

    hr = CoRegisterMessageFilter(NULL, NULL);
    ok_ole_success(hr, "CoRegisterMessageFilter");

    prev_filter = (IMessageFilter *)0xdeadbeef;
    hr = CoRegisterMessageFilter(NULL, &prev_filter);
    ok_ole_success(hr, "CoRegisterMessageFilter");
    ok(prev_filter == NULL, "prev_filter should have been set to NULL instead of %p\n", prev_filter);

    hr = CoRegisterMessageFilter(&MessageFilter, &prev_filter);
    ok_ole_success(hr, "CoRegisterMessageFilter");
    ok(prev_filter == NULL, "prev_filter should have been set to NULL instead of %p\n", prev_filter);

    hr = CoRegisterMessageFilter(NULL, NULL);
    ok_ole_success(hr, "CoRegisterMessageFilter");

    CoUninitialize();
}