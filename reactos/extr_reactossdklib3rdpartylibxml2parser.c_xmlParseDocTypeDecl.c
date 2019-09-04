#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* xmlParserCtxtPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_9__ {int hasExternalSubset; scalar_t__ instate; int /*<<< orphan*/  userData; TYPE_1__* sax; int /*<<< orphan*/  disableSAX; int /*<<< orphan*/ * extSubSystem; int /*<<< orphan*/ * extSubURI; int /*<<< orphan*/  const* intSubName; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* internalSubset ) (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  NEXT ; 
 char RAW ; 
 int /*<<< orphan*/  SKIP (int) ; 
 int /*<<< orphan*/  SKIP_BLANKS ; 
 int /*<<< orphan*/  XML_ERR_DOCTYPE_NOT_FINISHED ; 
 int /*<<< orphan*/  XML_ERR_NAME_REQUIRED ; 
 scalar_t__ XML_PARSER_EOF ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFatalErr (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFatalErrMsg (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * xmlParseExternalID (TYPE_2__*,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/ * xmlParseName (TYPE_2__*) ; 

void
xmlParseDocTypeDecl(xmlParserCtxtPtr ctxt) {
    const xmlChar *name = NULL;
    xmlChar *ExternalID = NULL;
    xmlChar *URI = NULL;

    /*
     * We know that '<!DOCTYPE' has been detected.
     */
    SKIP(9);

    SKIP_BLANKS;

    /*
     * Parse the DOCTYPE name.
     */
    name = xmlParseName(ctxt);
    if (name == NULL) {
	xmlFatalErrMsg(ctxt, XML_ERR_NAME_REQUIRED,
		       "xmlParseDocTypeDecl : no DOCTYPE name !\n");
    }
    ctxt->intSubName = name;

    SKIP_BLANKS;

    /*
     * Check for SystemID and ExternalID
     */
    URI = xmlParseExternalID(ctxt, &ExternalID, 1);

    if ((URI != NULL) || (ExternalID != NULL)) {
        ctxt->hasExternalSubset = 1;
    }
    ctxt->extSubURI = URI;
    ctxt->extSubSystem = ExternalID;

    SKIP_BLANKS;

    /*
     * Create and update the internal subset.
     */
    if ((ctxt->sax != NULL) && (ctxt->sax->internalSubset != NULL) &&
	(!ctxt->disableSAX))
	ctxt->sax->internalSubset(ctxt->userData, name, ExternalID, URI);
    if (ctxt->instate == XML_PARSER_EOF)
	return;

    /*
     * Is there any internal subset declarations ?
     * they are handled separately in xmlParseInternalSubset()
     */
    if (RAW == '[')
	return;

    /*
     * We should be at the end of the DOCTYPE declaration.
     */
    if (RAW != '>') {
	xmlFatalErr(ctxt, XML_ERR_DOCTYPE_NOT_FINISHED, NULL);
    }
    NEXT;
}