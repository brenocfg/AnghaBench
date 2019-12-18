#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlParserCtxtPtr ;
typedef  TYPE_2__* xmlEnumerationPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_12__ {struct TYPE_12__* next; int /*<<< orphan*/  name; } ;
struct TYPE_11__ {int /*<<< orphan*/  dict; } ;

/* Variables and functions */
 int /*<<< orphan*/  NEXT ; 
 char RAW ; 
 int /*<<< orphan*/  SHRINK ; 
 int /*<<< orphan*/  SKIP_BLANKS ; 
 int /*<<< orphan*/  XML_DTD_DUP_TOKEN ; 
 int /*<<< orphan*/  XML_ERR_NAME_REQUIRED ; 
 int /*<<< orphan*/  XML_ERR_NOTATION_NOT_FINISHED ; 
 int /*<<< orphan*/  XML_ERR_NOTATION_NOT_STARTED ; 
 TYPE_2__* xmlCreateEnumeration (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  xmlDictOwns (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  xmlFatalErr (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFatalErrMsg (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xmlFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFreeEnumeration (TYPE_2__*) ; 
 int /*<<< orphan*/ * xmlParseName (TYPE_1__*) ; 
 scalar_t__ xmlStrEqual (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlValidityError (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

xmlEnumerationPtr
xmlParseNotationType(xmlParserCtxtPtr ctxt) {
    const xmlChar *name;
    xmlEnumerationPtr ret = NULL, last = NULL, cur, tmp;

    if (RAW != '(') {
	xmlFatalErr(ctxt, XML_ERR_NOTATION_NOT_STARTED, NULL);
	return(NULL);
    }
    SHRINK;
    do {
        NEXT;
	SKIP_BLANKS;
        name = xmlParseName(ctxt);
	if (name == NULL) {
	    xmlFatalErrMsg(ctxt, XML_ERR_NAME_REQUIRED,
			   "Name expected in NOTATION declaration\n");
            xmlFreeEnumeration(ret);
	    return(NULL);
	}
	tmp = ret;
	while (tmp != NULL) {
	    if (xmlStrEqual(name, tmp->name)) {
		xmlValidityError(ctxt, XML_DTD_DUP_TOKEN,
	  "standalone: attribute notation value token %s duplicated\n",
				 name, NULL);
		if (!xmlDictOwns(ctxt->dict, name))
		    xmlFree((xmlChar *) name);
		break;
	    }
	    tmp = tmp->next;
	}
	if (tmp == NULL) {
	    cur = xmlCreateEnumeration(name);
	    if (cur == NULL) {
                xmlFreeEnumeration(ret);
                return(NULL);
            }
	    if (last == NULL) ret = last = cur;
	    else {
		last->next = cur;
		last = cur;
	    }
	}
	SKIP_BLANKS;
    } while (RAW == '|');
    if (RAW != ')') {
	xmlFatalErr(ctxt, XML_ERR_NOTATION_NOT_FINISHED, NULL);
        xmlFreeEnumeration(ret);
	return(NULL);
    }
    NEXT;
    return(ret);
}