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
typedef  int /*<<< orphan*/ * xmlParserInputPtr ;
typedef  TYPE_1__* xmlParserCtxtPtr ;
struct TYPE_4__ {int inputNr; int inputMax; int /*<<< orphan*/ * input; int /*<<< orphan*/ ** inputTab; } ;

/* Variables and functions */
 int /*<<< orphan*/  xmlErrMemory (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFreeInputStream (int /*<<< orphan*/ *) ; 
 scalar_t__ xmlRealloc (int /*<<< orphan*/ **,int) ; 

int
inputPush(xmlParserCtxtPtr ctxt, xmlParserInputPtr value)
{
    if ((ctxt == NULL) || (value == NULL))
        return(-1);
    if (ctxt->inputNr >= ctxt->inputMax) {
        ctxt->inputMax *= 2;
        ctxt->inputTab =
            (xmlParserInputPtr *) xmlRealloc(ctxt->inputTab,
                                             ctxt->inputMax *
                                             sizeof(ctxt->inputTab[0]));
        if (ctxt->inputTab == NULL) {
            xmlErrMemory(ctxt, NULL);
	    xmlFreeInputStream(value);
	    ctxt->inputMax /= 2;
	    value = NULL;
            return (-1);
        }
    }
    ctxt->inputTab[ctxt->inputNr] = value;
    ctxt->input = value;
    return (ctxt->inputNr++);
}