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
typedef  int /*<<< orphan*/  nsIDocument ;
typedef  int /*<<< orphan*/  nsIDOMNodeList ;
typedef  int /*<<< orphan*/  nsIDOMNode ;
typedef  int /*<<< orphan*/  nsIContentSerializer ;
typedef  int /*<<< orphan*/  nsIContent ;
typedef  int /*<<< orphan*/  nsAString ;
typedef  scalar_t__ cpp_bool ;
typedef  scalar_t__ UINT32 ;
typedef  int UINT16 ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
#define  COMMENT_NODE 133 
#define  DOCUMENT_FRAGMENT_NODE 132 
#define  DOCUMENT_NODE 131 
#define  DOCUMENT_TYPE_NODE 130 
#define  ELEMENT_NODE 129 
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_FAIL ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  IID_nsIContent ; 
 int /*<<< orphan*/  IID_nsIDocument ; 
 scalar_t__ NS_FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ NS_SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
#define  TEXT_NODE 128 
 int /*<<< orphan*/  nsIContentSerializer_AppendComment (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIContentSerializer_AppendDoctype (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIContentSerializer_AppendDocumentStart (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIContentSerializer_AppendElementEnd (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIContentSerializer_AppendElementStart (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIContentSerializer_AppendText (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIContent_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMNodeList_GetLength (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  nsIDOMNodeList_Item (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nsIDOMNodeList_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMNode_GetChildNodes (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nsIDOMNode_GetNodeType (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  nsIDOMNode_HasChildNodes (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  nsIDOMNode_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  nsIDOMNode_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDocument_Release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT nsnode_to_nsstring_rec(nsIContentSerializer *serializer, nsIDOMNode *nsnode, nsAString *str)
{
    nsIDOMNodeList *node_list = NULL;
    cpp_bool has_children = FALSE;
    nsIContent *nscontent;
    UINT16 type;
    nsresult nsres;

    nsIDOMNode_HasChildNodes(nsnode, &has_children);

    nsres = nsIDOMNode_GetNodeType(nsnode, &type);
    if(NS_FAILED(nsres)) {
        ERR("GetType failed: %08x\n", nsres);
        return E_FAIL;
    }

    if(type != DOCUMENT_NODE) {
        nsres = nsIDOMNode_QueryInterface(nsnode, &IID_nsIContent, (void**)&nscontent);
        if(NS_FAILED(nsres)) {
            ERR("Could not get nsIContent interface: %08x\n", nsres);
            return E_FAIL;
        }
    }

    switch(type) {
    case ELEMENT_NODE:
        nsIContentSerializer_AppendElementStart(serializer, nscontent, nscontent, str);
        break;
    case TEXT_NODE:
        nsIContentSerializer_AppendText(serializer, nscontent, 0, -1, str);
        break;
    case COMMENT_NODE:
        nsres = nsIContentSerializer_AppendComment(serializer, nscontent, 0, -1, str);
        break;
    case DOCUMENT_NODE: {
        nsIDocument *nsdoc;
        nsIDOMNode_QueryInterface(nsnode, &IID_nsIDocument, (void**)&nsdoc);
        nsIContentSerializer_AppendDocumentStart(serializer, nsdoc, str);
        nsIDocument_Release(nsdoc);
        break;
    }
    case DOCUMENT_TYPE_NODE:
        nsIContentSerializer_AppendDoctype(serializer, nscontent, str);
        break;
    case DOCUMENT_FRAGMENT_NODE:
        break;
    default:
        FIXME("Unhandled type %u\n", type);
    }

    if(has_children) {
        UINT32 child_cnt, i;
        nsIDOMNode *child_node;

        nsIDOMNode_GetChildNodes(nsnode, &node_list);
        nsIDOMNodeList_GetLength(node_list, &child_cnt);

        for(i=0; i<child_cnt; i++) {
            nsres = nsIDOMNodeList_Item(node_list, i, &child_node);
            if(NS_SUCCEEDED(nsres)) {
                nsnode_to_nsstring_rec(serializer, child_node, str);
                nsIDOMNode_Release(child_node);
            }else {
                ERR("Item failed: %08x\n", nsres);
            }
        }

        nsIDOMNodeList_Release(node_list);
    }

    if(type == ELEMENT_NODE)
        nsIContentSerializer_AppendElementEnd(serializer, nscontent, str);

    if(type != DOCUMENT_NODE)
        nsIContent_Release(nscontent);
    return S_OK;
}