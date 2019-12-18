#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * member_0; } ;
struct unk_impl {int member_1; int ref; int /*<<< orphan*/  inner_unk; int /*<<< orphan*/  IUnknown_iface; int /*<<< orphan*/ * member_2; TYPE_1__ member_0; } ;
struct TYPE_4__ {int /*<<< orphan*/ * member_0; } ;
struct ITextHostTestImpl {int member_1; int /*<<< orphan*/  ITextHost_iface; TYPE_2__ member_0; } ;
typedef  int ULONG ;
typedef  int /*<<< orphan*/  ITextServices ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int ITextServices_AddRef (int /*<<< orphan*/ *) ; 
 int ITextServices_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IUnknown_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  itextHostVtbl ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ pCreateTextServices (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pIID_ITextServices ; 
 int /*<<< orphan*/  unk_vtbl ; 

__attribute__((used)) static void test_COM(void)
{
    struct unk_impl unk_obj = {{&unk_vtbl}, 19, NULL};
    struct ITextHostTestImpl texthost = {{&itextHostVtbl}, 1};
    ITextServices *textsrv;
    ULONG refcount;
    HRESULT hr;

    /* COM aggregation */
    hr = pCreateTextServices(&unk_obj.IUnknown_iface, &texthost.ITextHost_iface,
                             &unk_obj.inner_unk);
    ok(hr == S_OK, "CreateTextServices failed: %08x\n", hr);
    hr = IUnknown_QueryInterface(unk_obj.inner_unk, pIID_ITextServices, (void**)&textsrv);
    ok(hr == S_OK, "QueryInterface for IID_ITextServices failed: %08x\n", hr);
    refcount = ITextServices_AddRef(textsrv);
    ok(refcount == unk_obj.ref, "CreateTextServices just pretends to support COM aggregation\n");
    refcount = ITextServices_Release(textsrv);
    ok(refcount == unk_obj.ref, "CreateTextServices just pretends to support COM aggregation\n");
    refcount = ITextServices_Release(textsrv);
    ok(refcount == 19, "Refcount should be back at 19 but is %u\n", refcount);

    IUnknown_Release(unk_obj.inner_unk);
}