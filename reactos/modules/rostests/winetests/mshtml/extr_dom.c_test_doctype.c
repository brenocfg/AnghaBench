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
typedef  int /*<<< orphan*/  IHTMLDocument2 ;
typedef  int /*<<< orphan*/  IHTMLDOMNode ;

/* Variables and functions */
 int /*<<< orphan*/  ET_COMMENT ; 
 int /*<<< orphan*/  IHTMLDOMNode_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IHTMLDocument2_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_doc_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_first_child (int /*<<< orphan*/ *) ; 
 int get_node_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/  test_comment_text (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  test_elem_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_doctype(IHTMLDocument2 *doc)
{
    IHTMLDocument2 *doc_node;
    IHTMLDOMNode *doctype;
    int type;

    doc_node = get_doc_node(doc);
    doctype = get_first_child((IUnknown*)doc_node);
    IHTMLDocument2_Release(doc_node);

    type = get_node_type((IUnknown*)doctype);
    ok(type == 8, "type = %d\n", type);

    test_comment_text((IUnknown*)doctype, "<!DOCTYPE html>");
    test_elem_type((IUnknown*)doctype, ET_COMMENT);
    IHTMLDOMNode_Release(doctype);
}