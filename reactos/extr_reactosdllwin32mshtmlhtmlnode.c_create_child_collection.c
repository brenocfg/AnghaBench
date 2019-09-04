#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsIDOMNodeList ;
struct TYPE_7__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_9__ {int ref; TYPE_1__ IHTMLDOMChildrenCollection_iface; int /*<<< orphan*/  dispex; TYPE_2__* doc; int /*<<< orphan*/ * nslist; } ;
struct TYPE_8__ {int /*<<< orphan*/  basedoc; } ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  TYPE_1__ IHTMLDOMChildrenCollection ;
typedef  TYPE_2__ HTMLDocumentNode ;
typedef  TYPE_3__ HTMLDOMChildrenCollection ;

/* Variables and functions */
 int /*<<< orphan*/  HTMLDOMChildrenCollectionVtbl ; 
 int /*<<< orphan*/  HTMLDOMChildrenCollection_dispex ; 
 TYPE_3__* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  htmldoc_addref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_dispex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMNodeList_AddRef (int /*<<< orphan*/ *) ; 

__attribute__((used)) static IHTMLDOMChildrenCollection *create_child_collection(HTMLDocumentNode *doc, nsIDOMNodeList *nslist)
{
    HTMLDOMChildrenCollection *ret;

    ret = heap_alloc_zero(sizeof(*ret));
    if(!ret)
        return NULL;

    ret->IHTMLDOMChildrenCollection_iface.lpVtbl = &HTMLDOMChildrenCollectionVtbl;
    ret->ref = 1;

    nsIDOMNodeList_AddRef(nslist);
    ret->nslist = nslist;

    htmldoc_addref(&doc->basedoc);
    ret->doc = doc;

    init_dispex(&ret->dispex, (IUnknown*)&ret->IHTMLDOMChildrenCollection_iface,
            &HTMLDOMChildrenCollection_dispex);

    return &ret->IHTMLDOMChildrenCollection_iface;
}