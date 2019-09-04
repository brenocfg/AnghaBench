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
struct TYPE_6__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_5__ {int ref; TYPE_2__ IShellBrowser_iface; } ;
typedef  TYPE_1__ IShellBrowserImpl ;
typedef  TYPE_2__ IShellBrowser ;

/* Variables and functions */
 int /*<<< orphan*/  IShellBrowserImpl_Vtbl ; 
 TYPE_1__* heap_alloc (int) ; 

__attribute__((used)) static IShellBrowser* IShellBrowserImpl_Construct(void)
{
    IShellBrowserImpl *browser;

    browser = heap_alloc(sizeof(*browser));
    browser->IShellBrowser_iface.lpVtbl = &IShellBrowserImpl_Vtbl;
    browser->ref = 1;

    return &browser->IShellBrowser_iface;
}