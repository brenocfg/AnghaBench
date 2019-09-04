#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* xmlParserCtxtPtr ;
typedef  int /*<<< orphan*/ * xmlElementContentPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_8__ {scalar_t__ instate; TYPE_1__* input; } ;
struct TYPE_7__ {int id; } ;

/* Variables and functions */
 scalar_t__ CMP7 (int /*<<< orphan*/ ,char,char,char,char,char,char,char) ; 
 int /*<<< orphan*/  CUR_PTR ; 
 int /*<<< orphan*/  GROW ; 
 int /*<<< orphan*/  NEXT ; 
 char RAW ; 
 int /*<<< orphan*/  SKIP_BLANKS ; 
 int XML_ELEMENT_TYPE_ELEMENT ; 
 int XML_ELEMENT_TYPE_MIXED ; 
 int /*<<< orphan*/  XML_ERR_ELEMCONTENT_NOT_STARTED ; 
 scalar_t__ XML_PARSER_EOF ; 
 int /*<<< orphan*/  xmlFatalErrMsgStr (TYPE_2__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * xmlParseElementChildrenContentDeclPriv (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/ * xmlParseElementMixedContentDecl (TYPE_2__*,int) ; 

int
xmlParseElementContentDecl(xmlParserCtxtPtr ctxt, const xmlChar *name,
                           xmlElementContentPtr *result) {

    xmlElementContentPtr tree = NULL;
    int inputid = ctxt->input->id;
    int res;

    *result = NULL;

    if (RAW != '(') {
	xmlFatalErrMsgStr(ctxt, XML_ERR_ELEMCONTENT_NOT_STARTED,
		"xmlParseElementContentDecl : %s '(' expected\n", name);
	return(-1);
    }
    NEXT;
    GROW;
    if (ctxt->instate == XML_PARSER_EOF)
        return(-1);
    SKIP_BLANKS;
    if (CMP7(CUR_PTR, '#', 'P', 'C', 'D', 'A', 'T', 'A')) {
        tree = xmlParseElementMixedContentDecl(ctxt, inputid);
	res = XML_ELEMENT_TYPE_MIXED;
    } else {
        tree = xmlParseElementChildrenContentDeclPriv(ctxt, inputid, 1);
	res = XML_ELEMENT_TYPE_ELEMENT;
    }
    SKIP_BLANKS;
    *result = tree;
    return(res);
}