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
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IReferenceClock ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ E_NOINTERFACE ; 
 int /*<<< orphan*/  IID_IDirectDraw ; 
 int /*<<< orphan*/  IID_IReferenceClock ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 scalar_t__ IReferenceClock_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_IReferenceClock_query_interface(const char * clockdesc, IReferenceClock * pClock)
{
    HRESULT hr;
    IUnknown *pF;

    hr = IReferenceClock_QueryInterface(pClock, &IID_IUnknown, (void**)&pF);
    ok(hr == S_OK, "IReferenceClock_QueryInterface returned %x\n", hr);
    ok(pF != NULL, "pF is NULL\n");
    if (SUCCEEDED(hr)) IUnknown_Release(pF);

    hr = IReferenceClock_QueryInterface(pClock, &IID_IDirectDraw, (void**)&pF);
    ok(hr == E_NOINTERFACE, "IReferenceClock_QueryInterface returned %x\n", hr);
    ok(pF == NULL, "pF is not NULL\n");

    hr = IReferenceClock_QueryInterface(pClock, &IID_IReferenceClock, (void**)&pF);
    ok(hr == S_OK, "IReferenceClock_QueryInterface returned %x\n", hr);
    ok(pF != NULL, "pF is NULL\n");
    if (SUCCEEDED(hr)) IUnknown_Release(pF);
}