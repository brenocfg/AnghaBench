#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xmlParserErrors ;
typedef  TYPE_1__* xmlParserCtxtPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_5__ {scalar_t__ errNo; int /*<<< orphan*/  instate; } ;

/* Variables and functions */
 scalar_t__ CMP6 (int /*<<< orphan*/ ,char,float,char,char,char,char) ; 
 scalar_t__ CMP8 (int /*<<< orphan*/ ,char,char,char,char,char,char,char,char) ; 
 scalar_t__ CMP9 (int /*<<< orphan*/ ,char,char,char,char,unsigned char,char,char,char,char) ; 
 int /*<<< orphan*/  CUR_PTR ; 
 int /*<<< orphan*/  SKIP (int) ; 
 scalar_t__ SKIP_BLANKS ; 
 int XML_ATTRIBUTE_FIXED ; 
 int XML_ATTRIBUTE_IMPLIED ; 
 int XML_ATTRIBUTE_NONE ; 
 int XML_ATTRIBUTE_REQUIRED ; 
 int /*<<< orphan*/  XML_ERR_SPACE_REQUIRED ; 
 int /*<<< orphan*/  XML_PARSER_DTD ; 
 int /*<<< orphan*/  xmlFatalErrMsg (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * xmlParseAttValue (TYPE_1__*) ; 

int
xmlParseDefaultDecl(xmlParserCtxtPtr ctxt, xmlChar **value) {
    int val;
    xmlChar *ret;

    *value = NULL;
    if (CMP9(CUR_PTR, '#', 'R', 'E', 'Q', 'U', 'I', 'R', 'E', 'D')) {
	SKIP(9);
	return(XML_ATTRIBUTE_REQUIRED);
    }
    if (CMP8(CUR_PTR, '#', 'I', 'M', 'P', 'L', 'I', 'E', 'D')) {
	SKIP(8);
	return(XML_ATTRIBUTE_IMPLIED);
    }
    val = XML_ATTRIBUTE_NONE;
    if (CMP6(CUR_PTR, '#', 'F', 'I', 'X', 'E', 'D')) {
	SKIP(6);
	val = XML_ATTRIBUTE_FIXED;
	if (SKIP_BLANKS == 0) {
	    xmlFatalErrMsg(ctxt, XML_ERR_SPACE_REQUIRED,
			   "Space required after '#FIXED'\n");
	}
    }
    ret = xmlParseAttValue(ctxt);
    ctxt->instate = XML_PARSER_DTD;
    if (ret == NULL) {
	xmlFatalErrMsg(ctxt, (xmlParserErrors)ctxt->errNo,
		       "Attribute default value declaration error\n");
    } else
        *value = ret;
    return(val);
}