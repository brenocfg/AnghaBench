#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_5__ {int ref; TYPE_1__ IXMLParser_iface; int /*<<< orphan*/  state; scalar_t__ flags; int /*<<< orphan*/ * input; int /*<<< orphan*/ * nodefactory; } ;
typedef  TYPE_2__ xmlparser ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,void*) ; 
 int /*<<< orphan*/  XMLPARSER_IDLE ; 
 TYPE_2__* heap_alloc (int) ; 
 int /*<<< orphan*/  xmlparser_vtbl ; 

HRESULT XMLParser_create(void **ppObj)
{
    xmlparser *This;

    TRACE("(%p)\n", ppObj);

    This = heap_alloc( sizeof(xmlparser) );
    if(!This)
        return E_OUTOFMEMORY;

    This->IXMLParser_iface.lpVtbl = &xmlparser_vtbl;
    This->nodefactory = NULL;
    This->input = NULL;
    This->flags = 0;
    This->state = XMLPARSER_IDLE;
    This->ref = 1;

    *ppObj = &This->IXMLParser_iface;

    TRACE("returning iface %p\n", *ppObj);

    return S_OK;
}