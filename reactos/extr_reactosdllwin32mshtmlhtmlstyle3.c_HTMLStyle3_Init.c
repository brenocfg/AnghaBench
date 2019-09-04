#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_9__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_8__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_7__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_11__ {TYPE_4__ IHTMLStyle6_iface; TYPE_3__ IHTMLStyle5_iface; TYPE_2__ IHTMLStyle4_iface; TYPE_1__ IHTMLStyle3_iface; } ;
typedef  TYPE_5__ HTMLStyle ;

/* Variables and functions */
 int /*<<< orphan*/  HTMLStyle3Vtbl ; 
 int /*<<< orphan*/  HTMLStyle4Vtbl ; 
 int /*<<< orphan*/  HTMLStyle5Vtbl ; 
 int /*<<< orphan*/  HTMLStyle6Vtbl ; 

void HTMLStyle3_Init(HTMLStyle *This)
{
    This->IHTMLStyle3_iface.lpVtbl = &HTMLStyle3Vtbl;
    This->IHTMLStyle4_iface.lpVtbl = &HTMLStyle4Vtbl;
    This->IHTMLStyle5_iface.lpVtbl = &HTMLStyle5Vtbl;
    This->IHTMLStyle6_iface.lpVtbl = &HTMLStyle6Vtbl;
}