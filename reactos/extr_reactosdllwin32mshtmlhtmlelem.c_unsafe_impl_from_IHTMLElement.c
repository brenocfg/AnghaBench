#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * lpVtbl; } ;
typedef  TYPE_1__ IHTMLElement ;
typedef  int /*<<< orphan*/  HTMLElement ;

/* Variables and functions */
 int /*<<< orphan*/  HTMLElementVtbl ; 
 int /*<<< orphan*/ * impl_from_IHTMLElement (TYPE_1__*) ; 

HTMLElement *unsafe_impl_from_IHTMLElement(IHTMLElement *iface)
{
    return iface->lpVtbl == &HTMLElementVtbl ? impl_from_IHTMLElement(iface) : NULL;
}