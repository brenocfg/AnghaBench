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
typedef  int /*<<< orphan*/  IServiceProvider ;
typedef  int /*<<< orphan*/  IHTMLDocument3 ;
typedef  int /*<<< orphan*/  IHTMLDocument2 ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ IHTMLDocument2_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IHTMLDocument2_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IHTMLDocument3_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IHTMLDocument2 ; 
 int /*<<< orphan*/  IID_IHTMLDocument3 ; 
 int /*<<< orphan*/  IID_IHTMLEditServices ; 
 int /*<<< orphan*/  IID_IServiceProvider ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 scalar_t__ IServiceProvider_QueryService (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IServiceProvider_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SID_SContainerDispatch ; 
 int /*<<< orphan*/  SID_SHTMLEditServices ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/ * create_document () ; 
 int /*<<< orphan*/  iface_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  release_document (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_ServiceProvider(void)
{
    IHTMLDocument3 *doc3, *doc3_2;
    IServiceProvider *provider;
    IHTMLDocument2 *doc, *doc2;
    IUnknown *unk;
    HRESULT hres;

    doc = create_document();
    if(!doc)
        return;

    hres = IHTMLDocument2_QueryInterface(doc, &IID_IServiceProvider, (void**)&provider);
    ok(hres == S_OK, "got 0x%08x\n", hres);

    hres = IServiceProvider_QueryService(provider, &SID_SContainerDispatch, &IID_IHTMLDocument2, (void**)&doc2);
    ok(hres == S_OK, "got 0x%08x\n", hres);
    ok(iface_cmp((IUnknown*)doc2, (IUnknown*)doc), "got wrong pointer\n");
    IHTMLDocument2_Release(doc2);

    hres = IServiceProvider_QueryService(provider, &SID_SContainerDispatch, &IID_IHTMLDocument3, (void**)&doc3);
    ok(hres == S_OK, "got 0x%08x\n", hres);
    ok(iface_cmp((IUnknown*)doc3, (IUnknown*)doc), "got wrong pointer\n");

    hres = IHTMLDocument2_QueryInterface(doc, &IID_IHTMLDocument3, (void**)&doc3_2);
    ok(hres == S_OK, "got 0x%08x\n", hres);
    ok(iface_cmp((IUnknown*)doc3_2, (IUnknown*)doc), "got wrong pointer\n");
    ok(iface_cmp((IUnknown*)doc3_2, (IUnknown*)doc3), "got wrong pointer\n");
    IHTMLDocument3_Release(doc3);
    IHTMLDocument3_Release(doc3_2);

    hres = IServiceProvider_QueryService(provider, &SID_SContainerDispatch, &IID_IUnknown, (void**)&unk);
    ok(hres == S_OK, "got 0x%08x\n", hres);
    ok(iface_cmp((IUnknown*)doc, unk), "got wrong pointer\n");
    IUnknown_Release(unk);

    hres = IServiceProvider_QueryService(provider, &SID_SHTMLEditServices, &IID_IHTMLEditServices, (void**)&unk);
    ok(hres == S_OK, "QueryService(HTMLEditServices) failed: %08x\n", hres);
    IUnknown_Release(unk);

    IServiceProvider_Release(provider);
    release_document(doc);
}