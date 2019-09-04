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
struct TYPE_5__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_6__ {int ref; TYPE_1__ IExplorerPaneVisibility_iface; } ;
typedef  TYPE_2__ IExplorerPaneVisibilityImpl ;

/* Variables and functions */
 int /*<<< orphan*/  epvvt ; 
 TYPE_2__* heap_alloc_zero (int) ; 

__attribute__((used)) static IExplorerPaneVisibilityImpl *create_explorerpanevisibility(void)
{
    IExplorerPaneVisibilityImpl *epv;

    epv = heap_alloc_zero(sizeof(*epv));
    epv->IExplorerPaneVisibility_iface.lpVtbl = &epvvt;
    epv->ref = 1;

    return epv;
}