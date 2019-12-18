#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_1__ IUnknown ;
typedef  int /*<<< orphan*/  IClassFactory ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  CLSID ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_CALLED (int /*<<< orphan*/ ) ; 
 scalar_t__ CLASS_E_NOAGGREGATION ; 
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 scalar_t__ CoGetClassObject (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ IClassFactory_CreateInstance (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IClassFactory_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IClassFactory ; 
 int /*<<< orphan*/  IID_IInternetProtocol ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 scalar_t__ IUnknown_QueryInterface (TYPE_1__*,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IUnknown_Release (TYPE_1__*) ; 
 int /*<<< orphan*/  SET_EXPECT (int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  outer_QI_test ; 
 int /*<<< orphan*/  outer_test_iid ; 
 int /*<<< orphan*/  outer_vtbl ; 

__attribute__((used)) static void test_com_aggregation(const CLSID *clsid)
{
    IUnknown outer = { &outer_vtbl };
    IClassFactory *class_factory;
    IUnknown *unk, *unk2, *unk3;
    HRESULT hres;

    hres = CoGetClassObject(clsid, CLSCTX_INPROC_SERVER, NULL, &IID_IClassFactory, (void**)&class_factory);
    ok(hres == S_OK, "CoGetClassObject failed: %08x\n", hres);

    hres = IClassFactory_CreateInstance(class_factory, &outer, &IID_IUnknown, (void**)&unk);
    ok(hres == S_OK, "CreateInstance returned: %08x\n", hres);

    hres = IUnknown_QueryInterface(unk, &IID_IInternetProtocol, (void**)&unk2);
    ok(hres == S_OK, "Could not get IDispatch iface: %08x\n", hres);

    SET_EXPECT(outer_QI_test);
    hres = IUnknown_QueryInterface(unk2, &outer_test_iid, (void**)&unk3);
    CHECK_CALLED(outer_QI_test);
    ok(hres == S_OK, "Could not get IInternetProtocol iface: %08x\n", hres);
    ok(unk3 == (IUnknown*)0xdeadbeef, "unexpected unk2\n");

    IUnknown_Release(unk2);
    IUnknown_Release(unk);

    unk = (void*)0xdeadbeef;
    hres = IClassFactory_CreateInstance(class_factory, &outer, &IID_IInternetProtocol, (void**)&unk);
    ok(hres == CLASS_E_NOAGGREGATION, "CreateInstance returned: %08x\n", hres);
    ok(!unk, "unk = %p\n", unk);

    IClassFactory_Release(class_factory);
}