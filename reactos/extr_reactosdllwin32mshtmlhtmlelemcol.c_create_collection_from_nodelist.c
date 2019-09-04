#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsIDOMNodeList ;
typedef  int /*<<< orphan*/  nsIDOMNode ;
struct TYPE_3__ {int size; scalar_t__ len; int /*<<< orphan*/ * buf; } ;
typedef  TYPE_1__ elem_vector_t ;
typedef  scalar_t__ UINT32 ;
typedef  int /*<<< orphan*/  IHTMLElementCollection ;
typedef  int /*<<< orphan*/  HTMLElement ;
typedef  int /*<<< orphan*/  HTMLDocumentNode ;
typedef  int /*<<< orphan*/  HTMLDOMNode ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * HTMLElementCollection_Create (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  elem_from_HTMLDOMNode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elem_vector_normalize (TYPE_1__*) ; 
 int /*<<< orphan*/  get_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * heap_alloc (int) ; 
 scalar_t__ is_elem_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMNodeList_GetLength (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  nsIDOMNodeList_Item (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nsIDOMNode_Release (int /*<<< orphan*/ *) ; 

IHTMLElementCollection *create_collection_from_nodelist(HTMLDocumentNode *doc, nsIDOMNodeList *nslist)
{
    UINT32 length = 0, i;
    HTMLDOMNode *node;
    elem_vector_t buf;
    HRESULT hres;

    nsIDOMNodeList_GetLength(nslist, &length);

    buf.len = 0;
    buf.size = length;
    if(length) {
        nsIDOMNode *nsnode;

        buf.buf = heap_alloc(buf.size*sizeof(HTMLElement*));

        for(i=0; i<length; i++) {
            nsIDOMNodeList_Item(nslist, i, &nsnode);
            if(is_elem_node(nsnode)) {
                hres = get_node(doc, nsnode, TRUE, &node);
                if(FAILED(hres))
                    continue;
                buf.buf[buf.len++] = elem_from_HTMLDOMNode(node);
            }
            nsIDOMNode_Release(nsnode);
        }

        elem_vector_normalize(&buf);
    }else {
        buf.buf = NULL;
    }

    return HTMLElementCollection_Create(buf.buf, buf.len);
}