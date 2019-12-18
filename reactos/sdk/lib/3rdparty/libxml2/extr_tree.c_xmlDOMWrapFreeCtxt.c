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
typedef  int /*<<< orphan*/  xmlNsMapPtr ;
typedef  TYPE_1__* xmlDOMWrapCtxtPtr ;
struct TYPE_4__ {int /*<<< orphan*/ * namespaceMap; } ;

/* Variables and functions */
 int /*<<< orphan*/  xmlDOMWrapNsMapFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlFree (TYPE_1__*) ; 

void
xmlDOMWrapFreeCtxt(xmlDOMWrapCtxtPtr ctxt)
{
    if (ctxt == NULL)
	return;
    if (ctxt->namespaceMap != NULL)
	xmlDOMWrapNsMapFree((xmlNsMapPtr) ctxt->namespaceMap);
    /*
    * TODO: Store the namespace map in the context.
    */
    xmlFree(ctxt);
}