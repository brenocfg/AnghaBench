#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* xmlParserCtxtPtr ;
typedef  int /*<<< orphan*/ * xmlEnumerationPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_13__ {scalar_t__ instate; TYPE_2__* input; scalar_t__ sax2; int /*<<< orphan*/  userData; TYPE_1__* sax; int /*<<< orphan*/  disableSAX; } ;
struct TYPE_12__ {int id; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* attributeDecl ) (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 scalar_t__ CMP9 (int /*<<< orphan*/ ,char,char,char,char,char,char,char,char,char) ; 
 int /*<<< orphan*/  CUR_PTR ; 
 int /*<<< orphan*/  GROW ; 
 int /*<<< orphan*/  NEXT ; 
 char RAW ; 
 int /*<<< orphan*/  SKIP (int) ; 
 scalar_t__ SKIP_BLANKS ; 
 int XML_ATTRIBUTE_CDATA ; 
 int XML_ATTRIBUTE_IMPLIED ; 
 int XML_ATTRIBUTE_REQUIRED ; 
 int /*<<< orphan*/  XML_ERR_ENTITY_BOUNDARY ; 
 int /*<<< orphan*/  XML_ERR_NAME_REQUIRED ; 
 int /*<<< orphan*/  XML_ERR_SPACE_REQUIRED ; 
 scalar_t__ XML_PARSER_EOF ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlAddDefAttrs (TYPE_3__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlAddSpecialAttr (TYPE_3__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  xmlAttrNormalizeSpace (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFatalErrMsg (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xmlFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFreeEnumeration (int /*<<< orphan*/ *) ; 
 int xmlParseAttributeType (TYPE_3__*,int /*<<< orphan*/ **) ; 
 int xmlParseDefaultDecl (TYPE_3__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * xmlParseName (TYPE_3__*) ; 

void
xmlParseAttributeListDecl(xmlParserCtxtPtr ctxt) {
    const xmlChar *elemName;
    const xmlChar *attrName;
    xmlEnumerationPtr tree;

    if (CMP9(CUR_PTR, '<', '!', 'A', 'T', 'T', 'L', 'I', 'S', 'T')) {
	int inputid = ctxt->input->id;

	SKIP(9);
	if (SKIP_BLANKS == 0) {
	    xmlFatalErrMsg(ctxt, XML_ERR_SPACE_REQUIRED,
		                 "Space required after '<!ATTLIST'\n");
	}
        elemName = xmlParseName(ctxt);
	if (elemName == NULL) {
	    xmlFatalErrMsg(ctxt, XML_ERR_NAME_REQUIRED,
			   "ATTLIST: no name for Element\n");
	    return;
	}
	SKIP_BLANKS;
	GROW;
	while ((RAW != '>') && (ctxt->instate != XML_PARSER_EOF)) {
	    int type;
	    int def;
	    xmlChar *defaultValue = NULL;

	    GROW;
            tree = NULL;
	    attrName = xmlParseName(ctxt);
	    if (attrName == NULL) {
		xmlFatalErrMsg(ctxt, XML_ERR_NAME_REQUIRED,
			       "ATTLIST: no name for Attribute\n");
		break;
	    }
	    GROW;
	    if (SKIP_BLANKS == 0) {
		xmlFatalErrMsg(ctxt, XML_ERR_SPACE_REQUIRED,
		        "Space required after the attribute name\n");
		break;
	    }

	    type = xmlParseAttributeType(ctxt, &tree);
	    if (type <= 0) {
	        break;
	    }

	    GROW;
	    if (SKIP_BLANKS == 0) {
		xmlFatalErrMsg(ctxt, XML_ERR_SPACE_REQUIRED,
			       "Space required after the attribute type\n");
	        if (tree != NULL)
		    xmlFreeEnumeration(tree);
		break;
	    }

	    def = xmlParseDefaultDecl(ctxt, &defaultValue);
	    if (def <= 0) {
                if (defaultValue != NULL)
		    xmlFree(defaultValue);
	        if (tree != NULL)
		    xmlFreeEnumeration(tree);
	        break;
	    }
	    if ((type != XML_ATTRIBUTE_CDATA) && (defaultValue != NULL))
	        xmlAttrNormalizeSpace(defaultValue, defaultValue);

	    GROW;
            if (RAW != '>') {
		if (SKIP_BLANKS == 0) {
		    xmlFatalErrMsg(ctxt, XML_ERR_SPACE_REQUIRED,
			"Space required after the attribute default value\n");
		    if (defaultValue != NULL)
			xmlFree(defaultValue);
		    if (tree != NULL)
			xmlFreeEnumeration(tree);
		    break;
		}
	    }
	    if ((ctxt->sax != NULL) && (!ctxt->disableSAX) &&
		(ctxt->sax->attributeDecl != NULL))
		ctxt->sax->attributeDecl(ctxt->userData, elemName, attrName,
	                        type, def, defaultValue, tree);
	    else if (tree != NULL)
		xmlFreeEnumeration(tree);

	    if ((ctxt->sax2) && (defaultValue != NULL) &&
	        (def != XML_ATTRIBUTE_IMPLIED) &&
		(def != XML_ATTRIBUTE_REQUIRED)) {
		xmlAddDefAttrs(ctxt, elemName, attrName, defaultValue);
	    }
	    if (ctxt->sax2) {
		xmlAddSpecialAttr(ctxt, elemName, attrName, type);
	    }
	    if (defaultValue != NULL)
	        xmlFree(defaultValue);
	    GROW;
	}
	if (RAW == '>') {
	    if (inputid != ctxt->input->id) {
		xmlFatalErrMsg(ctxt, XML_ERR_ENTITY_BOUNDARY,
                               "Attribute list declaration doesn't start and"
                               " stop in the same entity\n");
	    }
	    NEXT;
	}
    }
}