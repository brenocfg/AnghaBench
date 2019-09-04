#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsISelection ;
struct TYPE_11__ {int /*<<< orphan*/  selection_list; } ;
struct TYPE_9__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_8__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_10__ {int ref; TYPE_2__ IHTMLSelectionObject_iface; int /*<<< orphan*/  entry; TYPE_4__* doc; int /*<<< orphan*/ * nsselection; TYPE_1__ IHTMLSelectionObject2_iface; int /*<<< orphan*/  dispex; } ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  TYPE_2__ IHTMLSelectionObject ;
typedef  TYPE_3__ HTMLSelectionObject ;
typedef  TYPE_4__ HTMLDocumentNode ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  HTMLSelectionObject2Vtbl ; 
 int /*<<< orphan*/  HTMLSelectionObjectVtbl ; 
 int /*<<< orphan*/  HTMLSelectionObject_dispex ; 
 int /*<<< orphan*/  S_OK ; 
 TYPE_3__* heap_alloc (int) ; 
 int /*<<< orphan*/  init_dispex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

HRESULT HTMLSelectionObject_Create(HTMLDocumentNode *doc, nsISelection *nsselection, IHTMLSelectionObject **ret)
{
    HTMLSelectionObject *selection;

    selection = heap_alloc(sizeof(HTMLSelectionObject));
    if(!selection)
        return E_OUTOFMEMORY;

    init_dispex(&selection->dispex, (IUnknown*)&selection->IHTMLSelectionObject_iface, &HTMLSelectionObject_dispex);

    selection->IHTMLSelectionObject_iface.lpVtbl = &HTMLSelectionObjectVtbl;
    selection->IHTMLSelectionObject2_iface.lpVtbl = &HTMLSelectionObject2Vtbl;
    selection->ref = 1;
    selection->nsselection = nsselection; /* We shouldn't call AddRef here */

    selection->doc = doc;
    list_add_head(&doc->selection_list, &selection->entry);

    *ret = &selection->IHTMLSelectionObject_iface;
    return S_OK;
}