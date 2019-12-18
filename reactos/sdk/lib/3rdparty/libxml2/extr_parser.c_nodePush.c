#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlParserCtxtPtr ;
typedef  void* xmlNodePtr ;
struct TYPE_6__ {int nodeNr; int nodeMax; void** nodeTab; int options; void* node; } ;

/* Variables and functions */
 int /*<<< orphan*/  XML_ERR_INTERNAL_ERROR ; 
 int XML_PARSE_HUGE ; 
 int /*<<< orphan*/  xmlErrMemory (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFatalErrMsgInt (TYPE_1__*,int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  xmlHaltParser (TYPE_1__*) ; 
 unsigned int xmlParserMaxDepth ; 
 scalar_t__ xmlRealloc (void**,int) ; 

int
nodePush(xmlParserCtxtPtr ctxt, xmlNodePtr value)
{
    if (ctxt == NULL) return(0);
    if (ctxt->nodeNr >= ctxt->nodeMax) {
        xmlNodePtr *tmp;

	tmp = (xmlNodePtr *) xmlRealloc(ctxt->nodeTab,
                                      ctxt->nodeMax * 2 *
                                      sizeof(ctxt->nodeTab[0]));
        if (tmp == NULL) {
            xmlErrMemory(ctxt, NULL);
            return (-1);
        }
        ctxt->nodeTab = tmp;
	ctxt->nodeMax *= 2;
    }
    if ((((unsigned int) ctxt->nodeNr) > xmlParserMaxDepth) &&
        ((ctxt->options & XML_PARSE_HUGE) == 0)) {
	xmlFatalErrMsgInt(ctxt, XML_ERR_INTERNAL_ERROR,
		 "Excessive depth in document: %d use XML_PARSE_HUGE option\n",
			  xmlParserMaxDepth);
	xmlHaltParser(ctxt);
	return(-1);
    }
    ctxt->nodeTab[ctxt->nodeNr] = value;
    ctxt->node = value;
    return (ctxt->nodeNr++);
}