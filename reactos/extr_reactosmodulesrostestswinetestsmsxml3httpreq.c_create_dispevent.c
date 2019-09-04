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
struct TYPE_5__ {int ref; TYPE_2__ IDispatch_iface; } ;
typedef  TYPE_1__ dispevent ;
typedef  TYPE_2__ IDispatch ;

/* Variables and functions */
 int /*<<< orphan*/  dispeventVtbl ; 
 TYPE_1__* heap_alloc (int) ; 

__attribute__((used)) static IDispatch* create_dispevent(void)
{
    dispevent *event = heap_alloc(sizeof(*event));

    event->IDispatch_iface.lpVtbl = &dispeventVtbl;
    event->ref = 1;

    return &event->IDispatch_iface;
}