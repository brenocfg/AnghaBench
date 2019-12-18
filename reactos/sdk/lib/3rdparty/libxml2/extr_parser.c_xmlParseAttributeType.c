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
typedef  int /*<<< orphan*/  xmlEnumerationPtr ;

/* Variables and functions */
 scalar_t__ CMP5 (int /*<<< orphan*/ ,char,char,char,char,float) ; 
 scalar_t__ CMP6 (int /*<<< orphan*/ ,char,char,char,char,char,char) ; 
 scalar_t__ CMP7 (int /*<<< orphan*/ ,char,char,char,char,char,char,char) ; 
 scalar_t__ CMP8 (int /*<<< orphan*/ ,char,char,char,char,char,char,char,char) ; 
 int /*<<< orphan*/  CUR_PTR ; 
 char NXT (int) ; 
 char RAW ; 
 int /*<<< orphan*/  SHRINK ; 
 int /*<<< orphan*/  SKIP (int) ; 
 int XML_ATTRIBUTE_CDATA ; 
 int XML_ATTRIBUTE_ENTITIES ; 
 int XML_ATTRIBUTE_ENTITY ; 
 int XML_ATTRIBUTE_ID ; 
 int XML_ATTRIBUTE_IDREF ; 
 int XML_ATTRIBUTE_IDREFS ; 
 int XML_ATTRIBUTE_NMTOKEN ; 
 int XML_ATTRIBUTE_NMTOKENS ; 
 int xmlParseEnumeratedType (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
xmlParseAttributeType(xmlParserCtxtPtr ctxt, xmlEnumerationPtr *tree) {
    SHRINK;
    if (CMP5(CUR_PTR, 'C', 'D', 'A', 'T', 'A')) {
	SKIP(5);
	return(XML_ATTRIBUTE_CDATA);
     } else if (CMP6(CUR_PTR, 'I', 'D', 'R', 'E', 'F', 'S')) {
	SKIP(6);
	return(XML_ATTRIBUTE_IDREFS);
     } else if (CMP5(CUR_PTR, 'I', 'D', 'R', 'E', 'F')) {
	SKIP(5);
	return(XML_ATTRIBUTE_IDREF);
     } else if ((RAW == 'I') && (NXT(1) == 'D')) {
        SKIP(2);
	return(XML_ATTRIBUTE_ID);
     } else if (CMP6(CUR_PTR, 'E', 'N', 'T', 'I', 'T', 'Y')) {
	SKIP(6);
	return(XML_ATTRIBUTE_ENTITY);
     } else if (CMP8(CUR_PTR, 'E', 'N', 'T', 'I', 'T', 'I', 'E', 'S')) {
	SKIP(8);
	return(XML_ATTRIBUTE_ENTITIES);
     } else if (CMP8(CUR_PTR, 'N', 'M', 'T', 'O', 'K', 'E', 'N', 'S')) {
	SKIP(8);
	return(XML_ATTRIBUTE_NMTOKENS);
     } else if (CMP7(CUR_PTR, 'N', 'M', 'T', 'O', 'K', 'E', 'N')) {
	SKIP(7);
	return(XML_ATTRIBUTE_NMTOKEN);
     }
     return(xmlParseEnumeratedType(ctxt, tree));
}