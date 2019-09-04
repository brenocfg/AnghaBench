#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsresult ;
typedef  int /*<<< orphan*/  nsISupports ;
typedef  int /*<<< orphan*/  nsIDOMNode ;
struct TYPE_7__ {TYPE_1__* vtbl; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* bind_to_tree ) (TYPE_2__*) ;} ;
typedef  int /*<<< orphan*/  HTMLDocumentNode ;
typedef  TYPE_2__ HTMLDOMNode ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_nsIDOMNode ; 
 scalar_t__ NS_FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  get_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__**) ; 
 int /*<<< orphan*/  node_release (TYPE_2__*) ; 
 int /*<<< orphan*/  nsIDOMNode_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsISupports_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static nsresult run_bind_to_tree(HTMLDocumentNode *doc, nsISupports *nsiface, nsISupports *arg2)
{
    nsIDOMNode *nsnode;
    HTMLDOMNode *node;
    nsresult nsres;
    HRESULT hres;

    TRACE("(%p)->(%p)\n", doc, nsiface);

    nsres = nsISupports_QueryInterface(nsiface, &IID_nsIDOMNode, (void**)&nsnode);
    if(NS_FAILED(nsres))
        return nsres;

    hres = get_node(doc, nsnode, TRUE, &node);
    nsIDOMNode_Release(nsnode);
    if(FAILED(hres)) {
        ERR("Could not get node\n");
        return nsres;
    }

    if(node->vtbl->bind_to_tree)
        node->vtbl->bind_to_tree(node);

    node_release(node);
    return nsres;
}