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
typedef  TYPE_1__ IHTMLEventObj ;
typedef  int /*<<< orphan*/  HTMLEventObj ;

/* Variables and functions */
 int /*<<< orphan*/  HTMLEventObjVtbl ; 
 int /*<<< orphan*/ * impl_from_IHTMLEventObj (TYPE_1__*) ; 

__attribute__((used)) static inline HTMLEventObj *unsafe_impl_from_IHTMLEventObj(IHTMLEventObj *iface)
{
    return iface->lpVtbl == &HTMLEventObjVtbl ? impl_from_IHTMLEventObj(iface) : NULL;
}