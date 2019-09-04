#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsISelection ;
typedef  int /*<<< orphan*/  nsIDOMRange ;
typedef  int /*<<< orphan*/  nsIDOMNode ;
typedef  int /*<<< orphan*/  nsIDOMHTMLElement ;
typedef  int /*<<< orphan*/  nsIDOMElement ;
typedef  int /*<<< orphan*/  nsAString ;
typedef  scalar_t__ cpp_bool ;
struct TYPE_7__ {int /*<<< orphan*/  nsdoc; } ;
struct TYPE_6__ {TYPE_5__* doc_node; } ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int LONG ;
typedef  TYPE_1__ HTMLDocument ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  VARIANT_TRUE ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  create_nselem (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  fontW ; 
 int /*<<< orphan*/ * get_ns_selection (TYPE_1__*) ; 
 int /*<<< orphan*/  nsAString_Finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsAString_InitDepend (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsIDOMHTMLElement_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMHTMLElement_SetAttribute (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMRange_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMRange_SurroundContents (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsISelection_Collapse (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsISelection_GetIsCollapsed (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  nsISelection_GetRangeAt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nsISelection_GetRangeCount (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  nsISelection_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsISelection_RemoveAllRanges (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsISelection_SelectAllChildren (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_child_attr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_dirty (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sizeW ; 

__attribute__((used)) static void set_font_size(HTMLDocument *This, LPCWSTR size)
{
    nsISelection *nsselection;
    cpp_bool collapsed;
    nsIDOMHTMLElement *elem;
    nsIDOMRange *range;
    LONG range_cnt = 0;
    nsAString size_str;
    nsAString val_str;

    if(!This->doc_node->nsdoc) {
        WARN("NULL nsdoc\n");
        return;
    }

    nsselection = get_ns_selection(This);
    if(!nsselection)
        return;

    nsISelection_GetRangeCount(nsselection, &range_cnt);
    if(range_cnt != 1) {
        FIXME("range_cnt %d not supprted\n", range_cnt);
        if(!range_cnt) {
            nsISelection_Release(nsselection);
            return;
        }
    }

    create_nselem(This->doc_node, fontW, &elem);

    nsAString_InitDepend(&size_str, sizeW);
    nsAString_InitDepend(&val_str, size);

    nsIDOMHTMLElement_SetAttribute(elem, &size_str, &val_str);
    nsAString_Finish(&val_str);

    nsISelection_GetRangeAt(nsselection, 0, &range);
    nsISelection_GetIsCollapsed(nsselection, &collapsed);
    nsISelection_RemoveAllRanges(nsselection);

    nsIDOMRange_SurroundContents(range, (nsIDOMNode*)elem);

    if(collapsed) {
        nsISelection_Collapse(nsselection, (nsIDOMNode*)elem, 0);
    }else {
        /* Remove all size attributes from the range */
        remove_child_attr((nsIDOMElement*)elem, fontW, &size_str);
        nsISelection_SelectAllChildren(nsselection, (nsIDOMNode*)elem);
    }

    nsISelection_Release(nsselection);
    nsIDOMRange_Release(range);
    nsIDOMHTMLElement_Release(elem);

    nsAString_Finish(&size_str);

    set_dirty(This, VARIANT_TRUE);
}