#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* xmlParserCtxtPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_12__ {int /*<<< orphan*/  userData; TYPE_2__* sax; int /*<<< orphan*/  disableSAX; TYPE_1__* input; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* notationDecl ) (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct TYPE_10__ {int id; } ;

/* Variables and functions */
 scalar_t__ CMP10 (int /*<<< orphan*/ ,char,char,char,char,char,char,char,char,char,char) ; 
 int /*<<< orphan*/  CUR_PTR ; 
 int /*<<< orphan*/  NEXT ; 
 char RAW ; 
 int /*<<< orphan*/  SHRINK ; 
 int /*<<< orphan*/  SKIP (int) ; 
 scalar_t__ SKIP_BLANKS ; 
 int /*<<< orphan*/  XML_ERR_ENTITY_BOUNDARY ; 
 int /*<<< orphan*/  XML_ERR_NOTATION_NOT_FINISHED ; 
 int /*<<< orphan*/  XML_ERR_NOTATION_NOT_STARTED ; 
 int /*<<< orphan*/  XML_ERR_SPACE_REQUIRED ; 
 int /*<<< orphan*/  XML_NS_ERR_COLON ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFatalErr (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFatalErrMsg (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xmlFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlNsErr (TYPE_3__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xmlParseExternalID (TYPE_3__*,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xmlParseName (TYPE_3__*) ; 
 int /*<<< orphan*/ * xmlStrchr (int /*<<< orphan*/  const*,char) ; 

void
xmlParseNotationDecl(xmlParserCtxtPtr ctxt) {
    const xmlChar *name;
    xmlChar *Pubid;
    xmlChar *Systemid;

    if (CMP10(CUR_PTR, '<', '!', 'N', 'O', 'T', 'A', 'T', 'I', 'O', 'N')) {
	int inputid = ctxt->input->id;
	SHRINK;
	SKIP(10);
	if (SKIP_BLANKS == 0) {
	    xmlFatalErrMsg(ctxt, XML_ERR_SPACE_REQUIRED,
			   "Space required after '<!NOTATION'\n");
	    return;
	}

        name = xmlParseName(ctxt);
	if (name == NULL) {
	    xmlFatalErr(ctxt, XML_ERR_NOTATION_NOT_STARTED, NULL);
	    return;
	}
	if (xmlStrchr(name, ':') != NULL) {
	    xmlNsErr(ctxt, XML_NS_ERR_COLON,
		     "colons are forbidden from notation names '%s'\n",
		     name, NULL, NULL);
	}
	if (SKIP_BLANKS == 0) {
	    xmlFatalErrMsg(ctxt, XML_ERR_SPACE_REQUIRED,
		     "Space required after the NOTATION name'\n");
	    return;
	}

	/*
	 * Parse the IDs.
	 */
	Systemid = xmlParseExternalID(ctxt, &Pubid, 0);
	SKIP_BLANKS;

	if (RAW == '>') {
	    if (inputid != ctxt->input->id) {
		xmlFatalErrMsg(ctxt, XML_ERR_ENTITY_BOUNDARY,
	                       "Notation declaration doesn't start and stop"
                               " in the same entity\n");
	    }
	    NEXT;
	    if ((ctxt->sax != NULL) && (!ctxt->disableSAX) &&
		(ctxt->sax->notationDecl != NULL))
		ctxt->sax->notationDecl(ctxt->userData, name, Pubid, Systemid);
	} else {
	    xmlFatalErr(ctxt, XML_ERR_NOTATION_NOT_FINISHED, NULL);
	}
	if (Systemid != NULL) xmlFree(Systemid);
	if (Pubid != NULL) xmlFree(Pubid);
    }
}