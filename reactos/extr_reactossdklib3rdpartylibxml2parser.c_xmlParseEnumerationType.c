#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlParserCtxtPtr ;
typedef  TYPE_2__* xmlEnumerationPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_11__ {struct TYPE_11__* next; int /*<<< orphan*/  name; } ;
struct TYPE_10__ {int /*<<< orphan*/  dict; } ;

/* Variables and functions */
 int /*<<< orphan*/  NEXT ; 
 char RAW ; 
 int /*<<< orphan*/  SHRINK ; 
 int /*<<< orphan*/  SKIP_BLANKS ; 
 int /*<<< orphan*/  XML_DTD_DUP_TOKEN ; 
 int /*<<< orphan*/  XML_ERR_ATTLIST_NOT_FINISHED ; 
 int /*<<< orphan*/  XML_ERR_ATTLIST_NOT_STARTED ; 
 int /*<<< orphan*/  XML_ERR_NMTOKEN_REQUIRED ; 
 TYPE_2__* xmlCreateEnumeration (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlDictOwns (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFatalErr (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFreeEnumeration (TYPE_2__*) ; 
 int /*<<< orphan*/ * xmlParseNmtoken (TYPE_1__*) ; 
 scalar_t__ xmlStrEqual (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlValidityError (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

xmlEnumerationPtr
xmlParseEnumerationType(xmlParserCtxtPtr ctxt) {
    xmlChar *name;
    xmlEnumerationPtr ret = NULL, last = NULL, cur, tmp;

    if (RAW != '(') {
	xmlFatalErr(ctxt, XML_ERR_ATTLIST_NOT_STARTED, NULL);
	return(NULL);
    }
    SHRINK;
    do {
        NEXT;
	SKIP_BLANKS;
        name = xmlParseNmtoken(ctxt);
	if (name == NULL) {
	    xmlFatalErr(ctxt, XML_ERR_NMTOKEN_REQUIRED, NULL);
	    return(ret);
	}
	tmp = ret;
	while (tmp != NULL) {
	    if (xmlStrEqual(name, tmp->name)) {
		xmlValidityError(ctxt, XML_DTD_DUP_TOKEN,
	  "standalone: attribute enumeration value token %s duplicated\n",
				 name, NULL);
		if (!xmlDictOwns(ctxt->dict, name))
		    xmlFree(name);
		break;
	    }
	    tmp = tmp->next;
	}
	if (tmp == NULL) {
	    cur = xmlCreateEnumeration(name);
	    if (!xmlDictOwns(ctxt->dict, name))
		xmlFree(name);
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
	xmlFatalErr(ctxt, XML_ERR_ATTLIST_NOT_FINISHED, NULL);
	return(ret);
    }
    NEXT;
    return(ret);
}