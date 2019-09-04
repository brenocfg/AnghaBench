#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsIDOMCSSRuleList ;
struct TYPE_5__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_6__ {int ref; TYPE_1__ IHTMLStyleSheetRulesCollection_iface; int /*<<< orphan*/  dispex; int /*<<< orphan*/ * nslist; } ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  TYPE_1__ IHTMLStyleSheetRulesCollection ;
typedef  TYPE_2__ HTMLStyleSheetRulesCollection ;

/* Variables and functions */
 int /*<<< orphan*/  HTMLStyleSheetRulesCollectionVtbl ; 
 int /*<<< orphan*/  HTMLStyleSheetRulesCollection_dispex ; 
 TYPE_2__* heap_alloc (int) ; 
 int /*<<< orphan*/  init_dispex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMCSSRuleList_AddRef (int /*<<< orphan*/ *) ; 

__attribute__((used)) static IHTMLStyleSheetRulesCollection *HTMLStyleSheetRulesCollection_Create(nsIDOMCSSRuleList *nslist)
{
    HTMLStyleSheetRulesCollection *ret;

    ret = heap_alloc(sizeof(*ret));
    ret->IHTMLStyleSheetRulesCollection_iface.lpVtbl = &HTMLStyleSheetRulesCollectionVtbl;
    ret->ref = 1;
    ret->nslist = nslist;

    init_dispex(&ret->dispex, (IUnknown*)&ret->IHTMLStyleSheetRulesCollection_iface, &HTMLStyleSheetRulesCollection_dispex);

    if(nslist)
        nsIDOMCSSRuleList_AddRef(nslist);

    return &ret->IHTMLStyleSheetRulesCollection_iface;
}