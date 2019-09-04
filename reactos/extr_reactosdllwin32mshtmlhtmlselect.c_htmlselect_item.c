#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsresult ;
typedef  int /*<<< orphan*/  nsIDOMNode ;
typedef  int /*<<< orphan*/  nsIDOMHTMLOptionsCollection ;
struct TYPE_10__ {int /*<<< orphan*/  IHTMLDOMNode_iface; } ;
struct TYPE_7__ {int /*<<< orphan*/  doc; } ;
struct TYPE_8__ {TYPE_1__ node; } ;
struct TYPE_9__ {TYPE_2__ element; int /*<<< orphan*/  nsselect; } ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  TYPE_3__ HTMLSelectElement ;
typedef  TYPE_4__ HTMLDOMNode ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_FAIL ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ NS_FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  get_node (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__**) ; 
 int /*<<< orphan*/  nsIDOMHTMLOptionsCollection_Item (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nsIDOMHTMLOptionsCollection_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMHTMLSelectElement_GetOptions (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nsIDOMNode_Release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT htmlselect_item(HTMLSelectElement *This, int i, IDispatch **ret)
{
    nsIDOMHTMLOptionsCollection *nscol;
    nsIDOMNode *nsnode;
    nsresult nsres;
    HRESULT hres;

    nsres = nsIDOMHTMLSelectElement_GetOptions(This->nsselect, &nscol);
    if(NS_FAILED(nsres)) {
        ERR("GetOptions failed: %08x\n", nsres);
        return E_FAIL;
    }

    nsres = nsIDOMHTMLOptionsCollection_Item(nscol, i, &nsnode);
    nsIDOMHTMLOptionsCollection_Release(nscol);
    if(NS_FAILED(nsres)) {
        ERR("Item failed: %08x\n", nsres);
        return E_FAIL;
    }

    if(nsnode) {
        HTMLDOMNode *node;

        hres = get_node(This->element.node.doc, nsnode, TRUE, &node);
        nsIDOMNode_Release(nsnode);
        if(FAILED(hres))
            return hres;

        *ret = (IDispatch*)&node->IHTMLDOMNode_iface;
    }else {
        *ret = NULL;
    }
    return S_OK;
}