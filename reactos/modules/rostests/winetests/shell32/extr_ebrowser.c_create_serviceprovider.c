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
struct TYPE_6__ {int ref; TYPE_1__ IServiceProvider_iface; } ;
typedef  TYPE_2__ IServiceProviderImpl ;

/* Variables and functions */
 TYPE_2__* heap_alloc (int) ; 
 int /*<<< orphan*/  spvtbl ; 

__attribute__((used)) static IServiceProviderImpl *create_serviceprovider(void)
{
    IServiceProviderImpl *sp = heap_alloc(sizeof(*sp));
    sp->IServiceProvider_iface.lpVtbl = &spvtbl;
    sp->ref = 1;
    return sp;
}