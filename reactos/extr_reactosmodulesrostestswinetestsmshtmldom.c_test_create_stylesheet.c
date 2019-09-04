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
typedef  int /*<<< orphan*/  all_types2 ;
typedef  int /*<<< orphan*/  all_types ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IHTMLStyleSheet ;
typedef  int /*<<< orphan*/  IHTMLStyleElement ;
typedef  int /*<<< orphan*/  IHTMLElement ;
typedef  int /*<<< orphan*/  IHTMLDocument2 ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
#define  ET_BODY 133 
#define  ET_DIV 132 
#define  ET_HEAD 131 
#define  ET_HTML 130 
#define  ET_STYLE 129 
#define  ET_TITLE 128 
 scalar_t__ IHTMLDocument2_createStyleSheet (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 
 scalar_t__ IHTMLElement_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IHTMLElement_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IHTMLStyleElement_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IHTMLStyleElement_get_styleSheet (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IHTMLStyleSheet_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IHTMLStyleElement ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/ * get_doc_elem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iface_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  test_doc_all (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  test_elem_getelembytag (int /*<<< orphan*/ *,int /*<<< orphan*/  const,int,int /*<<< orphan*/ **) ; 

__attribute__((used)) static void test_create_stylesheet(IHTMLDocument2 *doc)
{
    IHTMLStyleSheet *stylesheet, *stylesheet2;
    IHTMLStyleElement *style_elem;
    IHTMLElement *doc_elem, *elem;
    HRESULT hres;

    static const elem_type_t all_types[] = {
        ET_HTML,
        ET_HEAD,
        ET_TITLE,
        ET_BODY,
        ET_DIV
    };

    static const elem_type_t all_types2[] = {
        ET_HTML,
        ET_HEAD,
        ET_TITLE,
        ET_STYLE,
        ET_BODY,
        ET_DIV
    };

    test_doc_all(doc, all_types, sizeof(all_types)/sizeof(*all_types));

    hres = IHTMLDocument2_createStyleSheet(doc, NULL, -1, &stylesheet);
    ok(hres == S_OK, "createStyleSheet failed: %08x\n", hres);

    test_doc_all(doc, all_types2, sizeof(all_types2)/sizeof(*all_types2));

    doc_elem = get_doc_elem(doc);

    test_elem_getelembytag((IUnknown*)doc_elem, ET_STYLE, 1, &elem);
    IHTMLElement_Release(doc_elem);

    hres = IHTMLElement_QueryInterface(elem, &IID_IHTMLStyleElement, (void**)&style_elem);
    IHTMLElement_Release(elem);
    ok(hres == S_OK, "Could not get IHTMLStyleElement iface: %08x\n", hres);

    stylesheet2 = NULL;
    hres = IHTMLStyleElement_get_styleSheet(style_elem, &stylesheet2);
    ok(hres == S_OK, "get_styleSheet failed: %08x\n", hres);
    ok(stylesheet2 != NULL, "stylesheet2 == NULL\n");
    ok(iface_cmp((IUnknown*)stylesheet, (IUnknown*)stylesheet2), "stylesheet != stylesheet2\n");

    IHTMLStyleSheet_Release(stylesheet2);
    IHTMLStyleSheet_Release(stylesheet);

    IHTMLStyleElement_Release(style_elem);
}