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
typedef  int /*<<< orphan*/  elem_type_t ;
typedef  int /*<<< orphan*/  all_types ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  void IHTMLLocation ;
typedef  int /*<<< orphan*/  IHTMLElementCollection ;
typedef  int /*<<< orphan*/  IHTMLElement ;
typedef  int /*<<< orphan*/  IHTMLDocument2 ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DIID_DispHTMLDocument ; 
#define  ET_BODY 133 
#define  ET_BR 132 
#define  ET_DIV 131 
#define  ET_HEAD 130 
#define  ET_HTML 129 
#define  ET_TITLE 128 
 scalar_t__ E_UNEXPECTED ; 
 int /*<<< orphan*/  IHTMLDocument2_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IHTMLDocument2_get_all (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ IHTMLDocument2_get_body (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ IHTMLDocument2_get_location (int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IHTMLElementCollection_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IHTMLElement_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * create_docfrag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_doc_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_elem_by_id (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_owner_doc (int /*<<< orphan*/ *) ; 
 int iface_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/ * test_create_elem (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  test_disp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  test_elem_collection (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  test_elem_source_index (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  test_node_append_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_docfrag(IHTMLDocument2 *doc)
{
    IHTMLDocument2 *frag, *owner_doc, *doc_node;
    IHTMLElement *div, *body, *br;
    IHTMLElementCollection *col;
    IHTMLLocation *location;
    HRESULT hres;

    static const elem_type_t all_types[] = {
        ET_HTML,
        ET_HEAD,
        ET_TITLE,
        ET_BODY,
        ET_DIV,
        ET_BR
    };

    frag = create_docfrag(doc);

    test_disp((IUnknown*)frag, &DIID_DispHTMLDocument, "[object]");

    body = (void*)0xdeadbeef;
    hres = IHTMLDocument2_get_body(frag, &body);
    ok(hres == S_OK, "get_body failed: %08x\n", hres);
    ok(!body, "body != NULL\n");

    location = (void*)0xdeadbeef;
    hres = IHTMLDocument2_get_location(frag, &location);
    ok(hres == E_UNEXPECTED, "get_location failed: %08x\n", hres);
    ok(location == (void*)0xdeadbeef, "location changed\n");

    br = test_create_elem(doc, "BR");
    test_elem_source_index(br, -1);
    test_node_append_child((IUnknown*)frag, (IUnknown*)br);
    test_elem_source_index(br, 0);
    IHTMLElement_Release(br);

    div = get_elem_by_id(doc, "divid", TRUE);
    test_node_append_child((IUnknown*)div, (IUnknown*)frag);
    IHTMLElement_Release(div);

    hres = IHTMLDocument2_get_all(doc, &col);
    ok(hres == S_OK, "get_all failed: %08x\n", hres);
    test_elem_collection((IUnknown*)col, all_types, sizeof(all_types)/sizeof(all_types[0]));
    IHTMLElementCollection_Release(col);

    div = test_create_elem(frag, "div");
    owner_doc = get_owner_doc((IUnknown*)div);
    doc_node = get_doc_node(doc);
    ok(iface_cmp((IUnknown*)owner_doc, (IUnknown*)doc_node), "owner_doc != doc_node\n");
    IHTMLDocument2_Release(doc_node);
    IHTMLDocument2_Release(owner_doc);
    IHTMLElement_Release(div);

    IHTMLDocument2_Release(frag);
}