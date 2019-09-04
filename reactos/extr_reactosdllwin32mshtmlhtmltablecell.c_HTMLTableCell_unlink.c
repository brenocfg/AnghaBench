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
typedef  int /*<<< orphan*/  nsIDOMHTMLTableCellElement ;
struct TYPE_3__ {int /*<<< orphan*/ * nscell; } ;
typedef  TYPE_1__ HTMLTableCell ;
typedef  int /*<<< orphan*/  HTMLDOMNode ;

/* Variables and functions */
 TYPE_1__* impl_from_HTMLDOMNode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMHTMLTableCellElement_Release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void HTMLTableCell_unlink(HTMLDOMNode *iface)
{
    HTMLTableCell *This = impl_from_HTMLDOMNode(iface);

    if(This->nscell) {
        nsIDOMHTMLTableCellElement *nscell = This->nscell;

        This->nscell = NULL;
        nsIDOMHTMLTableCellElement_Release(nscell);
    }
}