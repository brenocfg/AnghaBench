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
typedef  TYPE_1__* xmlParserCtxtPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_4__ {int options; int nsNr; int nsMax; int /*<<< orphan*/  const** nsTab; } ;

/* Variables and functions */
 int XML_PARSE_NSCLEAN ; 
 int /*<<< orphan*/  xmlErrMemory (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ xmlMalloc (int) ; 
 scalar_t__ xmlRealloc (char*,int) ; 

__attribute__((used)) static int
nsPush(xmlParserCtxtPtr ctxt, const xmlChar *prefix, const xmlChar *URL)
{
    if (ctxt->options & XML_PARSE_NSCLEAN) {
        int i;
	for (i = ctxt->nsNr - 2;i >= 0;i -= 2) {
	    if (ctxt->nsTab[i] == prefix) {
		/* in scope */
	        if (ctxt->nsTab[i + 1] == URL)
		    return(-2);
		/* out of scope keep it */
		break;
	    }
	}
    }
    if ((ctxt->nsMax == 0) || (ctxt->nsTab == NULL)) {
	ctxt->nsMax = 10;
	ctxt->nsNr = 0;
	ctxt->nsTab = (const xmlChar **)
	              xmlMalloc(ctxt->nsMax * sizeof(xmlChar *));
	if (ctxt->nsTab == NULL) {
	    xmlErrMemory(ctxt, NULL);
	    ctxt->nsMax = 0;
            return (-1);
	}
    } else if (ctxt->nsNr >= ctxt->nsMax) {
        const xmlChar ** tmp;
        ctxt->nsMax *= 2;
        tmp = (const xmlChar **) xmlRealloc((char *) ctxt->nsTab,
				    ctxt->nsMax * sizeof(ctxt->nsTab[0]));
        if (tmp == NULL) {
            xmlErrMemory(ctxt, NULL);
	    ctxt->nsMax /= 2;
            return (-1);
        }
	ctxt->nsTab = tmp;
    }
    ctxt->nsTab[ctxt->nsNr++] = prefix;
    ctxt->nsTab[ctxt->nsNr++] = URL;
    return (ctxt->nsNr);
}