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
typedef  int /*<<< orphan*/  IHTMLDocument3 ;
typedef  int /*<<< orphan*/  IHTMLDocument2 ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ IHTMLDocument2_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IHTMLDocument3_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IHTMLDocument3_createDocumentFragment (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IID_IHTMLDocument3 ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static IHTMLDocument2 *create_docfrag(IHTMLDocument2 *doc)
{
    IHTMLDocument2 *frag;
    IHTMLDocument3 *doc3;
    HRESULT hres;

    hres = IHTMLDocument2_QueryInterface(doc, &IID_IHTMLDocument3, (void**)&doc3);
    ok(hres == S_OK, "Could not get IHTMLDocument3 iface: %08x\n", hres);

    hres = IHTMLDocument3_createDocumentFragment(doc3, &frag);
    IHTMLDocument3_Release(doc3);
    ok(hres == S_OK, "createDocumentFragment failed: %08x\n", hres);
    ok(frag != NULL, "frag == NULL\n");

    return frag;
}