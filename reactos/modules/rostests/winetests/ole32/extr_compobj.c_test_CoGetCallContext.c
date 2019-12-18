#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_9__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_8__ {int refs; TYPE_2__ IUnknown_iface; } ;
typedef  TYPE_1__ Test_CallContext ;
typedef  TYPE_2__ IUnknown ;
typedef  int HRESULT ;

/* Variables and functions */
 int CoGetCallContext (int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  CoInitialize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CoUninitialize () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 int IUnknown_AddRef (TYPE_2__*) ; 
 int /*<<< orphan*/  IUnknown_Release (TYPE_2__*) ; 
 int RPC_E_CALL_COMPLETE ; 
 int /*<<< orphan*/  TestCallContext_Vtbl ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  ok_ole_success (int,char*) ; 
 int pCoSwitchCallContext (TYPE_2__*,TYPE_2__**) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void test_CoGetCallContext(void)
{
    HRESULT hr;
    ULONG refs;
    IUnknown *pUnk;
    Test_CallContext *test_object;

    if (!pCoSwitchCallContext)
    {
        skip("CoSwitchCallContext not present\n");
        return;
    }

    CoInitialize(NULL);

    test_object = HeapAlloc(GetProcessHeap(), 0, sizeof(Test_CallContext));
    test_object->IUnknown_iface.lpVtbl = &TestCallContext_Vtbl;
    test_object->refs = 1;

    hr = CoGetCallContext(&IID_IUnknown, (void**)&pUnk);
    ok(hr == RPC_E_CALL_COMPLETE, "Expected RPC_E_CALL_COMPLETE, got 0x%08x\n", hr);

    pUnk = (IUnknown*)0xdeadbeef;
    hr = pCoSwitchCallContext(&test_object->IUnknown_iface, &pUnk);
    ok_ole_success(hr, "CoSwitchCallContext");
    ok(pUnk == NULL, "expected NULL, got %p\n", pUnk);
    refs = IUnknown_AddRef(&test_object->IUnknown_iface);
    ok(refs == 2, "Expected refcount 2, got %d\n", refs);
    IUnknown_Release(&test_object->IUnknown_iface);

    pUnk = (IUnknown*)0xdeadbeef;
    hr = CoGetCallContext(&IID_IUnknown, (void**)&pUnk);
    ok_ole_success(hr, "CoGetCallContext");
    ok(pUnk == &test_object->IUnknown_iface, "expected %p, got %p\n",
       &test_object->IUnknown_iface, pUnk);
    refs = IUnknown_AddRef(&test_object->IUnknown_iface);
    ok(refs == 3, "Expected refcount 3, got %d\n", refs);
    IUnknown_Release(&test_object->IUnknown_iface);
    IUnknown_Release(pUnk);

    pUnk = (IUnknown*)0xdeadbeef;
    hr = pCoSwitchCallContext(NULL, &pUnk);
    ok_ole_success(hr, "CoSwitchCallContext");
    ok(pUnk == &test_object->IUnknown_iface, "expected %p, got %p\n",
       &test_object->IUnknown_iface, pUnk);
    refs = IUnknown_AddRef(&test_object->IUnknown_iface);
    ok(refs == 2, "Expected refcount 2, got %d\n", refs);
    IUnknown_Release(&test_object->IUnknown_iface);

    hr = CoGetCallContext(&IID_IUnknown, (void**)&pUnk);
    ok(hr == RPC_E_CALL_COMPLETE, "Expected RPC_E_CALL_COMPLETE, got 0x%08x\n", hr);

    IUnknown_Release(&test_object->IUnknown_iface);

    CoUninitialize();
}