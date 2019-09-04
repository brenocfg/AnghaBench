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
typedef  int ULONG ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  ITextServices ;
typedef  int /*<<< orphan*/  ITextHost ;
typedef  int /*<<< orphan*/  ITextDocument ;
typedef  int /*<<< orphan*/  IRichEditOle ;
typedef  int HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  IID_IRichEditOle ; 
 int /*<<< orphan*/  IID_ITextDocument ; 
 int IRichEditOle_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IRichEditOle_Release (int /*<<< orphan*/ *) ; 
 int ITextDocument_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  ITextDocument_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITextHost_Release (int /*<<< orphan*/ *) ; 
 int ITextServices_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  ITextServices_Release (int /*<<< orphan*/ *) ; 
 int S_OK ; 
 int get_refcount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_texthost (int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 

__attribute__((used)) static void test_QueryInterface(void)
{
    ITextServices *txtserv;
    ITextHost *host;
    HRESULT hres;
    IRichEditOle *reole, *txtsrv_reole;
    ITextDocument *txtdoc, *txtsrv_txtdoc;
    ULONG refcount;

    if(!init_texthost(&txtserv, &host))
        return;

    refcount = get_refcount((IUnknown *)txtserv);
    ok(refcount == 1, "got wrong ref count: %d\n", refcount);

    /* IID_IRichEditOle */
    hres = ITextServices_QueryInterface(txtserv, &IID_IRichEditOle, (void **)&txtsrv_reole);
    ok(hres == S_OK, "ITextServices_QueryInterface: 0x%08x\n", hres);
    refcount = get_refcount((IUnknown *)txtserv);
    ok(refcount == 2, "got wrong ref count: %d\n", refcount);
    refcount = get_refcount((IUnknown *)txtsrv_reole);
    ok(refcount == 2, "got wrong ref count: %d\n", refcount);

    hres = IRichEditOle_QueryInterface(txtsrv_reole, &IID_ITextDocument, (void **)&txtdoc);
    ok(hres == S_OK, "IRichEditOle_QueryInterface: 0x%08x\n", hres);
    refcount = get_refcount((IUnknown *)txtserv);
    ok(refcount == 3, "got wrong ref count: %d\n", refcount);
    refcount = get_refcount((IUnknown *)txtsrv_reole);
    ok(refcount == 3, "got wrong ref count: %d\n", refcount);

    ITextDocument_Release(txtdoc);
    refcount = get_refcount((IUnknown *)txtserv);
    ok(refcount == 2, "got wrong ref count: %d\n", refcount);
    IRichEditOle_Release(txtsrv_reole);
    refcount = get_refcount((IUnknown *)txtserv);
    ok(refcount == 1, "got wrong ref count: %d\n", refcount);

    /* IID_ITextDocument */
    hres = ITextServices_QueryInterface(txtserv, &IID_ITextDocument, (void **)&txtsrv_txtdoc);
    ok(hres == S_OK, "ITextServices_QueryInterface: 0x%08x\n", hres);
    refcount = get_refcount((IUnknown *)txtserv);
    ok(refcount == 2, "got wrong ref count: %d\n", refcount);
    refcount = get_refcount((IUnknown *)txtsrv_txtdoc);
    ok(refcount == 2, "got wrong ref count: %d\n", refcount);

    hres = ITextDocument_QueryInterface(txtsrv_txtdoc, &IID_IRichEditOle, (void **)&reole);
    ok(hres == S_OK, "ITextDocument_QueryInterface: 0x%08x\n", hres);
    refcount = get_refcount((IUnknown *)txtserv);
    ok(refcount == 3, "got wrong ref count: %d\n", refcount);
    refcount = get_refcount((IUnknown *)txtsrv_txtdoc);
    ok(refcount == 3, "got wrong ref count: %d\n", refcount);

    IRichEditOle_Release(reole);
    refcount = get_refcount((IUnknown *)txtserv);
    ok(refcount == 2, "got wrong ref count: %d\n", refcount);
    ITextDocument_Release(txtsrv_txtdoc);
    refcount = get_refcount((IUnknown *)txtserv);
    ok(refcount == 1, "got wrong ref count: %d\n", refcount);

    ITextServices_Release(txtserv);
    ITextHost_Release(host);
}