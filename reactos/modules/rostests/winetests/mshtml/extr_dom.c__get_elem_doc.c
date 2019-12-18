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
typedef  int /*<<< orphan*/  IHTMLElement ;
typedef  int /*<<< orphan*/  IHTMLDocument2 ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ IDispatch_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IDispatch_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IHTMLElement_get_document (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IID_IHTMLDocument2 ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/ * _get_elem_iface (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static IHTMLDocument2 *_get_elem_doc(unsigned line, IUnknown *unk)
{
    IHTMLElement *elem = _get_elem_iface(line, unk);
    IHTMLDocument2 *doc;
    IDispatch *disp;
    HRESULT hres;

    disp = NULL;
    hres = IHTMLElement_get_document(elem, &disp);
    ok(hres == S_OK, "get_document failed: %08x\n", hres);
    ok(disp != NULL, "disp == NULL\n");

    hres = IDispatch_QueryInterface(disp, &IID_IHTMLDocument2, (void**)&doc);
    IDispatch_Release(disp);
    ok(hres == S_OK, "Could not get IHTMLDocument2 iface: %08x\n", hres);

    return doc;
}