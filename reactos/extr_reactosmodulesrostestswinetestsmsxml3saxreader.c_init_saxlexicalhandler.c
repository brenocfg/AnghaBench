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
struct saxlexicalhandler {int ref; int /*<<< orphan*/  qi_hr; TYPE_1__ ISAXLexicalHandler_iface; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  SAXLexicalHandlerVtbl ; 

__attribute__((used)) static void init_saxlexicalhandler(struct saxlexicalhandler *handler, HRESULT hr)
{
    handler->ISAXLexicalHandler_iface.lpVtbl = &SAXLexicalHandlerVtbl;
    handler->ref = 1;
    handler->qi_hr = hr;
}