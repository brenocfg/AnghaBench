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

/* Variables and functions */
 unsigned int ARRAY_SIZE (scalar_t__) ; 
 scalar_t__ CLASS_E_NOAGGREGATION ; 
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_IMimeHtmlProtocol ; 
 scalar_t__ CoGetClassObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ E_NOINTERFACE ; 
 scalar_t__ IClassFactory_CreateInstance (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IClassFactory_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IClassFactory ; 
 int /*<<< orphan*/  IID_IInternetProtocol ; 
 int /*<<< orphan*/  IID_IInternetProtocolInfo ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 scalar_t__ IUnknown_QueryInterface (TYPE_1__*,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IUnknown_Release (TYPE_1__*) ; 
 scalar_t__ S_OK ; 
 scalar_t__ binding_tests ; 
 int /*<<< orphan*/  broken_mhtml_resolver ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  outer_vtbl ; 
 int /*<<< orphan*/  test_mhtml_protocol_binding (scalar_t__) ; 
 int /*<<< orphan*/  test_mhtml_protocol_info () ; 

__attribute__((used)) static void test_mhtml_protocol(void)
{
    IUnknown outer = { &outer_vtbl };
    IClassFactory *class_factory;
    IUnknown *unk, *unk2;
    unsigned i;
    HRESULT hres;

    /* test class factory */
    hres = CoGetClassObject(&CLSID_IMimeHtmlProtocol, CLSCTX_INPROC_SERVER, NULL, &IID_IUnknown, (void**)&unk);
    ok(hres == S_OK, "CoGetClassObject failed: %08x\n", hres);

    hres = IUnknown_QueryInterface(unk, &IID_IInternetProtocolInfo, (void**)&unk2);
    ok(hres == E_NOINTERFACE, "IInternetProtocolInfo supported\n");

    hres = IUnknown_QueryInterface(unk, &IID_IClassFactory, (void**)&class_factory);
    ok(hres == S_OK, "Could not get IClassFactory iface: %08x\n", hres);
    IUnknown_Release(unk);

    hres = IClassFactory_CreateInstance(class_factory, &outer, &IID_IUnknown, (void**)&unk);
    ok(hres == S_OK, "CreateInstance returned: %08x\n", hres);
    hres = IUnknown_QueryInterface(unk, &IID_IInternetProtocol, (void**)&unk2);
    ok(hres == S_OK, "Could not get IInternetProtocol iface: %08x\n", hres);
    IUnknown_Release(unk2);
    IUnknown_Release(unk);

    hres = IClassFactory_CreateInstance(class_factory, (IUnknown*)0xdeadbeef, &IID_IInternetProtocol, (void**)&unk2);
    ok(hres == CLASS_E_NOAGGREGATION, "CreateInstance returned: %08x\n", hres);

    IClassFactory_Release(class_factory);

    if(!broken_mhtml_resolver)
        test_mhtml_protocol_info();

    for(i = 0; i < ARRAY_SIZE(binding_tests); i++)
        test_mhtml_protocol_binding(binding_tests + i);
}