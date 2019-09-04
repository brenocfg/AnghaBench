#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * lpVtbl; } ;
struct saxdeclhandler {int ref; int /*<<< orphan*/  qi_hr; TYPE_1__ ISAXDeclHandler_iface; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  SAXDeclHandlerVtbl ; 

__attribute__((used)) static void init_saxdeclhandler(struct saxdeclhandler *handler, HRESULT hr)
{
    handler->ISAXDeclHandler_iface.lpVtbl = &SAXDeclHandlerVtbl;
    handler->ref = 1;
    handler->qi_hr = hr;
}