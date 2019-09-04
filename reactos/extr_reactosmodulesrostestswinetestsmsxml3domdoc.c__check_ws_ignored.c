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
typedef  int /*<<< orphan*/  IXMLDOMNodeList ;
typedef  int /*<<< orphan*/  IXMLDOMNode ;
typedef  int /*<<< orphan*/  IXMLDOMDocument2 ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  IXMLDOMDocument2_selectNodes (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IXMLDOMNodeList_get_item (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IXMLDOMNodeList_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IXMLDOMNode_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IXMLDOMNode_get_childNodes (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IXMLDOMNode_get_text (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _bstr_ (char*) ; 
 int /*<<< orphan*/  helper_expect_bstr_and_release (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  helper_expect_list_and_release (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  helper_ole_check_ver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void _check_ws_ignored(int line, const char *ver, IXMLDOMDocument2* doc, char const* str)
{
    IXMLDOMNode *node1, *node2;
    IXMLDOMNodeList *list;
    BSTR bstr;

    helper_ole_check_ver(IXMLDOMDocument2_selectNodes(doc, _bstr_("//*[local-name()='html']"), &list));
    helper_ole_check_ver(IXMLDOMNodeList_get_item(list, 0, &node1));
    helper_ole_check_ver(IXMLDOMNodeList_get_item(list, 1, &node2));
    helper_ole_check_ver(IXMLDOMNodeList_reset(list));
    helper_expect_list_and_release(list, "E1.E5.E1.E2.D1 E2.E5.E1.E2.D1");

    helper_ole_check_ver(IXMLDOMNode_get_childNodes(node1, &list));
    helper_expect_list_and_release(list,
            "[4]1.E1.E5.E1.E2.D1 T2.E1.E5.E1.E2.D1 E3.E1.E5.E1.E2.D1 "
            "E4.E1.E5.E1.E2.D1 E5.E1.E5.E1.E2.D1 E6.E1.E5.E1.E2.D1");
    helper_ole_check_ver(IXMLDOMNode_get_text(node1, &bstr));
    if (str)
    {
        helper_expect_bstr_and_release(bstr, str);
    }
    else
    {
        helper_expect_bstr_and_release(bstr, " This is a description.");
    }
    IXMLDOMNode_Release(node1);

    helper_ole_check_ver(IXMLDOMNode_get_childNodes(node2, &list));
    helper_expect_list_and_release(list,
            "T1.E2.E5.E1.E2.D1 E2.E2.E5.E1.E2.D1 T3.E2.E5.E1.E2.D1 "
            "E4.E2.E5.E1.E2.D1 T5.E2.E5.E1.E2.D1 E6.E2.E5.E1.E2.D1 T7.E2.E5.E1.E2.D1");
    helper_ole_check_ver(IXMLDOMNode_get_text(node2, &bstr));
    helper_expect_bstr_and_release(bstr,
            "\n                This is a description with preserved whitespace. \n            ");
    IXMLDOMNode_Release(node2);
}