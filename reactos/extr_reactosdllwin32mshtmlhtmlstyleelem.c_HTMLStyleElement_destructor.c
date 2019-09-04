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
struct TYPE_3__ {int /*<<< orphan*/ * style_sheet; } ;
typedef  TYPE_1__ HTMLStyleElement ;
typedef  int /*<<< orphan*/  HTMLDOMNode ;

/* Variables and functions */
 int /*<<< orphan*/  HTMLElement_destructor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IHTMLStyleSheet_Release (int /*<<< orphan*/ *) ; 
 TYPE_1__* impl_from_HTMLDOMNode (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void HTMLStyleElement_destructor(HTMLDOMNode *iface)
{
    HTMLStyleElement *This = impl_from_HTMLDOMNode(iface);

    if(This->style_sheet) {
        IHTMLStyleSheet_Release(This->style_sheet);
        This->style_sheet = NULL;
    }

    HTMLElement_destructor(iface);
}