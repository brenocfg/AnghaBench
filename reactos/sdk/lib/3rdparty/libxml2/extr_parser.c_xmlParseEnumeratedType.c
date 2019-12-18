#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  xmlParserCtxtPtr ;
typedef  int /*<<< orphan*/ * xmlEnumerationPtr ;

/* Variables and functions */
 scalar_t__ CMP8 (int /*<<< orphan*/ ,char,char,char,char,char,char,char,char) ; 
 int /*<<< orphan*/  CUR_PTR ; 
 int /*<<< orphan*/  SKIP (int) ; 
 scalar_t__ SKIP_BLANKS ; 
 int XML_ATTRIBUTE_ENUMERATION ; 
 int XML_ATTRIBUTE_NOTATION ; 
 int /*<<< orphan*/  XML_ERR_SPACE_REQUIRED ; 
 int /*<<< orphan*/  xmlFatalErrMsg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * xmlParseEnumerationType (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xmlParseNotationType (int /*<<< orphan*/ ) ; 

int
xmlParseEnumeratedType(xmlParserCtxtPtr ctxt, xmlEnumerationPtr *tree) {
    if (CMP8(CUR_PTR, 'N', 'O', 'T', 'A', 'T', 'I', 'O', 'N')) {
	SKIP(8);
	if (SKIP_BLANKS == 0) {
	    xmlFatalErrMsg(ctxt, XML_ERR_SPACE_REQUIRED,
			   "Space required after 'NOTATION'\n");
	    return(0);
	}
	*tree = xmlParseNotationType(ctxt);
	if (*tree == NULL) return(0);
	return(XML_ATTRIBUTE_NOTATION);
    }
    *tree = xmlParseEnumerationType(ctxt);
    if (*tree == NULL) return(0);
    return(XML_ATTRIBUTE_ENUMERATION);
}