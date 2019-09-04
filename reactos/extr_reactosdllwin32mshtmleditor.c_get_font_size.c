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
typedef  int /*<<< orphan*/  nsresult ;
typedef  int /*<<< orphan*/  nsISelection ;
typedef  int /*<<< orphan*/  nsIDOMNode ;
typedef  int /*<<< orphan*/  nsIDOMHTMLElement ;
typedef  int /*<<< orphan*/  nsAString ;
typedef  scalar_t__ WCHAR ;
typedef  scalar_t__ UINT16 ;
typedef  scalar_t__ PRUnichar ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  HTMLDocument ;

/* Variables and functions */
 scalar_t__ DOCUMENT_NODE ; 
 scalar_t__ ELEMENT_NODE ; 
 int /*<<< orphan*/  IID_nsIDOMHTMLElement ; 
 scalar_t__ NS_FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * debugstr_w (scalar_t__ const*) ; 
 int /*<<< orphan*/  fontW ; 
 int /*<<< orphan*/  get_elem_attr_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__ const**) ; 
 int /*<<< orphan*/ * get_ns_selection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsAString_Finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsAString_GetData (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsAString_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMHTMLElement_GetTagName (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMHTMLElement_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMNode_GetNodeType (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  nsIDOMNode_GetParentNode (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nsIDOMNode_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  nsIDOMNode_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsISelection_GetFocusNode (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nsISelection_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sizeW ; 
 int /*<<< orphan*/  strcmpiW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpyW (scalar_t__*,scalar_t__ const*) ; 

__attribute__((used)) static void get_font_size(HTMLDocument *This, WCHAR *ret)
{
    nsISelection *nsselection = get_ns_selection(This);
    nsIDOMHTMLElement *elem = NULL;
    nsIDOMNode *node = NULL, *tmp_node;
    nsAString tag_str;
    LPCWSTR tag;
    UINT16 node_type;
    nsresult nsres;

    *ret = 0;

    if(!nsselection)
        return;

    nsISelection_GetFocusNode(nsselection, &node);
    nsISelection_Release(nsselection);

    while(node) {
        nsres = nsIDOMNode_GetNodeType(node, &node_type);
        if(NS_FAILED(nsres) || node_type == DOCUMENT_NODE)
            break;

        if(node_type == ELEMENT_NODE) {
            nsIDOMNode_QueryInterface(node, &IID_nsIDOMHTMLElement, (void**)&elem);

            nsAString_Init(&tag_str, NULL);
            nsIDOMHTMLElement_GetTagName(elem, &tag_str);
            nsAString_GetData(&tag_str, &tag);

            if(!strcmpiW(tag, fontW)) {
                nsAString val_str;
                const PRUnichar *val;

                TRACE("found font tag %p\n", elem);

                get_elem_attr_value(elem, sizeW, &val_str, &val);
                if(*val) {
                    TRACE("found size %s\n", debugstr_w(val));
                    strcpyW(ret, val);
                }

                nsAString_Finish(&val_str);
            }

            nsAString_Finish(&tag_str);
            nsIDOMHTMLElement_Release(elem);
        }

        if(*ret)
            break;

        tmp_node = node;
        nsIDOMNode_GetParentNode(node, &node);
        nsIDOMNode_Release(tmp_node);
    }

    if(node)
        nsIDOMNode_Release(node);
}