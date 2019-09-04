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
typedef  int /*<<< orphan*/  VARIANT_BOOL ;
struct TYPE_3__ {int /*<<< orphan*/  IHTMLTextAreaElement_iface; } ;
typedef  TYPE_1__ HTMLTextAreaElement ;
typedef  int /*<<< orphan*/  HTMLDOMNode ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  IHTMLTextAreaElement_get_disabled (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* impl_from_HTMLDOMNode (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT HTMLTextAreaElementImpl_get_disabled(HTMLDOMNode *iface, VARIANT_BOOL *p)
{
    HTMLTextAreaElement *This = impl_from_HTMLDOMNode(iface);
    return IHTMLTextAreaElement_get_disabled(&This->IHTMLTextAreaElement_iface, p);
}