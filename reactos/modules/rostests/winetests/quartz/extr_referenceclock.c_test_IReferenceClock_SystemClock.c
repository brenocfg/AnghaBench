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
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  IReferenceClock ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_SystemClock ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IReferenceClock ; 
 int /*<<< orphan*/  IReferenceClock_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  test_IReferenceClock_methods (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_IReferenceClock_query_interface (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_IReferenceClock_SystemClock(void)
{
    IReferenceClock * pReferenceClock;
    HRESULT hr;

    hr = CoCreateInstance(&CLSID_SystemClock, NULL, CLSCTX_INPROC_SERVER, &IID_IReferenceClock, (LPVOID*)&pReferenceClock);
    ok(hr == S_OK, "Unable to create reference clock from system clock %x\n", hr);
    if (hr == S_OK)
    {
        test_IReferenceClock_query_interface("SystemClock", pReferenceClock);
	test_IReferenceClock_methods("SystemClock", pReferenceClock);
	IReferenceClock_Release(pReferenceClock);
    }
}