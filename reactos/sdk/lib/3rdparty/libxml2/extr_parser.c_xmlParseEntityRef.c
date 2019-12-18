#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* xmlParserCtxtPtr ;
typedef  TYPE_3__* xmlEntityPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_21__ {int etype; int checked; int /*<<< orphan*/ * content; } ;
struct TYPE_20__ {scalar_t__ instate; int options; int wellFormed; int standalone; scalar_t__ hasExternalSubset; scalar_t__ hasPErefs; scalar_t__ inSubset; scalar_t__ valid; struct TYPE_20__* userData; TYPE_1__* sax; int /*<<< orphan*/  nbentities; } ;
struct TYPE_19__ {int /*<<< orphan*/  (* reference ) (TYPE_2__*,int /*<<< orphan*/  const*) ;TYPE_3__* (* getEntity ) (TYPE_2__*,int /*<<< orphan*/  const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GROW ; 
 int /*<<< orphan*/  NEXT ; 
 char RAW ; 
 int /*<<< orphan*/  XML_ERR_ENTITYREF_SEMICOL_MISSING ; 
 int /*<<< orphan*/  XML_ERR_ENTITY_IS_EXTERNAL ; 
 int /*<<< orphan*/  XML_ERR_ENTITY_IS_PARAMETER ; 
 int /*<<< orphan*/  XML_ERR_LT_IN_ATTRIBUTE ; 
 int /*<<< orphan*/  XML_ERR_NAME_REQUIRED ; 
 int /*<<< orphan*/  XML_ERR_UNDECLARED_ENTITY ; 
 int /*<<< orphan*/  XML_ERR_UNPARSED_ENTITY ; 
 int XML_EXTERNAL_GENERAL_PARSED_ENTITY ; 
 int XML_EXTERNAL_GENERAL_UNPARSED_ENTITY ; 
#define  XML_EXTERNAL_PARAMETER_ENTITY 129 
#define  XML_INTERNAL_PARAMETER_ENTITY 128 
 int XML_INTERNAL_PREDEFINED_ENTITY ; 
 scalar_t__ XML_PARSER_ATTRIBUTE_VALUE ; 
 scalar_t__ XML_PARSER_EOF ; 
 int XML_PARSE_OLDSAX ; 
 int /*<<< orphan*/  XML_WAR_UNDECLARED_ENTITY ; 
 TYPE_3__* stub1 (TYPE_2__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  xmlErrMsgStr (TYPE_2__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  xmlFatalErr (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFatalErrMsg (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xmlFatalErrMsgStr (TYPE_2__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*) ; 
 TYPE_3__* xmlGetPredefinedEntity (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * xmlParseName (TYPE_2__*) ; 
 int /*<<< orphan*/  xmlParserEntityCheck (TYPE_2__*,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* xmlSAX2GetEntity (TYPE_2__*,int /*<<< orphan*/  const*) ; 
 scalar_t__ xmlStrchr (int /*<<< orphan*/ *,char) ; 

xmlEntityPtr
xmlParseEntityRef(xmlParserCtxtPtr ctxt) {
    const xmlChar *name;
    xmlEntityPtr ent = NULL;

    GROW;
    if (ctxt->instate == XML_PARSER_EOF)
        return(NULL);

    if (RAW != '&')
        return(NULL);
    NEXT;
    name = xmlParseName(ctxt);
    if (name == NULL) {
	xmlFatalErrMsg(ctxt, XML_ERR_NAME_REQUIRED,
		       "xmlParseEntityRef: no name\n");
        return(NULL);
    }
    if (RAW != ';') {
	xmlFatalErr(ctxt, XML_ERR_ENTITYREF_SEMICOL_MISSING, NULL);
	return(NULL);
    }
    NEXT;

    /*
     * Predefined entities override any extra definition
     */
    if ((ctxt->options & XML_PARSE_OLDSAX) == 0) {
        ent = xmlGetPredefinedEntity(name);
        if (ent != NULL)
            return(ent);
    }

    /*
     * Increase the number of entity references parsed
     */
    ctxt->nbentities++;

    /*
     * Ask first SAX for entity resolution, otherwise try the
     * entities which may have stored in the parser context.
     */
    if (ctxt->sax != NULL) {
	if (ctxt->sax->getEntity != NULL)
	    ent = ctxt->sax->getEntity(ctxt->userData, name);
	if ((ctxt->wellFormed == 1 ) && (ent == NULL) &&
	    (ctxt->options & XML_PARSE_OLDSAX))
	    ent = xmlGetPredefinedEntity(name);
	if ((ctxt->wellFormed == 1 ) && (ent == NULL) &&
	    (ctxt->userData==ctxt)) {
	    ent = xmlSAX2GetEntity(ctxt, name);
	}
    }
    if (ctxt->instate == XML_PARSER_EOF)
	return(NULL);
    /*
     * [ WFC: Entity Declared ]
     * In a document without any DTD, a document with only an
     * internal DTD subset which contains no parameter entity
     * references, or a document with "standalone='yes'", the
     * Name given in the entity reference must match that in an
     * entity declaration, except that well-formed documents
     * need not declare any of the following entities: amp, lt,
     * gt, apos, quot.
     * The declaration of a parameter entity must precede any
     * reference to it.
     * Similarly, the declaration of a general entity must
     * precede any reference to it which appears in a default
     * value in an attribute-list declaration. Note that if
     * entities are declared in the external subset or in
     * external parameter entities, a non-validating processor
     * is not obligated to read and process their declarations;
     * for such documents, the rule that an entity must be
     * declared is a well-formedness constraint only if
     * standalone='yes'.
     */
    if (ent == NULL) {
	if ((ctxt->standalone == 1) ||
	    ((ctxt->hasExternalSubset == 0) &&
	     (ctxt->hasPErefs == 0))) {
	    xmlFatalErrMsgStr(ctxt, XML_ERR_UNDECLARED_ENTITY,
		     "Entity '%s' not defined\n", name);
	} else {
	    xmlErrMsgStr(ctxt, XML_WAR_UNDECLARED_ENTITY,
		     "Entity '%s' not defined\n", name);
	    if ((ctxt->inSubset == 0) &&
		(ctxt->sax != NULL) &&
		(ctxt->sax->reference != NULL)) {
		ctxt->sax->reference(ctxt->userData, name);
	    }
	}
	xmlParserEntityCheck(ctxt, 0, ent, 0);
	ctxt->valid = 0;
    }

    /*
     * [ WFC: Parsed Entity ]
     * An entity reference must not contain the name of an
     * unparsed entity
     */
    else if (ent->etype == XML_EXTERNAL_GENERAL_UNPARSED_ENTITY) {
	xmlFatalErrMsgStr(ctxt, XML_ERR_UNPARSED_ENTITY,
		 "Entity reference to unparsed entity %s\n", name);
    }

    /*
     * [ WFC: No External Entity References ]
     * Attribute values cannot contain direct or indirect
     * entity references to external entities.
     */
    else if ((ctxt->instate == XML_PARSER_ATTRIBUTE_VALUE) &&
	     (ent->etype == XML_EXTERNAL_GENERAL_PARSED_ENTITY)) {
	xmlFatalErrMsgStr(ctxt, XML_ERR_ENTITY_IS_EXTERNAL,
	     "Attribute references external entity '%s'\n", name);
    }
    /*
     * [ WFC: No < in Attribute Values ]
     * The replacement text of any entity referred to directly or
     * indirectly in an attribute value (other than "&lt;") must
     * not contain a <.
     */
    else if ((ctxt->instate == XML_PARSER_ATTRIBUTE_VALUE) &&
	     (ent != NULL) && 
	     (ent->etype != XML_INTERNAL_PREDEFINED_ENTITY)) {
	if (((ent->checked & 1) || (ent->checked == 0)) &&
	     (ent->content != NULL) && (xmlStrchr(ent->content, '<'))) {
	    xmlFatalErrMsgStr(ctxt, XML_ERR_LT_IN_ATTRIBUTE,
	"'<' in entity '%s' is not allowed in attributes values\n", name);
        }
    }

    /*
     * Internal check, no parameter entities here ...
     */
    else {
	switch (ent->etype) {
	    case XML_INTERNAL_PARAMETER_ENTITY:
	    case XML_EXTERNAL_PARAMETER_ENTITY:
	    xmlFatalErrMsgStr(ctxt, XML_ERR_ENTITY_IS_PARAMETER,
	     "Attempt to reference the parameter entity '%s'\n",
			      name);
	    break;
	    default:
	    break;
	}
    }

    /*
     * [ WFC: No Recursion ]
     * A parsed entity must not contain a recursive reference
     * to itself, either directly or indirectly.
     * Done somewhere else
     */
    return(ent);
}