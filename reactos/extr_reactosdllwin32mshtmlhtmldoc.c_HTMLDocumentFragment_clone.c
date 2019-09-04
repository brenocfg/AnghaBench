#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsIDOMNode ;
struct TYPE_9__ {int /*<<< orphan*/  doc; } ;
struct TYPE_8__ {TYPE_2__ node; } ;
typedef  TYPE_1__ HTMLDocumentNode ;
typedef  TYPE_2__ HTMLDOMNode ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  create_document_fragment (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__**) ; 
 TYPE_1__* impl_from_HTMLDOMNode (TYPE_2__*) ; 

__attribute__((used)) static HRESULT HTMLDocumentFragment_clone(HTMLDOMNode *iface, nsIDOMNode *nsnode, HTMLDOMNode **ret)
{
    HTMLDocumentNode *This = impl_from_HTMLDOMNode(iface);
    HTMLDocumentNode *new_node;
    HRESULT hres;

    hres = create_document_fragment(nsnode, This->node.doc, &new_node);
    if(FAILED(hres))
        return hres;

    *ret = &new_node->node;
    return S_OK;
}