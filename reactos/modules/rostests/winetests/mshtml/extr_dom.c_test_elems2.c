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
typedef  int /*<<< orphan*/  outer_types ;
typedef  int /*<<< orphan*/  elem_type_t ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IHTMLFormElement ;
typedef  int /*<<< orphan*/  IHTMLElement ;
typedef  int /*<<< orphan*/  IHTMLDocument2 ;

/* Variables and functions */
#define  ET_A 129 
#define  ET_BR 128 
 int /*<<< orphan*/  E_INVALIDARG ; 
 int /*<<< orphan*/  IHTMLElement_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IHTMLFormElement_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VARIANT_FALSE ; 
 int /*<<< orphan*/  VARIANT_TRUE ; 
 int /*<<< orphan*/ * get_doc_elem_by_id (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * get_elem_by_id (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_textarea_form (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iface_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  link_put_disabled (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link_put_href (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  link_put_rel (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  link_put_rev (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  link_put_type (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  test_attr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_blocked (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_elem_all (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  test_elem_istextedit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_elem_names (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_elem_set_innerhtml (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  test_elem_set_outerhtml (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  test_form_action (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_form_elements (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_form_encoding (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  test_form_item (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_form_length (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  test_form_method (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  test_form_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_form_put_action (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  test_form_put_encoding (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  test_form_put_method (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  test_form_put_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  test_form_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_form_target (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_input_defaultValue (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  test_input_get_form (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  test_input_put_defaultValue (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  test_input_put_value (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  test_input_value (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  test_insert_adjacent_elems (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_link_disabled (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_link_href (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  test_link_media (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  test_link_rel (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  test_link_rev (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_link_type (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  test_option_form (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_select_form (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_textarea_defaultvalue (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  test_textarea_put_defaultvalue (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  test_textarea_put_readonly (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_textarea_put_value (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  test_textarea_readonly (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_textarea_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_textarea_value (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_elems2(IHTMLDocument2 *doc)
{
    IHTMLElement *elem, *elem2, *div;

    static const elem_type_t outer_types[] = {
        ET_BR,
        ET_A
    };

    div = get_doc_elem_by_id(doc, "divid");

    elem = get_elem_by_id(doc, "linkid", TRUE);
    if(elem) {
        test_link_disabled(elem, VARIANT_FALSE);
        test_link_rel(elem, "stylesheet");
        test_link_rev(elem, NULL);
        test_link_type(elem, "text/css");
        test_link_href(elem, "about:blank");
        test_link_media(elem, "all");
        link_put_disabled(elem, VARIANT_TRUE);
        link_put_rel(elem, "prev");
        link_put_rev(elem, "next");
        link_put_type(elem, "text/plain");
        link_put_href(elem, "about:prev");
        IHTMLElement_Release(elem);
    }

    test_elem_set_innerhtml((IUnknown*)div, "<div id=\"innerid\"></div>");
    elem2 = get_doc_elem_by_id(doc, "innerid");
    ok(elem2 != NULL, "elem2 == NULL\n");
    test_elem_set_outerhtml((IUnknown*)elem2, "<br><a href=\"about:blank\" id=\"aid\">a</a>");
    test_elem_all((IUnknown*)div, outer_types, sizeof(outer_types)/sizeof(*outer_types));
    IHTMLElement_Release(elem2);

    elem2 = get_doc_elem_by_id(doc, "aid");
    ok(elem2 != NULL, "elem2 == NULL\n");
    test_elem_set_outerhtml((IUnknown*)elem2, "");
    test_elem_all((IUnknown*)div, outer_types, 1);
    IHTMLElement_Release(elem2);

    test_elem_set_innerhtml((IUnknown*)div, "<textarea id=\"ta\"></textarea>");
    elem = get_elem_by_id(doc, "ta", TRUE);
    if(elem) {
        IHTMLFormElement *form;

        test_textarea_value((IUnknown*)elem, NULL);
        test_textarea_put_value((IUnknown*)elem, "test");
        test_textarea_defaultvalue((IUnknown*)elem, NULL);
        test_textarea_put_defaultvalue((IUnknown*)elem, "defval text");
        test_textarea_put_value((IUnknown*)elem, "test");
        test_textarea_readonly((IUnknown*)elem, VARIANT_FALSE);
        test_textarea_put_readonly((IUnknown*)elem, VARIANT_TRUE);
        test_textarea_put_readonly((IUnknown*)elem, VARIANT_FALSE);
        test_textarea_type((IUnknown*)elem);

        form = get_textarea_form((IUnknown*)elem);
        ok(!form, "form = %p\n", form);

        test_elem_istextedit(elem, VARIANT_TRUE);

        IHTMLElement_Release(elem);
    }

    test_elem_set_innerhtml((IUnknown*)div, "<textarea id=\"ta\">default text</textarea>");
    elem = get_elem_by_id(doc, "ta", TRUE);
    if(elem) {
        test_textarea_defaultvalue((IUnknown*)elem, "default text");
        IHTMLElement_Release(elem);
    }

    test_elem_set_innerhtml((IUnknown*)div, "<form id=\"fid\"><textarea id=\"ta\"></textarea></form>");
    elem = get_elem_by_id(doc, "ta", TRUE);
    if(elem) {
        IHTMLFormElement *form;

        elem2 = get_elem_by_id(doc, "fid", TRUE);
        ok(elem2 != NULL, "elem2 == NULL\n");

        form = get_textarea_form((IUnknown*)elem);
        ok(form != NULL, "form = NULL\n");
        ok(iface_cmp((IUnknown*)form, (IUnknown*)elem2), "form != elem2\n");

        IHTMLFormElement_Release(form);
        IHTMLElement_Release(elem2);
        IHTMLElement_Release(elem);
    }

    test_elem_set_innerhtml((IUnknown*)div,
            "<input value=\"val\" id =\"inputid\"  />");
    elem = get_elem_by_id(doc, "inputid", TRUE);
    if(elem) {
        test_input_defaultValue((IUnknown*)elem, "val");
        test_input_put_value((IUnknown*)elem, "test");
        test_input_put_defaultValue((IUnknown*)elem, "new val");
        test_input_value((IUnknown*)elem, "test");
        IHTMLElement_Release(elem);
    }

    test_elem_set_innerhtml((IUnknown*)div, "");
    test_insert_adjacent_elems(doc, div);

    test_elem_set_innerhtml((IUnknown*)div,
            "<form id=\"form\"><input type=\"button\" /><div><input type=\"text\" id=\"inputid\"/></div></textarea>");
    elem = get_elem_by_id(doc, "form", TRUE);
    if(elem) {
        test_form_length((IUnknown*)elem, 2);
        test_form_item(elem);
        test_form_action((IUnknown*)elem, NULL);
        test_form_put_action((IUnknown*)elem, "about:blank");
        test_form_method((IUnknown*)elem, "get");
        test_form_put_method((IUnknown*)elem, S_OK, "post");
        test_form_put_method((IUnknown*)elem, E_INVALIDARG, "put");
        test_form_method((IUnknown*)elem, "post");
        test_form_name((IUnknown*)elem, NULL);
        test_form_put_name((IUnknown*)elem, "Name");
        test_form_encoding((IUnknown*)elem, "application/x-www-form-urlencoded");
        test_form_put_encoding((IUnknown*)elem, S_OK, "text/plain");
        test_form_put_encoding((IUnknown*)elem, S_OK, "multipart/form-data");
        test_form_put_encoding((IUnknown*)elem, E_INVALIDARG, "image/png");
        test_form_encoding((IUnknown*)elem, "multipart/form-data");
        test_form_elements((IUnknown*)elem);
        test_form_reset((IUnknown*)elem);
        test_form_target((IUnknown*)elem);
        IHTMLElement_Release(elem);

        elem = get_elem_by_id(doc, "inputid", TRUE);
        test_input_get_form((IUnknown*)elem, "form");
        IHTMLElement_Release(elem);
    }

    test_elem_set_innerhtml((IUnknown*)div,
            "<form id=\"form\" name=\"form_name\"><select id=\"sform\"><option id=\"oform\"></option></select></form>");
    elem = get_elem_by_id(doc, "sform", TRUE);
    elem2 = get_elem_by_id(doc, "form", TRUE);
    if(elem && elem2) {
        test_select_form((IUnknown*)elem, (IUnknown*)elem2);
        IHTMLElement_Release(elem);

        elem = get_elem_by_id(doc, "oform", TRUE);
        if(elem) {
            test_option_form((IUnknown*)elem, (IUnknown*)elem2);
            IHTMLElement_Release(elem);
        }
        IHTMLElement_Release(elem2);
    }

    test_attr(div);
    test_blocked(doc, div);
    test_elem_names(doc);

    IHTMLElement_Release(div);
}