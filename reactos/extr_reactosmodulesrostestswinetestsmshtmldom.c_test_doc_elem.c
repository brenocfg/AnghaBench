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
typedef  int /*<<< orphan*/  IHTMLDocument3 ;
typedef  int /*<<< orphan*/  IHTMLDocument2 ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 scalar_t__ IHTMLDocument2_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IHTMLDocument2_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IHTMLDocument2_toString (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IHTMLDocument3_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IHTMLDocument3_get_documentElement (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IHTMLElement_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IHTMLDocument3 ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_doc_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_owner_doc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iface_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  strcmp_wa (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  test_elem_client_rect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_elem_tag (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  test_node_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * wine_dbgstr_w (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_doc_elem(IHTMLDocument2 *doc)
{
    IHTMLDocument2 *doc_node, *owner_doc;
    IHTMLElement *elem;
    IHTMLDocument3 *doc3;
    HRESULT hres;
    BSTR bstr;

    hres = IHTMLDocument2_QueryInterface(doc, &IID_IHTMLDocument3, (void**)&doc3);
    ok(hres == S_OK, "QueryInterface(IID_IHTMLDocument3) failed: %08x\n", hres);

    hres = IHTMLDocument2_toString(doc, &bstr);
    ok(hres == S_OK, "toString failed: %08x\n", hres);
    ok(!strcmp_wa(bstr, "[object]"),
            "toString returned %s, expected [object]\n", wine_dbgstr_w(bstr));
    SysFreeString(bstr);

    hres = IHTMLDocument3_get_documentElement(doc3, &elem);
    IHTMLDocument3_Release(doc3);
    ok(hres == S_OK, "get_documentElement failed: %08x\n", hres);

    test_node_name((IUnknown*)elem, "HTML");
    test_elem_tag((IUnknown*)elem, "HTML");

    doc_node = get_doc_node(doc);
    owner_doc = get_owner_doc((IUnknown*)elem);
    ok(iface_cmp((IUnknown *)doc_node, (IUnknown *)owner_doc), "doc_node != owner_doc\n");
    IHTMLDocument2_Release(owner_doc);

    owner_doc = get_owner_doc((IUnknown*)doc_node);
    ok(!owner_doc, "owner_doc = %p\n", owner_doc);
    IHTMLDocument2_Release(doc_node);

    test_elem_client_rect((IUnknown*)elem);

    IHTMLElement_Release(elem);
}